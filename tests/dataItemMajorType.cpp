#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
	#include "dataitem.h"
}

namespace dataItemMajorTypeTest {

uint8_t unsignedIntegerCbor[]   = { 0x00 };
uint8_t negativeIntegerCbor[]   = { 0x01 };
uint8_t byteArrayCbor[]   = { 0x02 };
uint8_t utf8Cbor[]   = { 0x03 };
uint8_t arrayCbor[]   = { 0x04 };
uint8_t mapCbor[]   = { 0x05 };
uint8_t tagCbor[]   = { 0x06 };
uint8_t specialCbor[]   = { 0x07 };

TEST(DataItemMajorTypeTest, majorType) {
	DataItem *unsignedIntegerItem = microCBORDecode(unsignedIntegerCbor);
	DataItem *negativeIntegerItem = microCBORDecode(negativeIntegerCbor);
	DataItem *byteArrayItem = microCBORDecode(byteArrayCbor);
	DataItem *utf8Item = microCBORDecode(utf8Cbor);
	DataItem *arrayItem = microCBORDecode(arrayCbor);
	DataItem *mapItem = microCBORDecode(mapCbor);
	DataItem *tagItem = microCBORDecode(tagCbor);
	DataItem *specialItem = microCBORDecode(specialCbor);
}

}
