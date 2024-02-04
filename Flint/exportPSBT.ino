#include <Arduino.h>



void showPSBT( std::string& str )
{

    

      lv_qrcode_update(qr,  str.c_str(), strlen(str.c_str()));
}

void displayPSBT(){
  HDPrivateKey hd = KeyManager::getInstance().getHDPrivateKey();
  PSBT psbt = CurrentPSBT::getInstance().getPSBT();

  // Use a String to accumulate the output
  String output = "\n\n Transactions details:\n";

  // going through all outputs
  for(int i = 0; i < psbt.tx.outputsNumber; i++){
    output += psbt.tx.txOuts[i].address(&Testnet); // Append address
    
    // check if it is a change output
    if(psbt.txOutsMeta[i].derivationsLen > 0){ // there is derivation path
      PSBTDerivation der = psbt.txOutsMeta[i].derivations[0];
      HDPublicKey pub = hd.derive(der.derivation, der.derivationLen).xpub();
      // as pub is HDPublicKey it will also generate correct address type
      if(pub.address() == psbt.tx.txOuts[i].address()){
        output += " (change) ";
      }
    }

    output += "\n     -> ";
    output += int(psbt.tx.txOuts[i].amount); // Append amount
    output += " sat\n\n";
  }

  // Now use the output String to set the label text
  lv_label_set_text_static(ui_Label1129, output.c_str());

  // If you still want to print it to the Serial for debugging
  Serial.println(output);
}
