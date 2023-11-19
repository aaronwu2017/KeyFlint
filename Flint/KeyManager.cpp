// KeyManager.cpp
#include "KeyManager.h"
#include "Bitcoin.h"
KeyManager::KeyManager() {
    // Constructor implementation, if needed
}

KeyManager& KeyManager::getInstance() {
    static KeyManager instance;
    return instance;
}

void KeyManager::setValues(const HDPrivateKey* hdKey, 
                           const HDPrivateKey* hdPassphraseKey, 
                           const std::string mnemonics[24], 
                           const std::string* pass) {
    if (hdKey != nullptr) {
        this->hd = *hdKey;
    }
    if (hdPassphraseKey != nullptr) {
        this->hdWithPassphrase = *hdPassphraseKey;
    }
    for (int i = 0; i < 24; ++i) {
        this->mnemonic[i] = mnemonics[i];  // Assuming you always want to set mnemonics
    }
    if (pass != nullptr) {
        this->passphrase = *pass;
    }
}