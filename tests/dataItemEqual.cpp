#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
	#include "dataitem.h"
}

namespace dataItemEqualTest {

uint8_t unsignedIntegerCbor[] = { 0x14 };	// 20
uint8_t negativeIntegerCbor[] = { 0x2B };	// -12
uint8_t utf8StringCbor[] = { 0x42, 0x78, 0x79 };	// h'7879'
uint8_t byteStringCbor[] = { 0x62, 0x78, 0x79 };	// "xy"
uint8_t arrayCbor[] = { 0x83, 0x01, 0x02, 0x03 };   // [1, 2, 3]
uint8_t mapCbor[] = { 0xA3, 0x01, 0x61, 0x61, 0x02, 0x61, 0x62, 0x03, 0x61, 0x63 };   // { 1: "a", 2: "b", 3: "c" }
uint8_t tagCbor[] = { 0xC0, 0x00 };	// 0(0)
uint8_t specialCbor[] = { 0xF4 };	// false

TEST(dataItemEqualTest, dataItemEqualTest) {
	DataItem *unsignedIntegerItem = microCBORDecode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = microCBORDecode(negativeIntegerCbor);
	DataItem *utf8StringItem = microCBORDecode(utf8StringCbor);
	DataItem *byteStringItem = microCBORDecode(byteStringCbor);
	DataItem *arrayItem = microCBORDecode(arrayCbor);
	DataItem *mapItem = microCBORDecode(mapCbor);
	DataItem *tagItem = microCBORDecode(tagCbor);
	DataItem *specialItem = microCBORDecode(specialCbor);

	DataItem *unsignedIntegerCopyItem = microCBORDecode(unsignedIntegerCbor);
	DataItem *negativeIntegerCopyItem = microCBORDecode(negativeIntegerCbor);
	DataItem *utf8StringCopyItem = microCBORDecode(utf8StringCbor);
	DataItem *byteStringCopyItem = microCBORDecode(byteStringCbor);
	DataItem *arrayCopyItem = microCBORDecode(arrayCbor);
	DataItem *mapCopyItem = microCBORDecode(mapCbor);
	DataItem *tagCopyItem = microCBORDecode(tagCbor);
	DataItem *specialCopyItem = microCBORDecode(specialCbor);

    EXPECT_TRUE(dataItemEqual(unsignedIntegerItem, unsignedIntegerCopyItem));
    EXPECT_TRUE(dataItemEqual(negativeIntegerItem, negativeIntegerCopyItem));
    EXPECT_TRUE(dataItemEqual(utf8StringItem, utf8StringCopyItem));
    EXPECT_TRUE(dataItemEqual(byteStringItem, byteStringCopyItem));
    EXPECT_TRUE(dataItemEqual(arrayItem, arrayCopyItem));
    EXPECT_TRUE(dataItemEqual(byteStringItem, byteStringCopyItem));
    EXPECT_TRUE(dataItemEqual(tagItem, tagCopyItem));
    EXPECT_TRUE(dataItemEqual(mapItem, mapCopyItem));
}

TEST(dataItemEqualTest, dataItemNotEqualTest) {
	DataItem *unsignedIntegerItem = microCBORDecode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = microCBORDecode(negativeIntegerCbor);
	DataItem *utf8StringItem = microCBORDecode(utf8StringCbor);
	DataItem *byteStringItem = microCBORDecode(byteStringCbor);
	DataItem *arrayItem = microCBORDecode(arrayCbor);
	DataItem *mapItem = microCBORDecode(mapCbor);
	DataItem *tagItem = microCBORDecode(tagCbor);
	DataItem *specialItem = microCBORDecode(specialCbor);

    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, negativeIntegerItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, utf8StringItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, byteStringItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, arrayItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, mapItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, tagItem));
    EXPECT_FALSE(dataItemEqual(unsignedIntegerItem, specialItem));

    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, utf8StringItem));
    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, byteStringItem));
    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, arrayItem));
    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, mapItem));
    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, tagItem));
    EXPECT_FALSE(dataItemEqual(negativeIntegerItem, specialItem));
    
    EXPECT_FALSE(dataItemEqual(utf8StringItem, byteStringItem));
    EXPECT_FALSE(dataItemEqual(utf8StringItem, arrayItem));
    EXPECT_FALSE(dataItemEqual(utf8StringItem, mapItem));
    EXPECT_FALSE(dataItemEqual(utf8StringItem, tagItem));
    EXPECT_FALSE(dataItemEqual(utf8StringItem, specialItem));
    
    EXPECT_FALSE(dataItemEqual(byteStringItem, arrayItem));
    EXPECT_FALSE(dataItemEqual(byteStringItem, mapItem));
    EXPECT_FALSE(dataItemEqual(byteStringItem, tagItem));
    EXPECT_FALSE(dataItemEqual(byteStringItem, specialItem));
    
    EXPECT_FALSE(dataItemEqual(arrayItem, mapItem));
    EXPECT_FALSE(dataItemEqual(arrayItem, tagItem));
    EXPECT_FALSE(dataItemEqual(arrayItem, specialItem));
    
    EXPECT_FALSE(dataItemEqual(mapItem, tagItem));
    EXPECT_FALSE(dataItemEqual(mapItem, specialItem));
    
    EXPECT_FALSE(dataItemEqual(tagItem, specialItem));
}

}