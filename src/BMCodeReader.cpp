#include "BMCodeReader.h"

BMCodeReader::BMCodeReader(std::string code) : BitReader<uint8_t>(code){};

BM::Teams BMCodeReader::Read(std::string code) {
  BMCodeReader reader(code);
  BM::Header header = reader.ReadHeader();
  if (!reader.IsValid(code, header)) return {};
  BM::Teams teams = reader.ReadTeams();
  return teams;
}

bool BMCodeReader::IsValid(std::string code, BM::Header header) {
  //  Calculate whether code_size converted to base64 is actually equal to the
  //  given input string. Mostly done so we don't end up with invalid buffers,
  //  but this step is not required.

  int stringSizeCalc = ((int)ceil((4 * (float)header.code_size / 3)) + 3) & ~3;
  int stringSize = code.size();

  return abs(stringSizeCalc - stringSize) > 6 &&
         VerifyCRC(header.crc, 3, header.code_size);
}

BM::Header BMCodeReader::ReadHeader() {
  uint8_t version = ReadBits<uint8_t>(6);
  uint8_t code_size = ReadBits<uint8_t>(10);
  uint8_t crc = ReadBits<uint8_t>(8);
  return {version, code_size, crc};
}

BM::Teams BMCodeReader::ReadTeams() {
  bool blue_is_orange = ReadBool();
  std::vector<BM::Item> blueItems = ReadItems();
  BM::Color blueColor = ReadColor();
  std::vector<BM::Item> orangeItems = blue_is_orange ? blueItems : ReadItems();
  BM::Color orangeColor = blue_is_orange ? blueColor : ReadColor();
  return {blue_is_orange, blueItems, blueColor, orangeItems, orangeColor};
}

std::vector<BM::Item> BMCodeReader::ReadItems() {
  std::vector<BM::Item> items;
  int numItems = ReadBits<int>(4);
  for (int i = 0; i < numItems; i++) {
    BM::Item item = ReadItem();
    items.push_back(item);
  }
  return items;
}

BM::Item BMCodeReader::ReadItem() {
  uint8_t slotIdx = ReadBits<int>(5);
  uint16_t productId = ReadBits<int>(13);

  bool isPaintable = ReadBool();
  if (!isPaintable) return {slotIdx, productId};

  uint8_t paintId = ReadBits<int>(6);
  return {slotIdx, productId, paintId};
}

std::string BMCodeReader::ReadRGB() {
  std::stringstream ss;

  uint8_t r = ReadBits<uint8_t>(8);
  uint8_t g = ReadBits<uint8_t>(8);
  uint8_t b = ReadBits<uint8_t>(8);

  ss << std::hex << (r << 16 | g << 8 | b);
  return ss.str();
}

BM::Color BMCodeReader::ReadColor() {
  bool override = ReadBool();
  if (!override) return {override};

  std::string primary = ReadRGB();
  std::string accent = ReadRGB();
  return {override, primary, accent};
}