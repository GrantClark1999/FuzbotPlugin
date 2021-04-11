// //
// https://github.com/bakkesmodorg/BakkesModLoadoutLib/blob/master/BakkesModLoadoutLib
// #pragma once

// #include <stdint.h>

// #include <string>

// #include "BitReader.h"
// #include "Models.h"

// #define CURRENT_LOADOUT_VERSION 2

// using namespace std;

// class BMCodeReader : public BitReader<uint8_t> {
//  public:
//   static BMLoadout Read(string code) {
//     BMCodeReader reader(code);
//     Header header = reader.ReadHeader();
//     if (!reader.IsValid(code, header)) return {};
//     Body body = reader.ReadBody();
//     delete &reader;
//     return {header, body};
//   }

//   bool IsValid(string code, Header header) {
//     //  Calculate whether code_size converted to base64 is actually equal to
//     the
//     //  given input string. Mostly done so we don't end up with invalid
//     buffers,
//     //  but this step is not required.

//     int stringSizeCalc =
//         ((int)ceil((4 * (float)header.code_size / 3)) + 3) & ~3;
//     int stringSize = code.size();

//     return abs(stringSizeCalc - stringSize) > 6 &&
//            VerifyCRC(header.crc, 3, header.code_size);
//   }

//   Header ReadHeader() {
//     uint8_t version = ReadBits<uint8_t>(6);
//     uint8_t code_size = ReadBits<uint8_t>(10);
//     uint8_t crc = ReadBits<uint8_t>(8);
//     return {version, code_size, crc};
//   }

//   Body ReadBody() {
//     bool blue_is_orange = ReadBool();
//     OverrideLoadout blueLoadout = ReadLoadout();
//     OverrideColor blueColor = ReadColor();
//     OverrideLoadout orangeLoadout =
//         blue_is_orange ? blueLoadout : ReadLoadout();
//     OverrideColor orangeColor = blue_is_orange ? blueColor : ReadColor();
//     return {blue_is_orange, blueLoadout, blueColor, orangeLoadout,
//     orangeColor};
//   }

//   OverrideLoadout ReadLoadout() {
//     OverrideLoadout items;
//     int numItems = ReadBits<int>(4);
//     for (int i = 0; i < numItems; i++) {
//       Item item = ReadItem();
//       items.insert_or_assign(item.slot_index, item);
//     }
//     return items;
//   }

//   Item ReadItem() {
//     int slot_index = ReadBits<int>(5);
//     int product_id = ReadBits<int>(13);
//     Item item{slot_index, product_id};

//     bool isPaintable = ReadBool();
//     if (isPaintable) {
//       item.paint_index = ReadBits<int>(6);
//     }

//     return item;
//   }

//   unsigned long ReadRGB() {
//     uint8_t r = ReadBits<uint8_t>(8);
//     uint8_t g = ReadBits<uint8_t>(8);
//     uint8_t b = ReadBits<uint8_t>(8);
//     return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
//   }

//   OverrideColor ReadColor() {
//     bool override = ReadBool();
//     if (!override) return {override};

//     unsigned long primary = ReadRGB();
//     unsigned long accent = ReadRGB();
//     return {override, primary, accent};
//   }
// };