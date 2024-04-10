#include "userConfig.h"
void displayPublicKey() {
    // Get the master HD private key from the KeyManager
    HDPrivateKey hd = KeyManager::getInstance().getHDPrivateKey();
    
    // Derive the BIP84 native SegWit account for mainnet (assuming mainnet with '0', adjust if needed)
    HDPrivateKey account = hd.derive(derivationPath);
    
    // Get the extended public key (xpub) from the derived account
    HDPublicKey xpub = account.xpub();
    xpub.type = myScriptType ; 
; // Ensure the type is set for correct address derivation
    
    // Convert the xpub to a string for display
    String xpubString = xpub.toString();

    // Assuming xpub has a method to get its string representation
    Serial.println(xpubString);
 lv_qrcode_update(XPub_qr , xpubString.c_str(), strlen(xpubString.c_str()));
    // Split the xpubString into four parts and add newline characters
    int partLength = xpubString.length() / 6;
    String formattedXpub = "";
    for (int i = 0; i < 6; i++) {
        int start = i * partLength; 
        int end = (i < 5) ? (start + partLength) : xpubString.length(); // Ensure the last part includes the end of the string
        formattedXpub += xpubString.substring(start, end);
        if (i < 5) { // Don't add a newline at the end of the last part
            formattedXpub += "\n";
        }
    }

    // Prepare the output string
    String output = "\n\nNative SegWit Public Key \n(xpub):\n" + formattedXpub;

    // Use the output String to set the label text in the UI
    lv_label_set_text_static(ui_Label116, output.c_str());

    // Print the formatted xpub to the Serial for debugging
    Serial.println(formattedXpub);
}
