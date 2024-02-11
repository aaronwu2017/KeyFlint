void displayPrivateKey() {
    HDPrivateKey hd = KeyManager::getInstance().getHDPrivateKey();
    HDPrivateKey account = hd.derive("m/84'/0'/0'/");
    // Convert HDPrivateKey to string for manipulation
    String keyString = account.toString();

    // Calculate positions for splitting the string into four parts
    int partLength = keyString.length() / 4; // Determine the length of each part

    // Create the output string and insert newline characters at calculated positions
    String output = "\n\n\n\n\n\n\n\nDerived Private Key with Passphrase:\n\n";
    for (int i = 0; i < 3; ++i) { // Only need to add newline three times
        output += keyString.substring(i * partLength, (i + 1) * partLength) + "\n";
    }
    // Add the last part without a newline at the end
    output += keyString.substring(3 * partLength);













 const std::string* mnemonics = KeyManager::getInstance().getMnemonic(); // Hypothetical getter


 output += "\n\n\nSeed Sords:\n\n";
    for (int i = 0; i < 24; ++i) {
        output += mnemonics[i].c_str(); // Convert std::string to c_str for concatenation
        if ((i + 1) % 6 == 0) { // After every 4 words, add a newline
            output += "\n";
        } else {
            output += " "; // Add a space between words
        }
    }



    
    // Now use the output String to set the label text
    lv_label_set_text_static(ui_Label118, output.c_str());

    // If you still want to print it to the Serial for debugging
    Serial.println(output);                                                                              
}