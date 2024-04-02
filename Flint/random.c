 //   #include <esp_random.h>
 #include <esp_system.h>

#include <bootloader_random.h>

#include "random.h"
#include "bootloader_random.h"
#include <esp_log.h>
#include <mbedtls/sha256.h>
#define LOG_TAG "esp32_random"

 void esp32_random_collecting(uint8_t* outputArray, size_t size) {
    //1 First source of randomness
    // from https://docs.espressif.com/projects/esp-idf/en/release-v4.1/api-reference/system/system.html
    // If the RF subsystem is not used by the program, the function bootloader_random_enable() can be
    // called  to enable an entropy source.
    // Note: we need to call bootloader_rq working later.
    // Have to set the log level to ERROR to be visiable on arduino ide
    esp_log_level_set("esp32_random", ESP_LOG_ERROR);
    bootloader_random_enable();
    esp_fill_random(outputArray, size); 
    bootloader_random_disable();
    ESP_LOGE(LOG_TAG, "Random data collection complete.");

    // Enable to log immediately after collecting random data.


    //ESP_LOG_BUFFER_HEX_LEVEL(LOG_TAG,  outputArray, (uint16_t)size,
    //ESP_LOG_ERROR);

    // 2 Second source of randomness. Add hardware-level uniqueness.
    uint8_t mac[6];
    if (esp_efuse_mac_get_default(mac) == ESP_OK) {
        // XOR the MAC address with the first 6 bytes of the random data for hardware uniqueness.
        for (size_t i = 0; i < sizeof(mac) && i < size; i++) {
            outputArray[i] ^= mac[i];
        }
  //  ESP_LOG_BUFFER_HEX_LEVEL(LOG_TAG,  outputArray, (uint16_t)size,
  //   ESP_LOG_ERROR);
    } else {
      
    ESP_LOGE(LOG_TAG, "Failed to get MAC address for uniqueness.");

    }

    //3 Third source of randomness. System up time
    // Add modest entropy via current time hashed with the collected random data
    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);
    mbedtls_sha256_starts_ret(&ctx, 0); // Use 0 for SHA-256, 1 for SHA-224

    // Convert current time to a string and hash it together with the random data
    char timeString[20];
    snprintf(timeString, 20, "%llu", (long long unsigned)esp_timer_get_time());
    //ESP_LOGE(LOG_TAG, "Current time: %s", timeString);
    mbedtls_sha256_update_ret(&ctx, (const unsigned char *)timeString, strlen(timeString));
    mbedtls_sha256_update_ret(&ctx, outputArray, size);

    unsigned char hash[32]; // SHA-256 produces a 32 byte hash
    mbedtls_sha256_finish_ret(&ctx, hash);
    mbedtls_sha256_free(&ctx);
    memcpy(outputArray, hash, 32);
}
