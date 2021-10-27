#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
	#include "utils.h"
}

namespace dataItemRemoveItemAtIndexTest {

uint8_t arrayCbor[]				= { 0x88, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // [20, -12, h'7879', h'616263', "xy", "abc", 0(0), false]

uint8_t finalSixToZero6Cbor[]	= { 0x87, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00 }; // [20, -12, h'7879', h'616263', "xy", "abc", 0(0)]
uint8_t finalSixToZero5Cbor[]	= { 0x86, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63 }; // [20, -12, h'7879', h'616263', "xy", "abc"]
uint8_t finalSixToZero4Cbor[]	= { 0x85, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79 }; // [20, -12, h'7879', h'616263', "xy"]
uint8_t finalSixToZero3Cbor[]	= { 0x84, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63 }; // [20, -12, h'7879', h'616263']
uint8_t finalSixToZero2Cbor[]	= { 0x83, 0x14, 0x2B, 0x42, 0x78, 0x79 }; // [20, -12, h'7879']
uint8_t finalSixToZero1Cbor[]	= { 0x82, 0x14, 0x2B }; // [20, -12]
uint8_t finalSixToZero0Cbor[]	= { 0x81, 0x14 }; // [20]

uint8_t finalZero1Cbor[]		= { 0x87, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // [-12, h'7879', h'616263', "xy", "abc", 0(0), false]
uint8_t finalZero2Cbor[]		= { 0x86, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // [h'7879', h'616263', "xy", "abc", 0(0), false]
uint8_t finalZero3Cbor[]		= { 0x85, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // [h'616263', "xy", "abc", 0(0), false]
uint8_t finalZero4Cbor[]		= { 0x84, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // ["xy", "abc", 0(0), false]
uint8_t finalZero5Cbor[]		= { 0x83, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // ["abc", 0(0), false]
uint8_t finalZero6Cbor[]		= { 0x82, 0xC0, 0x00, 0xF4 }; // [0(0), false]
uint8_t finalZero7Cbor[]		= { 0x81, 0xF4 }; // [false]

uint8_t finalRandom1Cbor[]		= { 0x87, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xF4 }; // [20, -12, h'7879', h'616263', "xy", "abc", false]
uint8_t finalRandom2Cbor[]		= { 0x86, 0x14, 0x2B, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xF4 }; // [20, -12, h'616263', "xy", "abc", false]
uint8_t finalRandom3Cbor[]		= { 0x85, 0x14, 0x2B, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0xF4 }; // [20, -12, h'616263', "xy", false]
uint8_t finalRandom4Cbor[]		= { 0x84, 0x14, 0x2B, 0x43, 0x61, 0x62, 0x63, 0xF4 }; // [20, -12, h'616263', false]
uint8_t finalRandom5Cbor[]		= { 0x83, 0x14, 0x2B, 0xF4 }; // [20, -12, false]
uint8_t finalRandom6Cbor[]		= { 0x82, 0x14, 0xF4 }; // [20, false]
uint8_t finalRandom7Cbor[]		= { 0x81, 0x14 }; // [20]

uint8_t zeroArrayCbor[] = { 0x80 };

TEST(dataItemRemoveItemAtIndexTest, dataItemRemoveItemAtIndexSixToZero) {
	DataItem *arrayItem = decode(arrayCbor);
	uint8_t *final;
	
	dataItemRemoveElementAtIndex(arrayItem, 7);
	final = encode(arrayItem);
	dbg_buff_print(final, arrayItem->byteCount);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero6Cbor, sizeof(finalSixToZero6Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 6);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero5Cbor, sizeof(finalSixToZero5Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 5);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero4Cbor, sizeof(finalSixToZero4Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 4);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero3Cbor, sizeof(finalSixToZero3Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 3);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero2Cbor, sizeof(finalSixToZero2Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 2);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero1Cbor, sizeof(finalSixToZero1Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 1);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalSixToZero0Cbor, sizeof(finalSixToZero0Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, zeroArrayCbor, sizeof(zeroArrayCbor)));
}

TEST(dataItemRemoveItemAtIndexTest, dataItemRemoveItemAtIndexZero) {
	DataItem *arrayItem = decode(arrayCbor);
	uint8_t *final;

	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero1Cbor, sizeof(finalZero1Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero2Cbor, sizeof(finalZero2Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero3Cbor, sizeof(finalZero3Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero4Cbor, sizeof(finalZero4Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero5Cbor, sizeof(finalZero5Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero6Cbor, sizeof(finalZero6Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalZero7Cbor, sizeof(finalZero7Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, zeroArrayCbor, sizeof(zeroArrayCbor)));
}

TEST(dataItemRemoveItemAtIndexTest, dataItemRemoveItemAtIndexRandom) {
	DataItem *arrayItem = decode(arrayCbor);
	uint8_t *final;

	dataItemRemoveElementAtIndex(arrayItem, 6);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom1Cbor, sizeof(finalRandom1Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 2);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom2Cbor, sizeof(finalRandom2Cbor)));

	dataItemRemoveElementAtIndex(arrayItem, 4);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom3Cbor, sizeof(finalRandom3Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 3);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom4Cbor, sizeof(finalRandom4Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 2);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom5Cbor, sizeof(finalRandom5Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 1);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom6Cbor, sizeof(finalRandom6Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 1);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, finalRandom7Cbor, sizeof(finalRandom7Cbor)));
	
	dataItemRemoveElementAtIndex(arrayItem, 0);
	final = encode(arrayItem);
	EXPECT_TRUE(compareByteArray(final, zeroArrayCbor, sizeof(zeroArrayCbor)));
	
}

}