#include <gtest/gtest.h>

extern "C" {
	#include "decoder.h"
	#include "dataitem.h"
}

uint8_t unsignedIntegerZeroCbor[] = { 0x00 };
uint8_t unsignedIntegerOneCbor[] = { 0x01 };

uint8_t negativeIntegerMinusOneCbor[] = { 0x20 };
uint8_t negativeIntegerMinusTwoCbor[] = { 0x21 };

TEST(dataItemLessThanOrEqualTest, keyLessThanOrEqualUnsignedInteger) {
	DataItem* unsignedIntegerZeroItem = microCBORDecode(unsignedIntegerZeroCbor);
	DataItem* unsignedIntegerOneItem = microCBORDecode(unsignedIntegerOneCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(unsignedIntegerZeroItem, unsignedIntegerOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(unsignedIntegerOneItem, unsignedIntegerZeroItem));
}

TEST(dataItemLessThanOrEqualTest, keyLessThanOrEqualNegativeInteger) {
	DataItem* negativeIntegerMinusOneItem = microCBORDecode(negativeIntegerMinusOneCbor);
	DataItem* negativeIntegerMinusTwoItem = microCBORDecode(negativeIntegerMinusTwoCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(negativeIntegerMinusTwoItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(negativeIntegerMinusOneItem, negativeIntegerMinusTwoItem));
}

TEST(dataItemLessThanOrEqualTest, keyLessThanOrEqualUnsignedNegativeInteger) {
	DataItem* unsignedIntegerZeroItem = microCBORDecode(unsignedIntegerZeroCbor);
	DataItem* negativeIntegerMinusOneItem = microCBORDecode(negativeIntegerMinusOneCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(unsignedIntegerZeroItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(negativeIntegerMinusOneItem, unsignedIntegerZeroItem));
}
