#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
	#include "dataitem.h"
}

#define FIRST_LOWER_LIMIT   (uint64_t)0x0000000000000000
#define FIRST_MIDDLE        (uint64_t)0x000000000000000B
#define FIRST_UPPER_LIMIT   (uint64_t)0x0000000000000017
#define FIRST_BYTE_COUNT    (uint64_t)1

#define SECOND_HEADER       (uint8_t)0x18
#define SECOND_LOWER_LIMIT  (uint64_t)0x0000000000000018
#define SECOND_MIDDLE       (uint64_t)0x0000000000000073
#define SECOND_UPPER_LIMIT  (uint64_t)0x00000000000000FF
#define SECOND_BYTE_COUNT   (uint64_t)2

#define THIRD_HEADER        (uint8_t)0x19
#define THIRD_LOWER_LIMIT   (uint64_t)0x0000000000000100
#define THIRD_MIDDLE        (uint64_t)0x0000000000007F7F
#define THIRD_UPPER_LIMIT   (uint64_t)0x000000000000FFFF
#define THIRD_BYTE_COUNT    (uint64_t)3

#define FORTH_HEADER        (uint8_t)0x1A
#define FORTH_LOWER_LIMIT   (uint64_t)0x0000000000010000
#define FORTH_MIDDLE        (uint64_t)0x000000007FFF7FFF
#define FORTH_UPPER_LIMIT   (uint64_t)0x00000000FFFFFFFF
#define FORTH_BYTE_COUNT    (uint64_t)5

#define FIFTH_HEADER        (uint8_t)0x1B
#define FIFTH_LOWER_LIMIT   (uint64_t)0x0000000100000000
#define FIFTH_MIDDLE        (uint64_t)0x7FFFFFFF7FFFFFFF
#define FIFTH_UPPER_LIMIT   (uint64_t)0xFFFFFFFFFFFFFFFF
#define FIFTH_BYTE_COUNT    (uint64_t)9

namespace dataItemCountTest {

uint8_t firstLowerLimitCbor[]   = { 0x00 };
uint8_t firstMiddleCbor[]       = { 0x0B };
uint8_t firstUpperLimitCbor[]   = { 0x17 };

uint8_t secondLowerLimitCbor[]  = { 0x18, 0x18 };
uint8_t secondMiddleCbor[]      = { 0x18, 0x73 };
uint8_t secondUpperLimitCbor[]  = { 0x18, 0xFF };

uint8_t thirdLowerLimitCbor[]   = { 0x19, 0x01, 0x00 };
uint8_t thirdMiddleCbor[]       = { 0x19, 0x7F, 0x7F };
uint8_t thirdUpperLimitCbor[]   = { 0x19, 0xFF, 0xFF };

uint8_t forthLowerLimitCbor[]   = { 0x1A, 0x00, 0x01, 0x00, 0x00 };
uint8_t forthMiddleCbor[]       = { 0x1A, 0x7F, 0xFF, 0x7F, 0xFF };
uint8_t forthUpperLimitCbor[]   = { 0x1A, 0xFF, 0xFF, 0xFF, 0xFF };

uint8_t fifthLowerLimitCbor[]   = { 0x1B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
uint8_t fifthMiddleCbor[]       = { 0x1B, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF };
uint8_t fifthUpperLimitCbor[]   = { 0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

TEST(unsignedIntegerDataItemCountTest, firstRange) {
    DataItem *firstLowerLimitItem = decode(firstLowerLimitCbor);
    DataItem *firstMiddleItem = decode(firstMiddleCbor);
    DataItem *firstUpperLimitItem = decode(firstUpperLimitCbor);

	uint64_t count;
	count = dataItemCount(firstLowerLimitItem);
	EXPECT_EQ(count, FIRST_LOWER_LIMIT);

	count = dataItemCount(firstMiddleItem);
	EXPECT_EQ(count, FIRST_MIDDLE);

	count = dataItemCount(firstUpperLimitItem);
	EXPECT_EQ(count, FIRST_UPPER_LIMIT);
}

TEST(unsignedIntegerDataItemCountTest, secondRange) {
    DataItem *secondLowerLimitItem = decode(secondLowerLimitCbor);
    DataItem *secondMiddleItem = decode(secondMiddleCbor);
    DataItem *secondUpperLimitItem = decode(secondUpperLimitCbor);

	uint64_t count;
	count = dataItemCount(secondLowerLimitItem);
	EXPECT_EQ(count, SECOND_LOWER_LIMIT);

	count = dataItemCount(secondMiddleItem);
	EXPECT_EQ(count, SECOND_MIDDLE);

	count = dataItemCount(secondUpperLimitItem);
	EXPECT_EQ(count, SECOND_UPPER_LIMIT);
}

TEST(unsignedIntegerDataItemCountTest, thirdRange) {
    DataItem *thirdLowerLimitItem = decode(thirdLowerLimitCbor);
    DataItem *thirdMiddleItem = decode(thirdMiddleCbor);
    DataItem *thirdUpperLimitItem = decode(thirdUpperLimitCbor);

	uint64_t count;
	count = dataItemCount(thirdLowerLimitItem);
	EXPECT_EQ(count, THIRD_LOWER_LIMIT);

	count = dataItemCount(thirdMiddleItem);
	EXPECT_EQ(count, THIRD_MIDDLE);

	count = dataItemCount(thirdUpperLimitItem);
	EXPECT_EQ(count, THIRD_UPPER_LIMIT);
}

TEST(unsignedIntegerDataItemCountTest, forthRange) {
    DataItem *forthLowerLimitItem = decode(forthLowerLimitCbor);
    DataItem *forthMiddleItem = decode(forthMiddleCbor);
    DataItem *forthUpperLimitItem = decode(forthUpperLimitCbor);

	uint64_t count;
	count = dataItemCount(forthLowerLimitItem);
	EXPECT_EQ(count, FORTH_LOWER_LIMIT);

	count = dataItemCount(forthMiddleItem);
	EXPECT_EQ(count, FORTH_MIDDLE);

	count = dataItemCount(forthUpperLimitItem);
	EXPECT_EQ(count, FORTH_UPPER_LIMIT);
}

TEST(unsignedIntegerDataItemCountTest, fifthRange) {
    DataItem *fifthLowerLimitItem = decode(fifthLowerLimitCbor);
    DataItem *fifthMiddleItem = decode(fifthMiddleCbor);
    DataItem *fifthUpperLimitItem = decode(fifthUpperLimitCbor);

	uint64_t count;
	count = dataItemCount(fifthLowerLimitItem);
	EXPECT_EQ(count, FIFTH_LOWER_LIMIT);

	count = dataItemCount(fifthMiddleItem);
	EXPECT_EQ(count, FIFTH_MIDDLE);

	count = dataItemCount(fifthUpperLimitItem);
	EXPECT_EQ(count, FIFTH_UPPER_LIMIT);
}

}
