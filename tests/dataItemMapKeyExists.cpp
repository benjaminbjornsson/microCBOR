#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
	#include "utils.h"
}

uint8_t map1Cbor[]	= { 0xA4, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t map2Cbor[]	= { 0xA3, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263', "xy": "abc" }
uint8_t map3Cbor[]	= { 0xA2, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263' }
uint8_t map4Cbor[]	= { 0xA1, 0x14, 0x2B }; // { 20 : -12 }
uint8_t emptyMapCbor[] = { 0xA0 };

uint8_t key1Cbor[] = { 0x14 };
uint8_t key2Cbor[] = { 0x42, 0x78, 0x79 };
uint8_t key3Cbor[] = { 0x62, 0x78, 0x79 };
uint8_t key4Cbor[] = { 0xC0, 0x00 };

TEST(dataItemMapIndexOfKeyTest, dataItemExistsTest) {
	DataItem *map1Item = microCBORDecode(map1Cbor);
	DataItem *map2Item = microCBORDecode(map2Cbor);
	DataItem *map3Item = microCBORDecode(map3Cbor);
	DataItem *map4Item = microCBORDecode(map4Cbor);
	DataItem *map5Item = microCBORDecode(emptyMapCbor);
	DataItem *keyItem;
	
	keyItem = microCBORDecode(key1Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map1Item, keyItem), 0);
	free(keyItem);

	keyItem = microCBORDecode(key2Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map1Item, keyItem), 1);
	free(keyItem);

	keyItem = microCBORDecode(key3Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map1Item, keyItem), 2);
	free(keyItem);

	keyItem = microCBORDecode(key4Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map1Item, keyItem), 3);
	free(keyItem);

	
	keyItem = microCBORDecode(key1Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map2Item, keyItem), 0);
	free(keyItem);

	keyItem = microCBORDecode(key2Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map2Item, keyItem), 1);
	free(keyItem);

	keyItem = microCBORDecode(key3Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map2Item, keyItem), 2);
	free(keyItem);

	keyItem = microCBORDecode(key4Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map2Item, keyItem), -1);
	free(keyItem);


	keyItem = microCBORDecode(key1Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map3Item, keyItem), 0);
	free(keyItem);

	keyItem = microCBORDecode(key2Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map3Item, keyItem), 1);
	free(keyItem);

	keyItem = microCBORDecode(key3Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map3Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key4Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map3Item, keyItem), -1);
	free(keyItem);

	
	keyItem = microCBORDecode(key1Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map4Item, keyItem), 0);
	free(keyItem);

	keyItem = microCBORDecode(key2Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map4Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key3Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map4Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key4Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map4Item, keyItem), -1);
	free(keyItem);

	
	keyItem = microCBORDecode(key1Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map5Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key2Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map5Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key3Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map5Item, keyItem), -1);
	free(keyItem);

	keyItem = microCBORDecode(key4Cbor);
	EXPECT_EQ(dataItemMapIndexOfKey(map5Item, keyItem), -1);
	free(keyItem);
}
