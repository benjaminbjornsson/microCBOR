#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
}

namespace dataItemMapInsertKeyValueTest {

uint8_t unsignedIntegerCbor[] = { 0x14 };	// 20
uint8_t negativeIntegerCbor[] = { 0x2B };	// -12
uint8_t utf8String1Cbor[] = { 0x42, 0x78, 0x79 };	// h'7879'
uint8_t utf8String2Cbor[] = { 0x43, 0x61, 0x62, 0x63 };	// h'616263'
uint8_t byteString1Cbor[] = { 0x62, 0x78, 0x79 };	// "xy"
uint8_t byteString2Cbor[] = { 0x63, 0x61, 0x62, 0x63 };	// "abc"
uint8_t tagCbor[] = { 0xC0, 0x00 };	// 0(0)
uint8_t specialCbor[] = { 0xF4 };	// false

uint8_t mapCbor[] = { 0xA0 };	// {}
uint8_t finalMapCbor1[]	= { 0xA4, 0x14, 0x42, 0x78, 0x79, 0x2B, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : h'7879', -12 : h'616263', "xy" : "abc", 0(0) : false }
uint8_t finalMapCbor2[]	= { 0xA4, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12 , h'7879' : h'616263', "xy" : "abc", 0(0) : false }

TEST(dataItemMapInsertKeyValueTest, dataItemMapInsertKeyValue) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);
	
	DataItem *mapItem = decode(mapCbor);
	dataItemMapInsertKeyValue(mapItem, unsignedIntegerItem, utf8String1Item);
	dataItemMapInsertKeyValue(mapItem, negativeIntegerItem, utf8String2Item);
	dataItemMapInsertKeyValue(mapItem, byteString1Item, byteString2Item);
	dataItemMapInsertKeyValue(mapItem, tagItem, specialItem);

	uint8_t *finalCbor = encode(mapItem);

	for(int i = 0; i < sizeof(finalMapCbor1); i++) {
		EXPECT_EQ(finalCbor[i], finalMapCbor1[i]);
	}
}

TEST(dataItemMapInsertKeyValueTest, dataItemMapInsertKeyValueReverse) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);
	
	DataItem *mapItem = decode(mapCbor);
	dataItemMapInsertKeyValue(mapItem, tagItem, specialItem);
	dataItemMapInsertKeyValue(mapItem, byteString1Item, byteString2Item);
	dataItemMapInsertKeyValue(mapItem, negativeIntegerItem, utf8String2Item);
	dataItemMapInsertKeyValue(mapItem, unsignedIntegerItem, utf8String1Item);

	uint8_t *finalCbor = encode(mapItem);

	for(int i = 0; i < sizeof(finalMapCbor1); i++) {
		EXPECT_EQ(finalCbor[i], finalMapCbor1[i]);
	}
}

TEST(dataItemMapInsertKeyValueTest, dataItemMapInsertKeyValueByteStringAsKey) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);
	
	DataItem *mapItem = decode(mapCbor);
	dataItemMapInsertKeyValue(mapItem, unsignedIntegerItem, negativeIntegerItem);
	dataItemMapInsertKeyValue(mapItem, utf8String1Item, utf8String2Item);
	dataItemMapInsertKeyValue(mapItem, byteString1Item, byteString2Item);
	dataItemMapInsertKeyValue(mapItem, tagItem, specialItem);

	uint8_t *finalCbor = encode(mapItem);

	for(int i = 0; i < sizeof(finalMapCbor2); i++) {
		EXPECT_EQ(finalCbor[i], finalMapCbor2[i]);
	}
}

}