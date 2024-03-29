void initializeDecoder(){


auto decoder = std::make_unique<ur::URDecoder>();


CurrentPSBT::getInstance().setDecoder(std::move(decoder));
CurrentPSBT::getInstance().setStartReceiving(true);

} 

void stopPSBTReceving(){

  CurrentPSBT::getInstance().setStartReceiving(false);
}
void stopPSBTExporting(){

 CurrentPSBT::getInstance().setStartExporting(false);
}

void  encoderActivity(){
   CurrentPSBT& currentPSBT = CurrentPSBT::getInstance();
     std::string str = currentPSBT.getNextPart();
     
lv_qrcode_update(qr, str.c_str(), strlen(str.c_str()));
    //    showPSBT(str);
        delay(100);
}
void decoderActivity(){
   CurrentPSBT& currentPSBT = CurrentPSBT::getInstance();
    if (!currentPSBT.isDecodeSuccess()) {
        delay(100);
            if (Serial1.available() > 0) {
                String tempVal = "";
                while (Serial1.available() > 0) {
                    tempVal += char(Serial1.read());
                }
                Serial.println(tempVal);
                currentPSBT.receivePart(tempVal.c_str());
                Serial.println(currentPSBT.estimated_percent_complete());
               
            }
        } else {
            // Next screen
            ur::ByteVector psbtURFormat = currentPSBT.getDecodedUR().cbor();
            std::string psbtURFormatHex = ur::data_to_hex(psbtURFormat);
            if (psbtURFormatHex.size() >= 2 && psbtURFormatHex.substr(0, 2) == "59") {
                // Create a new string from the vector, starting from the 4th byte
                

                _ui_screen_change( &ui_Screen1113, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_Screen1113_screen_init);
                std::string strippedString = psbtURFormatHex.substr(6); 
                PSBT psbt;
                psbt.parse(strippedString.c_str());  
                CurrentPSBT::getInstance().setPSBT(psbt);
                 displayPSBT();
            }

            CurrentPSBT::getInstance().setStartReceiving(false);
        }
}

void initializeEncoder(){


 PSBT psbt= CurrentPSBT::getInstance().getPSBT();
   std::string psbtAsString = psbt.toString().c_str();

    ur::ByteVector message = hexStringToByteVector(psbtAsString);
  ur::ByteVector cbor;
  ur::CborLite::encodeBytes(cbor, message);
  auto ur =  ur::UR("crypto-psbt", cbor);
auto encoder = std::make_unique<ur::UREncoder>(ur, 10);
CurrentPSBT::getInstance().setEncoder(std::move(encoder));
CurrentPSBT::getInstance().setStartExporting(true);

}
ur::ByteVector hexStringToByteVector(const std::string& hex) {
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}


 void signAndExport(){
 

     CurrentPSBT& currentPSBT = CurrentPSBT::getInstance();
PSBT psbt= CurrentPSBT::getInstance().getPSBT();
const HDPrivateKey& privateKey = KeyManager::getInstance().getHDPrivateKey();
   Serial.println(psbt);
psbt.sign(privateKey);
   Serial.println(psbt);



std::string hex = psbt.toString().c_str();

 ur::ByteVector message = hexStringToByteVector(hex);
  ur::ByteVector cbor;
  ur::CborLite::encodeBytes(cbor, message);
  auto ur =  ur::UR("crypto-psbt", cbor);
auto encoder = std::make_unique<ur::UREncoder>(ur, 10);
CurrentPSBT::getInstance().setEncoder(std::move(encoder));
CurrentPSBT::getInstance().setStartExporting(true);

 }


 void displayPSBT(){
  HDPrivateKey hd = KeyManager::getInstance().getHDPrivateKey();
  PSBT psbt = CurrentPSBT::getInstance().getPSBT();
  // Use a String to accumulate the output
  String output = "\n\n\n\n Transactions details:\n";

  // going through all outputs
  for(int i = 0; i < psbt.tx.outputsNumber; i++){
    output += psbt.tx.txOuts[i].address(networkParams); // Append address

    // check if it is a change output
    if(psbt.txOutsMeta[i].derivationsLen > 0){ // there is derivation path
      PSBTDerivation der = psbt.txOutsMeta[i].derivations[0];
      HDPublicKey pub = hd.derive(der.derivation, der.derivationLen).xpub();
      // as pub is HDPublicKey it will also generate correct address type
      if(pub.address() == psbt.tx.txOuts[i].address()){
        output += "\n (change) ";
      }
    }

    output += "\n     -> ";
    output += int(psbt.tx.txOuts[i].amount); // Append amount
    output += " sat\n\n";
  }
 long long feeAmount = psbt.fee(); // 
  output += "Fee: ";
  output += feeAmount; // C
  output += " sat\n";
  // Now use the output String to set the label text
  lv_label_set_text_static(ui_Label1129, output.c_str());

  // If you still want to print it to the Serial for debugging
  Serial.println(output);
}