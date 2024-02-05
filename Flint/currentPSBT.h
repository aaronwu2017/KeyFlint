
#ifndef CURRENT_PSBT_H
#define CURRENT_PSBT_H

#include "PSBT.h"
#include "ur-encoder.hpp"
#include <memory>
#include <string>
//
#include <Arduino.h>
#include <assert.h> 
#include "crc32.h"
#include "xoshiro256.hpp"
#include "utils.hpp"
#include "random-sampler.hpp"
#include "fountain-encoder.hpp"
#include "fountain-utils.hpp"
#include "test-utils.hpp"
#include <vector>
#include <array>
#include <string>
#include <assert.h>
#include <algorithm>
//

class CurrentPSBT {
public:
    static CurrentPSBT& getInstance();

    CurrentPSBT(const CurrentPSBT&) = delete;
    CurrentPSBT& operator=(const CurrentPSBT&) = delete;
  void setPSBT(const PSBT& newPSBT);
    std::string getNextPart();
    PSBT getPSBT();
    void setStartExporting(bool value);
    bool getStartExporting() const;
    void setStartReceiving(bool value);
    bool getStartReceiving() const;
    void setEncoder(std::unique_ptr<ur::UREncoder> newEncoder);
    void setDecoder(std::unique_ptr<ur::URDecoder> newDecoder);
    double estimated_percent_complete() const;
    bool is_failure() const;

    void initializeEncoder(const ur::UR& ur, size_t max_fragment_len, uint32_t first_seq_num = 0, size_t min_fragment_len = 10);
     void receivePart(const std::string& part); // Method to receive a part and process it with the decoder.
    bool isDecodeSuccess() const; // Method to check if the decoding was successful.
    ur::UR getDecodedUR() const; // Method to get the decoded UR.
    ~CurrentPSBT();

private:
    std::unique_ptr<ur::UREncoder> encoder;
    std::unique_ptr<ur::URDecoder> decoder;
    bool startExporting;
    bool startReceiving;
    PSBT psbt;

    CurrentPSBT();
};

#endif // CURRENT_PSBT_H