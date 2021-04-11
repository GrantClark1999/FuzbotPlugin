// https://github.com/bakkesmodorg/BakkesModLoadoutLib/blob/master/BakkesModLoadoutLib
#pragma once

#include <stdint.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "BM.h"
#include "BitReader.h"

#define CURRENT_LOADOUT_VERSION 2

class BMCodeReader : public BitReader<uint8_t> {
 public:
  static BM::Teams Read(std::string code);

 private:
  BMCodeReader(std::string code) : BitReader<uint8_t>(code){};

  bool IsValid(std::string code, BM::Header header);
  BM::Header ReadHeader();

  BM::Teams ReadTeams();
  std::vector<BM::Item> ReadItems();
  BM::Item ReadItem();
  std::string ReadRGB();
  BM::Color ReadColor();
};