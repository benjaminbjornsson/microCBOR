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
	DataItem* unsignedIntegerZeroItem = decode(unsignedIntegerZeroCbor);
	DataItem* unsignedIntegerOneItem = decode(unsignedIntegerOneCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(unsignedIntegerZeroItem, unsignedIntegerOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(unsignedIntegerOneItem, unsignedIntegerZeroItem));
}

TEST(dataItemLessThanOrEqualTest, keyLessThanOrEqualNegativeInteger) {
	DataItem* negativeIntegerMinusOneItem = decode(negativeIntegerMinusOneCbor);
	DataItem* negativeIntegerMinusTwoItem = decode(negativeIntegerMinusTwoCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(negativeIntegerMinusTwoItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(negativeIntegerMinusOneItem, negativeIntegerMinusTwoItem));
}

TEST(dataItemLessThanOrEqualTest, keyLessThanOrEqualUnsignedNegativeInteger) {
	DataItem* unsignedIntegerZeroItem = decode(unsignedIntegerZeroCbor);
	DataItem* negativeIntegerMinusOneItem = decode(negativeIntegerMinusOneCbor);

	EXPECT_TRUE(dataItemLessThanOrEqual(unsignedIntegerZeroItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemLessThanOrEqual(negativeIntegerMinusOneItem, unsignedIntegerZeroItem));
}
