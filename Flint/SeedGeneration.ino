extern "C" {
  #include "Trie.h"

#include "random.h"

}
#define SHA256_LEN 32
#include "utility/trezor/bip39_english.h"
static TrieNode *myTrie = NULL;
static TrieNode *currentNode = NULL;
String seedPhrase[24];

// Function to get the currently selected seed word in the UI roller
void getSelectedSeedWord(lv_event_t *e) {
    // Get the index of the selected word

    int wordIndex = lv_roller_get_selected(ui_Roller2);
    Serial.println(wordIndex);
    setSelectedSeedWordBip39Text(wordIndex);
  
}

void setSelectedSeedWordBip39Text(int wordIndex){
    // Retrieve the seed phrase array from KeyManager
    const std::string* mySeedPhrase = KeyManager::getInstance().getSeedPhrase();

    // Get the selected word as a std::string and then convert to a C-style string
    const std::string& wordString = mySeedPhrase[wordIndex];
    const char* word = wordString.c_str();

    // Traverse the trie to find the node corresponding to the selected word
    currentNode = myTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        currentNode = currentNode->children[index];
    }

    // Get the number associated with the node
    int number = currentNode->bip39Number;

    // Convert the number to a binary string
    char binaryString[12]; // 11 for binary digits + 1 for null terminator
    itoa(number, binaryString, 2); // Convert to binary string

    // Create the final string to set on the label
    char labelString[64];
    sprintf(labelString, "Number: %d\nBinary: %s", number, binaryString);

    // Set the text of the label to display the information
    lv_label_set_text(ui_Label13, labelString);
}


void splitString(const std::string& str, std::string seedPhraseArray[24]) {
    int wordIndex = 0;
    size_t startPos = 0;

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || i == str.length() - 1) {
            std::string word = (i == str.length() - 1) ? str.substr(startPos) : str.substr(startPos, i - startPos);
            seedPhraseArray[wordIndex++] = word;
            startPos = i + 1;

            if (wordIndex >= 24) {
                break;
            }
        }
    }
}


//todo refactor to make it more clear
void initiateKeyPair(const char* seedphrase) {
  std::string seedphraseStr(seedphrase);

    // Check if the last character is a space for user input seed path

    if( seedphraseStr.back() == ' '){
         seedphraseStr.pop_back();
    }
       std::string seedPhraseArray[24];
     

        splitString(seedphraseStr, seedPhraseArray);
    
    // Convert the array back to a single string without trailing space
    std::string mnemonicsString;
    for (int i = 0; i < 24 && !seedPhraseArray[i].empty(); i++) {
        if (i > 0) mnemonicsString += " ";
        mnemonicsString += seedPhraseArray[i];
    }

    Serial.println(mnemonicsString.c_str());

     HDPrivateKey hd(seedphraseStr.c_str(), "");
    KeyManager::getInstance().setMnemonicsString(seedphraseStr.c_str());
    KeyManager::getInstance().setHDPrivateKey(&hd);
    
    // Additionally, set the mnemonic array in KeyManager
    KeyManager::getInstance().setMnemonicWords(seedPhraseArray);
        
}



void generateSeed(const char* userEntropy) {
    uint8_t final_entropy_state[SHA256_LEN];
    getFinalRandomEntropy(final_entropy_state,256,userEntropy);
    String seedPhraseString =  generateMnemonic(24, final_entropy_state,256);


    initiateKeyPair(seedPhraseString.c_str());
    displaySeedOnUI();
}

void getFinalRandomEntropy(uint8_t* outputArray, size_t size, const char* userEntropy) {
    uint8_t esp32_entropy_state[SHA256_LEN];
    esp32_random_collecting(esp32_entropy_state, SHA256_LEN);

    // Buffer to store the combined entropy
    uint8_t combined_entropy[2 * SHA256_LEN];  // Adjust the size as needed

    // Copy ESP32 entropy to combined_entropy
    memcpy(combined_entropy, esp32_entropy_state, SHA256_LEN);

    if (userEntropy != nullptr) {
        // Convert userEntropy from string to bytes and append to combined_entropy
        // (Assuming userEntropy is a binary string like "101010...")
        size_t userEntropyLen = strlen(userEntropy);
        for (size_t i = 0; i < userEntropyLen; ++i) {
            // Assuming SHA256_LEN + i/8 is within bounds of combined_entropy
            combined_entropy[SHA256_LEN + i / 8] <<= 1;
            if (userEntropy[i] == '1') {
                combined_entropy[SHA256_LEN + i / 8] |= 1;
            }
        }
    }

    // Perform double hashing on the combined entropy
    uint8_t double_hash[SHA256_LEN];
    doubleSha(combined_entropy, sizeof(combined_entropy), double_hash);

    // Copy the double hash result to the output array
    memcpy(outputArray, double_hash, SHA256_LEN);
}

void displaySeedOnUI(){

 if (myTrie == NULL) {
        myTrie = createNode(0);  
        for (int i = 0; i < 2048; i++) {
            insert(myTrie, wordlist[i],i);  // Insert words into the trie
           
        }
        currentNode = myTrie;
   
    }



std::string seedPhraseStdString = KeyManager::getInstance().getMnemonicsString();

    String options = "";
    int wordNumber = 1; // Initialize word number counter


//number each word in the 24 word seedphrase
    for (int i = 0; i < seedPhraseStdString.length(); i++) {
        if (i == 0 || seedPhraseStdString[i - 1] == ' ') { // Check for the start of a new word
            options += String(wordNumber) + ". "; // Append the word number and a period
            wordNumber++; // Increment the word number
        }

        if (seedPhraseStdString[i] == ' ') {
            options += '\n'; // Add a newline character instead of space
        } else {
            options += seedPhraseStdString[i]; // Add the current character
        }
    }

    const char *options_cStr = options.c_str();
    lv_roller_set_options(ui_Roller2, options_cStr, LV_ROLLER_MODE_NORMAL);

    //String labelStr = seedPhrase[0];
   // lv_label_set_text(ui_Label28, labelStr.c_str());
   setSelectedSeedWordBip39Text(0);
    }