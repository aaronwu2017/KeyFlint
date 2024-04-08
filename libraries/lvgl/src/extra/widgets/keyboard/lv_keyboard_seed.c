#include <stdio.h>
#include "lv_keyboard_seed.h"
#include "../../../../../uBitcoin/src/utility/trezor/bip39_english.h"

#include "../../../../../ui/src/ui.h"
#include <esp_log.h>

//#define LOG_TAG "seed_keyboard "    e.g.           ESP_LOGE(LOG_TAG, "after initializing trie");
#if LV_USE_BTNMATRIX
void initializeNewTrieFromASingleLetter(char letter);
void initializeTrieForA();

static int letterTobtnm_mapIndex[26] = {10, 24, 22, 12, 2, 13, 14, 15, 7, 16, 17, 18, 26, 25, 8, 9, 0, 3, 11, 4, 6, 23, 1, 21, 5, 20};
void btnm_event_handler1(lv_event_t * e) {
    char strtest[12];
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
    lv_obj_t * ta = lv_event_get_user_data(e);
    int index = txt[0] - 'a';
    const char * fullEnteredText = lv_textarea_get_text(ta) ;
    if(strcmp(txt, "go") == 0) {
        if(!seedWordsValidation(fullEnteredText)){
            return;
        }
        lv_event_send(obj, LV_EVENT_READY, NULL);
        //  lv_event_send(obj, LV_EVENT_READY, ta);
        initiateKeyPair(fullEnteredText);
    }



    if (strcmp(txt, "space") == 0) {
        if (currentNode == NULL || currentNode->isEndOfWord == 0) {
            return;
        } 
        if (fullEnteredText != NULL && strlen(fullEnteredText) > 0) { // Ensure the string is not NULL and not empty
            char lastCharacter = fullEnteredText[strlen(fullEnteredText) - 1]; // Get the last character of the text
            if (lastCharacter != ' ') { // Check if the last character is not a space
                lv_textarea_add_text(ta, " "); // Add a space only if the last character is not a space
                // get ready to process a new word
                deleteTrie(myTrie);
                myTrie = NULL;
                currentNode =NULL;
                for (int i = 0; i < 26; i++) {
                    lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[i], LV_BTNMATRIX_CTRL_HIDDEN);
                }
                lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23], LV_BTNMATRIX_CTRL_HIDDEN);
            }
            // If the last character is a space, do nothing
        } 
        return; // Return after handling the "space" case
    }


    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
        // need to delete the previous word
        if(currentNode == NULL || currentNode->parent == NULL){
            const char *lastSpace = strrchr(fullEnteredText, ' ');
            if (lastSpace != NULL) {
                const char *lastWord = fullEnteredText;
                for (const char *p = lastSpace - 1; p > fullEnteredText; --p) {
                    if ( *(p - 1) == ' '&&*p != ' ') {
                        lastWord = p;
                        break;
                    }
                }
               initializeNewTrieFromASingleLetter(lastWord[0]);
                for (const char *p = lastWord; p <= lastSpace; p++) {
                  if (*p == ' ') {
                        lv_textarea_del_char(ta);
                    } else{
                        int lastWordLetterIndex = *p - 'a';
                        currentNode = currentNode->children[lastWordLetterIndex];
                    }                 
                }

                currentNode = currentNode->parent;
                lv_textarea_del_char(ta);
                return;
            }else{
           //no text on the textarea
                return;    
            }

        } else {
        //delete the current word
            currentNode = currentNode->parent;
            lv_textarea_del_char(ta);
            if(currentNode == myTrie){
                deleteTrie(myTrie);
                currentNode = NULL;
                myTrie = NULL;
                for (int i = 0; i < 26; i++) {
                    lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[i], LV_BTNMATRIX_CTRL_HIDDEN);
                }
                lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23], LV_BTNMATRIX_CTRL_HIDDEN);
            } else {
                for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {
                    lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
                    if (currentNode->children[horizontalIndex] == NULL) {
                        lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
                    }
                }
            }
            return;
        }
        
    }
////////////////////// not space, not go, not back, regular letter
    if (myTrie == NULL) {
        initializeNewTrieFromASingleLetter(txt[0]);
        currentNode = myTrie;
    }

    if (currentNode && currentNode->children[index] != NULL) {
        currentNode = currentNode->children[index];
    }

    lv_textarea_add_text(ta, txt);
    // reset keyboard
    for (int i = 0; i < 26; i++) {
        lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[i], LV_BTNMATRIX_CTRL_HIDDEN);
    }


    int hasChild = 0;
    for (int i = 0; i < 26; i++) {
        if (currentNode->children[i] != NULL) {
            hasChild = 1;
            break;
        }
    }
    if (currentNode->isEndOfWord == 1 && hasChild ==0) {
        lv_textarea_add_text(ta, " ");
        currentNode = myTrie;
        deleteTrie(myTrie);
        currentNode = NULL;
        myTrie =NULL;
    } else{
        for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {
                if (currentNode->children[horizontalIndex] == NULL) {
                    lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
                }
        } 
    }
    if(currentNode == myTrie){
         //disable x  as bip39 word list doesnot have word starting with x
       lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23], LV_BTNMATRIX_CTRL_HIDDEN);
    }
}

