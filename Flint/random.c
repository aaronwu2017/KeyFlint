    #include <esp_random.h>
#include <esp_system.h>
#include <bootloader_random.h>
#include "esp_system.h"
#include "esp_random.h"
#include "random.h"
#include "bootloader_random.h"




 void random_start_collecting(uint8_t* outputArray, size_t size) {
    // from https://docs.espressif.com/projects/esp-idf/en/release-v4.1/api-reference/system/system.html
    // If the RF subsystem is not used by the program, the function bootloader_random_enable() can be
    // called to enable an entropy source.
    // Note: we need to call bootloader_rq working later.

 
    bootloader_random_enable();
    esp_fill_random(outputArray, size);
    bootloader_random_disable();

 

}
