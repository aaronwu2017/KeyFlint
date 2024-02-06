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
const std::string& KeyManager::getMnemonicsString() const {
    return mnemonicsString;
}
void KeyManager::setHDPrivateKey(const HDPrivateKey* hdKey){
     this->hd = *hdKey;
}
const HDPrivateKey& KeyManager::getHDPrivateKey() const {
    return hd;
}

void KeyManager::setMnemonicsString(const char* seedphrase) {
    if (seedphrase != nullptr) {
        mnemonicsString = seedphrase;
    }
}
void KeyManager::setValues(const HDPrivateKey* hdKey, 
                           const HDPrivateKey* hdPassphraseKey, 
                           const std::string mnemonics[24], 
                          const std::string* mnemonicsString,
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
    if (mnemonicsString != nullptr) {
        this->mnemonicsString = *mnemonicsString;
    }
    if (pass != nullptr) {
        this->passphrase = *pass;
    }
    
}