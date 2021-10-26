#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
}

uint8_t unsignedIntegerCbor[] = { 0x14 };
uint8_t negativeIntegerCbor[] = { 0x2B };
uint8_t utf8String1Cbor[] = { 0x42, 0x78, 0x79 };
uint8_t utf8String2Cbor[] = { 0x43, 0x61, 0x62, 0x63 };
uint8_t byteString1Cbor[] = { 0x62, 0x78, 0x79 };
uint8_t byteString2Cbor[] = { 0x63, 0x61, 0x62, 0x63 };
uint8_t tagCbor[] = { 0xC0, 0x00 };
uint8_t specialCbor[] = { 0xF4 };

uint8_t arrayCbor[] = { 0x80 };
uint8_t finalZeroToSevenCbor[]	= { 0x88, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 };
uint8_t finalSevenToZeroCbor[]	= { 0x88, 0xF4, 0xC0, 0x00, 0x63, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x42, 0x78, 0x79, 0x2B, 0x14 };
uint8_t finalRandomCbor[]		= { 0x88, 0x42, 0x78, 0x79, 0x14, 0xC0, 0x00, 0x43, 0x61, 0x62, 0x63, 0x63, 0x61, 0x62, 0x63, 0x2B, 0x62, 0x78, 0x79, 0xF4 };

TEST(dataItemInsertItemAtIndexTest, dataItemInsertItemAtIndexZeroToSeven) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);

	DataItem *arrayItem = decode(arrayCbor);
	dataItemInsertElementAtIndex(arrayItem, unsignedIntegerItem, 0);
	dataItemInsertElementAtIndex(arrayItem, negativeIntegerItem, 1);
	dataItemInsertElementAtIndex(arrayItem, utf8String1Item, 2);
	dataItemInsertElementAtIndex(arrayItem, utf8String2Item, 3);
	dataItemInsertElementAtIndex(arrayItem, byteString1Item, 4);
	dataItemInsertElementAtIndex(arrayItem, byteString2Item, 5);
	dataItemInsertElementAtIndex(arrayItem, tagItem, 6);
	dataItemInsertElementAtIndex(arrayItem, specialItem, 7);

	uint8_t *final = encode(arrayItem);
	for(int i = 0; i < sizeof(finalZeroToSevenCbor); i++) {
		EXPECT_EQ(final[i], finalZeroToSevenCbor[i]);
	}
}

TEST(dataItemInsertItemAtIndexTest, dataItemInsertItemAtIndexSevenToZero) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);

	DataItem *arrayItem = decode(arrayCbor);
	dataItemInsertElementAtIndex(arrayItem, unsignedIntegerItem, 0);
	dataItemInsertElementAtIndex(arrayItem, negativeIntegerItem, 0);
	dataItemInsertElementAtIndex(arrayItem, utf8String1Item, 0);
	dataItemInsertElementAtIndex(arrayItem, utf8String2Item, 0);
	dataItemInsertElementAtIndex(arrayItem, byteString1Item, 0);
	dataItemInsertElementAtIndex(arrayItem, byteString2Item, 0);
	dataItemInsertElementAtIndex(arrayItem, tagItem, 0);
	dataItemInsertElementAtIndex(arrayItem, specialItem, 0);

	uint8_t *final = encode(arrayItem);
	for(int i = 0; i < sizeof(finalSevenToZeroCbor); i++) {
		EXPECT_EQ(final[i], finalSevenToZeroCbor[i]);
	}
}

TEST(dataItemInsertItemAtIndexTest, dataItemInsertItemAtIndexRandom) {
	DataItem *unsignedIntegerItem = decode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = decode(negativeIntegerCbor);
	DataItem *utf8String1Item = decode(utf8String1Cbor);
	DataItem *utf8String2Item = decode(utf8String2Cbor);
	DataItem *byteString1Item = decode(byteString1Cbor);
	DataItem *byteString2Item = decode(byteString2Cbor);
	DataItem *tagItem = decode(tagCbor);
	DataItem *specialItem = decode(specialCbor);

	DataItem *arrayItem = decode(arrayCbor);
	dataItemInsertElementAtIndex(arrayItem, unsignedIntegerItem, 0);
	dataItemInsertElementAtIndex(arrayItem, negativeIntegerItem, 1);
	dataItemInsertElementAtIndex(arrayItem, utf8String1Item, 0);
	dataItemInsertElementAtIndex(arrayItem, utf8String2Item, 2);
	dataItemInsertElementAtIndex(arrayItem, byteString1Item, 4);
	dataItemInsertElementAtIndex(arrayItem, byteString2Item, 3);
	dataItemInsertElementAtIndex(arrayItem, tagItem, 2);
	dataItemInsertElementAtIndex(arrayItem, specialItem, 7);

	uint8_t *final = encode(arrayItem);
	for(int i = 0; i < sizeof(finalRandomCbor); i++) {
		EXPECT_EQ(final[i], finalRandomCbor[i]);
}
}