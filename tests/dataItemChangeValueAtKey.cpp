#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
	#include "decoder.h"
	#include "encoder.h"
	#include "dataitem.h"
	#include "utils.h"
}

namespace dataItemChangeValueAtKeyTest {

uint8_t mapCbor[]				= { 0xA4, 0x14, 0x2B, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }

uint8_t finalMap1Cbor[]				= { 0xA4, 0x14, 0x62, 0x78, 0x79, 0x42, 0x78, 0x79, 0x43, 0x61, 0x62, 0x63, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t finalMap2Cbor[]				= { 0xA4, 0x14, 0x62, 0x78, 0x79, 0x42, 0x78, 0x79, 0x62, 0x78, 0x79, 0x62, 0x78, 0x79, 0x63, 0x61, 0x62, 0x63, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t finalMap3Cbor[]				= { 0xA4, 0x14, 0x62, 0x78, 0x79, 0x42, 0x78, 0x79, 0x62, 0x78, 0x79, 0x62, 0x78, 0x79, 0x62, 0x78, 0x79, 0xC0, 0x00, 0xF4 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }
uint8_t finalMap4Cbor[]				= { 0xA4, 0x14, 0x62, 0x78, 0x79, 0x42, 0x78, 0x79, 0x62, 0x78, 0x79, 0x62, 0x78, 0x79, 0x62, 0x78, 0x79, 0xC0, 0x00, 0x62, 0x78, 0x79 }; // { 20 : -12, h'7879': h'616263', "xy": "abc", 0(0): false }


uint8_t key1Cbor[] = { 0x14 };
uint8_t key2Cbor[] = { 0x42, 0x78, 0x79 };
uint8_t key3Cbor[] = { 0x62, 0x78, 0x79 };
uint8_t key4Cbor[] = { 0xC0, 0x00 };

uint8_t valueCbor[] = { 0x62, 0x78, 0x79 };

uint8_t zeroMapCbor[] = { 0xA0 };

TEST(dataItemChangeValueAtKeyTest, dataItemChangeValueAtKeyTest) {
	DataItem *mapItem = decode(mapCbor);

	DataItem *key1Item = decode(key1Cbor);
	DataItem *key2Item = decode(key2Cbor);
	DataItem *key3Item = decode(key3Cbor);
	DataItem *key4Item = decode(key4Cbor);

	DataItem *valueItem = decode(valueCbor);
	
	dataItemChangeValueAtKey(mapItem, key1Item, valueItem);
	uint8_t *final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalMap1Cbor, dataItemCount(mapItem)));

	dataItemChangeValueAtKey(mapItem, key2Item, valueItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalMap2Cbor, dataItemCount(mapItem)));

	dataItemChangeValueAtKey(mapItem, key3Item, valueItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalMap3Cbor, dataItemCount(mapItem)));

	dataItemChangeValueAtKey(mapItem, key4Item, valueItem);
	final = encode(mapItem);
	EXPECT_TRUE(compareByteArray(final, finalMap4Cbor, dataItemCount(mapItem)));
}

}
