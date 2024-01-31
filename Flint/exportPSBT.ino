#include <Arduino.h>



void showPSBT( std::string& str )
{

    

      lv_qrcode_update(qr,  str.c_str(), strlen(str.c_str()));
}




