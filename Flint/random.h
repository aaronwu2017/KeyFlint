#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <stdint.h>
#include <stddef.h>

void esp32_random_collecting(uint8_t* outputArray, size_t size);

#endif // RANDOM_UTILS_H