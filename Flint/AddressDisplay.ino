void displayAddresses() {
    HDPrivateKey hd = KeyManager::getInstance().getHDPrivateKey();
    
    // Assuming derive() can correctly handle BIP84 derivation paths
    // and your HDPrivateKey class or a related class has a method to derive addresses
    // Derive the account level private key for account 0
    HDPrivateKey account = hd.derive("m/84'/0'/0'");

    // This string will accumulate the addresses
    String output = "\n\n\n\nFirst 10 Native SegWit addresses:\n";

    // Loop to derive the first 5 addresses under the external chain of account 0
    for (int i = 0; i < 10; i++) {
        // Derive the ith address under the external chain (0 for external)
        HDPrivateKey addressKey = account.derive("0/" + String(i));
        // Assuming your addressKey object has a method to get the address string
        String address = addressKey.address(); // This should return the SegWit address
        
        output += String(i + 1) + ": " + address + "\n";
        
        // Also print each address to the Serial for debugging
        Serial.println(String(i + 1) + ": " + address);
    }

    // Use the output String to set the label text
    lv_label_set_text_static(ui_Label119, output.c_str());

    // If you still want to print it to the Serial for debugging
    Serial.println(output);
}
