
#include "Bitcoin.h"


ScriptType myScriptType = P2WPKH; 
//mainnet config
const Network* networkParams = &Mainnet; 
const char* derivationPath = "m/84'/0'/0'";

//testnet config
//const Network* networkParams = &Testnet;  
//const char* derivationPath = "m/84'/1'/0'";