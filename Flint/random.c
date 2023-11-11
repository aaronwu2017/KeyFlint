    #include <esp_random.h>
#include <esp_system.h>

#define SHA256_LEN 32  // Assuming SHA256_LEN is 32 bytes for the entropy_state array.

static uint8_t entropy_state[SHA256_LEN];  // Consider moving this to the source (.c) file or making it extern.
void random_start_collecting(void)
{

    // from https://docs.espressif.com/projects/esp-idf/en/release-v4.1/api-reference/system/system.html
    // If the RF subsystem is not used by the program, the function bootloader_random_enable() can be
    // called to enable an entropy source.
    // Note: we need to call bootloader_random_disable() afterwards if we want
    // BLE or I2S peripherals (camera?) working later.

    bootloader_random_enable();
    esp_fill_random(entropy_state, sizeof(entropy_state));
    bootloader_random_disable();


}
