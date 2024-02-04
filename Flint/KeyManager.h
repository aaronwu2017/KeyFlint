// KeyManager.h
#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H
#include "Bitcoin.h"
#include <Arduino.h>
// Include other necessary headers...



class KeyManager {
private:
    KeyManager();
    KeyManager(const KeyManager&) = delete;
    KeyManager& operator=(const KeyManager&) = delete;

public:
    static KeyManager& getInstance();

    HDPrivateKey hd;
    HDPrivateKey hdWithPassphrase;
    std::string mnemonic[24];
    std::string mnemonicsString;
    std::string passphrase;
const std::string* getSeedPhrase() const {
        return mnemonic;  
    }
const HDPrivateKey& getHDPrivateKey() const;
const std::string& getMnemonicsString() const;
void setHDPrivateKey(const HDPrivateKey* hdKey);
void setMnemonicsString(const char* seedphrase);
  void setValues(const HDPrivateKey* hdKey, 
                   const HDPrivateKey* hdPassphraseKey, 
                   const std::string mnemonics[24], 
                   const std::string* mnemonicsString,
                   const std::string* pass);
};


#endif // KEY_MANAGER_H
