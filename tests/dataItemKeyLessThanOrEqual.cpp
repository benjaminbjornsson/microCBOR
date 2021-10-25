#include <gtest/gtest.h>

extern "C" {
	#include "decoder.h"
	#include "dataitem.h"
}

uint8_t unsignedIntegerZeroCbor[] = { 0x00 };
uint8_t unsignedIntegerOneCbor[] = { 0x01 };

uint8_t negativeIntegerMinusOneCbor[] = { 0x20 };
uint8_t negativeIntegerMinusTwoCbor[] = { 0x21 };

TEST(dataItemKeyLessThanOrEqualTest, keyLessThanOrEqualUnsignedInteger) {
	DataItem* unsignedIntegerZeroItem = decode(unsignedIntegerZeroCbor);
	DataItem* unsignedIntegerOneItem = decode(unsignedIntegerOneCbor);

	EXPECT_TRUE(dataItemKeyLessThanOrEqual(unsignedIntegerZeroItem, unsignedIntegerOneItem));
	EXPECT_FALSE(dataItemKeyLessThanOrEqual(unsignedIntegerOneItem, unsignedIntegerZeroItem));
}

TEST(dataItemKeyLessThanOrEqualTest, keyLessThanOrEqualNegativeInteger) {
	DataItem* negativeIntegerMinusOneItem = decode(negativeIntegerMinusOneCbor);
	DataItem* negativeIntegerMinusTwoItem = decode(negativeIntegerMinusTwoCbor);

	EXPECT_TRUE(dataItemKeyLessThanOrEqual(negativeIntegerMinusTwoItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemKeyLessThanOrEqual(negativeIntegerMinusOneItem, negativeIntegerMinusTwoItem));
}

TEST(dataItemKeyLessThanOrEqualTest, keyLessThanOrEqualUnsignedNegativeInteger) {
	DataItem* unsignedIntegerZeroItem = decode(unsignedIntegerZeroCbor);
	DataItem* negativeIntegerMinusOneItem = decode(negativeIntegerMinusOneCbor);

	EXPECT_TRUE(dataItemKeyLessThanOrEqual(unsignedIntegerZeroItem, negativeIntegerMinusOneItem));
	EXPECT_FALSE(dataItemKeyLessThanOrEqual(negativeIntegerMinusOneItem, unsignedIntegerZeroItem));
}
