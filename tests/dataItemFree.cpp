#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
	#include "dataitem.h"
}

namespace dataItemFreeTest {

uint8_t unsignedIntegerCbor[] = { 0x14 };	// 20
uint8_t negativeIntegerCbor[] = { 0x2B };	// -12
uint8_t utf8StringCbor[] = { 0x42, 0x78, 0x79 };	// h'7879'
uint8_t byteStringCbor[] = { 0x62, 0x78, 0x79 };	// "xy"
uint8_t arrayCbor[] = { 0x83, 0x01, 0x02, 0x03 };   // [1, 2, 3]
uint8_t mapCbor[] = { 0xA3, 0x01, 0x61, 0x61, 0x02, 0x61, 0x62, 0x03, 0x61, 0x63 };   // { 1: "a", 2: "b", 3: "c" }
uint8_t tagCbor[] = { 0xC0, 0x00 };	// 0(0)
uint8_t specialCbor[] = { 0xF4 };	// false

TEST(dataItemFreeTest, dataItemFree) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8StringItem = decode(utf8StringCbor);
	DataItem *byteStringItem = decode(byteStringCbor);
	DataItem *arrayItem = decode(arrayCbor);
	DataItem *mapItem = decode(mapCbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);

    dataItemFree(unsignedIntegerItem);
    dataItemFree(negativeIntegerItem);
    dataItemFree(utf8StringItem);
    dataItemFree(byteStringItem);
    dataItemFree(arrayItem);
    dataItemFree(mapItem);
    dataItemFree(tagItem);
    dataItemFree(specialItem);
}

}