static const char * btnm_map_go[] = {"q", "w", "e", "r", "t", "y","u","i", "o","p","\n",
                                  "a", "s", "d", "f", "g","h","j","k","l", "\n",
                                  LV_SYMBOL_BACKSPACE,"z", "x", "c", "v", "b","n","m","go222222",""
                                   };


static const char * btnm_map[] = {"q", "w", "e", "r", "t", "y","u","i", "o","p","\n",
                                  "a", "s", "d", "f", "g","h","j","k","l", "\n",
                                  LV_SYMBOL_BACKSPACE,"z", "x", "c", "v", "b","n","m","space","go",""
                                   };



lv_obj_t * lv_ex_btnmatrix_seed(lv_obj_t * obj)
{
    lv_obj_t * btnm1 = lv_btnmatrix_create(obj);
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_btnmatrix_set_btn_width(btnm1, 27,  50);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);

    return btnm1;
}


int seedWordsValidation(const char* seedWords) {
    int spaceCount = 0; // Variable to hold the count of spaces
    int length = strlen(seedWords); // Get the length of the seed words string

    // Loop through each character in the string to count spaces
    for(int i = 0; i < length; i++) {
        if(seedWords[i] == ' ') {
            spaceCount++;
        }
    }

    // Check if the number of spaces is either 11 or 23
    if(spaceCount == 12 || spaceCount == 24) {
        return 1; // Valid seed words
    } else {
        return 0; // Invalid seed words
    }
}



void initializeNewTrieFromASingleLetter(char letter) {
        switch(letter) {
            case 'a': initializeTrieForA(); break;
            case 'b': initializeTrieForB(); break;
            case 'c': initializeTrieForC(); break;
            case 'd': initializeTrieForD(); break;
            case 'e': initializeTrieForE(); break;
            case 'f': initializeTrieForF(); break;
            case 'g': initializeTrieForG(); break;
            case 'h': initializeTrieForH(); break;
            case 'i': initializeTrieForI(); break;
            case 'j': initializeTrieForJ(); break;
            case 'k': initializeTrieForK(); break;
            case 'l': initializeTrieForL(); break;
            case 'm': initializeTrieForM(); break;
            case 'n': initializeTrieForN(); break;
            case 'o': initializeTrieForO(); break;
            case 'p': initializeTrieForP(); break;
            case 'q': initializeTrieForQ(); break;
            case 'r': initializeTrieForR(); break;
            case 's': initializeTrieForS(); break;
            case 't': initializeTrieForT(); break;
            case 'u': initializeTrieForU(); break;
            case 'v': initializeTrieForV(); break;
            case 'w': initializeTrieForW(); break;
   
            case 'y': initializeTrieForY(); break;
            case 'z': initializeTrieForZ(); break;
           // default: handleDefaultCase(); // Optional: handle any character that is not a-z
        }
}
void initializeTrieForA(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 0; i <= 135; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}

void initializeTrieForB(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 136; i <= 252; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForC(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 253; i <= 438; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForD(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 439; i <= 550; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForE(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 551; i <= 650; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForF(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 651; i <= 756; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForG(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 757; i <= 832; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForH(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 833; i <= 896; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForI(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 897; i <= 951; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForJ(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 952; i <= 971; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForK(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 972; i <= 991; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForL(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 992; i <= 1067; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForM(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1068; i <= 1172; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForN(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1173; i <= 1213; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForO(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1214; i <= 1268; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForP(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1269; i <=1400; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForQ(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1401; i <= 1408; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForR(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1409; i <= 1516; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForS(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1517; i <= 1766; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForT(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1767; i <= 1887; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForU(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1888; i <= 1922; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForV(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1923; i <= 1968; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForW(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 1969; i <= 2037; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}

void initializeTrieForY(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 2038; i <= 2043; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}
void initializeTrieForZ(){
    myTrie = createNode(0);  
    currentNode = myTrie;
    for (int i = 2044; i <= 2047; i++) {
        insert(myTrie, wordlist[i],i);  // Insert words into the trie
    }

}

#endif