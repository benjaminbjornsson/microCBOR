#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
	#include "utils.h"
}

uint8_t map1Cbor[]				= { 0xA4, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t map2Cbor[]	= { 0xA3, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263', "xy": "abc" }
uint8_t map3Cbor[]	= { 0xA2, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63 }; // { 20 : -12, h'7879': h'616263' }
uint8_t map4Cbor[]	= { 0xA1, 0x14, 0x2B }; // { 20 : -12 }
uint8_t emptyMapCbor[] = { 0xA0 };

uint8_t key1Cbor[] = { 0x14 };
uint8_t key2Cbor[] = { 0x42, 0x78, 0x79 };
uint8_t key3Cbor[] = { 0x62, 0x78, 0x79 };
uint8_t key4Cbor[] = { 0xC0, 0x00 };

TEST(dataItemKeyExistsTest, dataItemExistsTest) {
	DataItem *map1Item = decode(map1Cbor);
	DataItem *map2Item = decode(map2Cbor);
	DataItem *map3Item = decode(map3Cbor);
	DataItem *map4Item = decode(map4Cbor);
	DataItem *map5Item = decode(emptyMapCbor);
	DataItem *keyItem;
	
	keyItem = decode(key1Cbor);
	EXPECT_TRUE(dataItemKeyExists(map1Item, keyItem));
	free(keyItem);

	keyItem = decode(key2Cbor);
	EXPECT_TRUE(dataItemKeyExists(map1Item, keyItem));
	free(keyItem);

	keyItem = decode(key3Cbor);
	EXPECT_TRUE(dataItemKeyExists(map1Item, keyItem));
	free(keyItem);

	keyItem = decode(key4Cbor);
	EXPECT_TRUE(dataItemKeyExists(map1Item, keyItem));
	free(keyItem);

	
	keyItem = decode(key1Cbor);
	EXPECT_TRUE(dataItemKeyExists(map2Item, keyItem));
	free(keyItem);

	keyItem = decode(key2Cbor);
	EXPECT_TRUE(dataItemKeyExists(map2Item, keyItem));
	free(keyItem);

	keyItem = decode(key3Cbor);
	EXPECT_TRUE(dataItemKeyExists(map2Item, keyItem));
	free(keyItem);

	keyItem = decode(key4Cbor);
	EXPECT_FALSE(dataItemKeyExists(map2Item, keyItem));
	free(keyItem);


	keyItem = decode(key1Cbor);
	EXPECT_TRUE(dataItemKeyExists(map3Item, keyItem));
	free(keyItem);

	keyItem = decode(key2Cbor);
	EXPECT_TRUE(dataItemKeyExists(map3Item, keyItem));
	free(keyItem);

	keyItem = decode(key3Cbor);
	EXPECT_FALSE(dataItemKeyExists(map3Item, keyItem));
	free(keyItem);

	keyItem = decode(key4Cbor);
	EXPECT_FALSE(dataItemKeyExists(map3Item, keyItem));
	free(keyItem);

	
	keyItem = decode(key1Cbor);
	EXPECT_TRUE(dataItemKeyExists(map4Item, keyItem));
	free(keyItem);

	keyItem = decode(key2Cbor);
	EXPECT_FALSE(dataItemKeyExists(map4Item, keyItem));
	free(keyItem);

	keyItem = decode(key3Cbor);
	EXPECT_FALSE(dataItemKeyExists(map4Item, keyItem));
	free(keyItem);

	keyItem = decode(key4Cbor);
	EXPECT_FALSE(dataItemKeyExists(map4Item, keyItem));
	free(keyItem);

	
	keyItem = decode(key1Cbor);
	EXPECT_FALSE(dataItemKeyExists(map5Item, keyItem));
	free(keyItem);

	keyItem = decode(key2Cbor);
	EXPECT_FALSE(dataItemKeyExists(map5Item, keyItem));
	free(keyItem);

	keyItem = decode(key3Cbor);
	EXPECT_FALSE(dataItemKeyExists(map5Item, keyItem));
	free(keyItem);

	keyItem = decode(key4Cbor);
	EXPECT_FALSE(dataItemKeyExists(map5Item, keyItem));
	free(keyItem);
}
