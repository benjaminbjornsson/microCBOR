#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
	#include "utils.h"
}

namespace dataItemRemoveKeyValueAtKeyTest {

uint8_t mapCbor[]				= { 0xA4, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }

uint8_t finalFourToZero1Cbor[]	= { 0xA3, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263', "xy": "abc" }
uint8_t finalFourToZero2Cbor[]	= { 0xA2, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263' }
uint8_t finalFourToZero3Cbor[]	= { 0xA1, 0x14, 0x2B }; // { 20 : -12 }

uint8_t finalZero1Cbor[]		= { 0xA3, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t finalZero2Cbor[]		= { 0xA2, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { "xy": "abc", 0(0): false }
uint8_t finalZero3Cbor[]		= { 0xA1, 0xC0, 0x00, 0xF4 }; // { 0(0): false }

uint8_t finalRandom1Cbor[]		= { 0xA3, 0x14, 0x2B, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, "xy": "abc", 0(0): false }
uint8_t finalRandom2Cbor[]		= { 0xA2, 0x14, 0x2B, 0xC0, 0x00, 0xF4 }; // { 20 : -12, 0(0): false }
uint8_t finalRandom3Cbor[]		= { 0xA1, 0x14, 0x2B }; // { 20 : -12 }

uint8_t key1Cbor[] = { 0x14 };
uint8_t key2Cbor[] = { 0x42, 0x78, 0x79 };
uint8_t key3Cbor[] = { 0x62, 0x78, 0x79 };
uint8_t key4Cbor[] = { 0xC0, 0x00 };

uint8_t zeroMapCbor[] = { 0xA0 };

TEST(dataItemRemoveKeyValueAtKeyTest, dataItemRemoveKeyValueAtKeyFourToZero) {
	DataItem *mapItem = decode(mapCbor);
	DataItem *keyItem;
	uint8_t *final;
	
	keyItem = decode(key4Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalFourToZero1Cbor, sizeof(finalFourToZero1Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalFourToZero1Cbor));
	free(keyItem);

	keyItem = decode(key3Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalFourToZero2Cbor, sizeof(finalFourToZero2Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalFourToZero2Cbor));
	free(keyItem);

	keyItem = decode(key2Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalFourToZero3Cbor, sizeof(finalFourToZero3Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalFourToZero3Cbor));
	free(keyItem);

	keyItem = decode(key1Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, zeroMapCbor, sizeof(zeroMapCbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(zeroMapCbor));
	free(keyItem);
}

TEST(dataItemRemoveKeyValueAtKeyTest, dataItemRemoveKeyValueAtKeyZero) {
	DataItem *mapItem = decode(mapCbor);
	DataItem *keyItem;
	uint8_t *final;

	keyItem = decode(key1Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalZero1Cbor, sizeof(finalZero1Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalZero1Cbor));
	free(keyItem);

	keyItem = decode(key2Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalZero2Cbor, sizeof(finalZero2Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalZero2Cbor));
	free(keyItem);

	keyItem = decode(key3Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalZero3Cbor, sizeof(finalZero3Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalZero3Cbor));
	free(keyItem);

	keyItem = decode(key4Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, zeroMapCbor, sizeof(zeroMapCbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(zeroMapCbor));
	free(keyItem);
}

TEST(dataItemRemoveKeyValueAtKeyTest, dataItemRemoveKeyValueAtKeyRandom) {
	DataItem *mapItem = decode(mapCbor);
	DataItem *keyItem;
	uint8_t *final;

	keyItem = decode(key2Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	dbg_buff_print(final, dataItemByteCount(mapItem));
	EXPECT_TRUE(compareByteArray(final, finalRandom1Cbor, sizeof(finalRandom1Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalRandom1Cbor));

	keyItem = decode(key3Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	dbg_buff_print(final, dataItemByteCount(mapItem));
	EXPECT_TRUE(compareByteArray(final, finalRandom2Cbor, sizeof(finalRandom2Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalRandom2Cbor));

	keyItem = decode(key4Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	dbg_buff_print(final, dataItemByteCount(mapItem));
	EXPECT_TRUE(compareByteArray(final, finalRandom3Cbor, sizeof(finalRandom3Cbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(finalRandom3Cbor));
	
	keyItem = decode(key1Cbor);
	dataItemRemoveKeyValueAtKey(mapItem, keyItem);
	final = encode(mapItem);
	dbg_buff_print(final, dataItemByteCount(mapItem));
	EXPECT_TRUE(compareByteArray(final, zeroMapCbor, sizeof(zeroMapCbor)));
	EXPECT_EQ(dataItemByteCount(mapItem), sizeof(zeroMapCbor));
}

}
