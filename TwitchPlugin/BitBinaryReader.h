// https://github.com/bakkesmodorg/BakkesModLoadoutLib/blob/master/BakkesModLoadoutLib
#pragma once
#include <stdint.h>

#include <vector>

#include "base64.h"

template <typename A>
class BitBinaryReader {
 public:
  const int type_size = sizeof(A) * 8;
  int current_bit = 0;
  A* buffer;

  BitBinaryReader(std::string hexString) {
    std::vector<BYTE> decodedVector = base64_decode_bytearr(hexString);
    // std::string decoded = base64_decode(hexString);
    // const char* data = decoded.c_str();
    buffer = (A*)malloc(decodedVector.size());
    memcpy(buffer, &decodedVector[0], decodedVector.size());
  }

  BitBinaryReader(A* inBuf) { buffer = inBuf; }

  ~BitBinaryReader() { delete buffer; }

  template <typename T>
  T ReadBits(int useLSBcount = sizeof(T) * 8) {
    T t = 0;
    for (int i = 0; i < useLSBcount; i++) {
      t |= ((buffer[current_bit / type_size] >> (current_bit % type_size)) & 1) << i;
      current_bit++;
    }
    return t;
  }
  uint8_t CalculateCRC(int startByte, int endByte) {
    uint8_t crc = 0b11111111;
    for (int i = startByte; i < endByte; i++) {
      crc = crc ^ buffer[i];
    }
    return crc;
  }
  bool VerifyCRC(uint8_t crc, int startByte, int endByte) { return (crc ^ CalculateCRC(startByte, endByte)) == 0; }

  bool ReadBool() { return ReadBits<bool>(1) & 1; }
};