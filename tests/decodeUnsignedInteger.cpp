#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
}

namespace unsignedInteger {

#define FIRST_LOWER_LIMIT	(uint64_t)0x0000000000000000
#define	FIRST_MIDDLE		(uint64_t)0x000000000000000B
#define FIRST_UPPER_LIMIT	(uint64_t)0x0000000000000017
#define FIRST_BYTE_COUNT    (uint64_t)1

#define SECOND_HEADER		(uint8_t)0x18
#define	SECOND_LOWER_LIMIT	(uint64_t)0x0000000000000018
#define	SECOND_MIDDLE		(uint64_t)0x0000000000000073
#define SECOND_UPPER_LIMIT	(uint64_t)0x00000000000000FF
#define SECOND_BYTE_COUNT   (uint64_t)2

#define THIRD_HEADER		(uint8_t)0x19
#define	THIRD_LOWER_LIMIT	(uint64_t)0x0000000000000100
#define	THIRD_MIDDLE		(uint64_t)0x0000000000007F7F
#define THIRD_UPPER_LIMIT	(uint64_t)0x000000000000FFFF
#define THIRD_BYTE_COUNT    (uint64_t)3

#define FORTH_HEADER		(uint8_t)0x1A
#define	FORTH_LOWER_LIMIT	(uint64_t)0x0000000000010000
#define	FORTH_MIDDLE		(uint64_t)0x000000007FFF7FFF
#define FORTH_UPPER_LIMIT	(uint64_t)0x00000000FFFFFFFF
#define FORTH_BYTE_COUNT    (uint64_t)5

#define FIFTH_HEADER		(uint8_t)0x1B
#define	FIFTH_LOWER_LIMIT	(uint64_t)0x0000000100000000
#define	FIFTH_MIDDLE		(uint64_t)0x7FFFFFFF7FFFFFFF
#define FIFTH_UPPER_LIMIT	(uint64_t)0xFFFFFFFFFFFFFFFF
#define FIFTH_BYTE_COUNT    (uint64_t)9

uint8_t firstLowerLimitCbor[]	= { 0x00 };
uint8_t firstMiddleCbor[]		= { 0x0B };
uint8_t firstUpperLimitCbor[]	= { 0x17 };

uint8_t secondLowerLimitCbor[]	= { 0x18, 0x18 };
uint8_t secondMiddleCbor[]		= { 0x18, 0x73 };
uint8_t secondUpperLimitCbor[]	= { 0x18, 0xFF };

uint8_t thirdLowerLimitCbor[]	= { 0x19, 0x01, 0x00 };
uint8_t thirdMiddleCbor[]		= { 0x19, 0x7F, 0x7F };
uint8_t thirdUpperLimitCbor[]	= { 0x19, 0xFF, 0xFF };

uint8_t forthLowerLimitCbor[]	= { 0x1A, 0x00, 0x01, 0x00, 0x00 };
uint8_t forthMiddleCbor[]		= { 0x1A, 0x7F, 0xFF, 0x7F, 0xFF };
uint8_t forthUpperLimitCbor[]	= { 0x1A, 0xFF, 0xFF, 0xFF, 0xFF };

uint8_t fifthLowerLimitCbor[]	= { 0x1B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
uint8_t fifthMiddleCbor[]		= { 0x1B, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF };
uint8_t fifthUpperLimitCbor[]	= { 0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/*
################################################################
	Region 1: 0x00-0x17
################################################################
*/

/* ########## First Lower: 0x00 ########## */
TEST(unsignedIntegerTest, firstLowerLimit) {
	DataItem *firstLowerLimitItem = microCBORDecode(firstLowerLimitCbor);
    EXPECT_EQ(firstLowerLimitItem->header, firstLowerLimitCbor[0]);
    EXPECT_EQ(dataItemByteCount(firstLowerLimitItem), FIRST_BYTE_COUNT);
}

/* ########## First Lower: 0x0B ########## */
TEST(unsignedIntegerTest, firstMiddle) {
	DataItem *firstMiddleItem = microCBORDecode(firstMiddleCbor);
    EXPECT_EQ(firstMiddleItem->header, firstMiddleCbor[0]);
    EXPECT_EQ(dataItemByteCount(firstMiddleItem), FIRST_BYTE_COUNT);
}

/* ########## First Lower: 0x17 ########## */
TEST(unsignedIntegerTest, firstUpperLimit) {
	DataItem *firstUpperLimitItem = microCBORDecode(firstUpperLimitCbor);
    EXPECT_EQ(firstUpperLimitItem->header, firstUpperLimitCbor[0]);
    EXPECT_EQ(dataItemByteCount(firstUpperLimitItem), FIRST_BYTE_COUNT);
}

/*
################################################################
    Region 2: 0x18-0xFF
################################################################
*/

/* ########## Second Lower: 0x18 ########## */
TEST(unsignedIntegerTest, secondLowerLimit) {
	DataItem *secondLowerLimitItem = microCBORDecode(secondLowerLimitCbor);
    EXPECT_EQ(secondLowerLimitItem->header, secondLowerLimitCbor[0]);
    EXPECT_EQ(secondLowerLimitItem->extendedCount, SECOND_LOWER_LIMIT);
    EXPECT_EQ(dataItemByteCount(secondLowerLimitItem), SECOND_BYTE_COUNT);
}

/* ########## Second Middle: 0x74 ########## */
TEST(unsignedIntegerTest, secondMiddle) {
	DataItem *secondMiddleItem = microCBORDecode(secondMiddleCbor);
    EXPECT_EQ(secondMiddleItem->header, secondMiddleCbor[0]);
    EXPECT_EQ(secondMiddleItem->extendedCount, SECOND_MIDDLE);
    EXPECT_EQ(dataItemByteCount(secondMiddleItem), SECOND_BYTE_COUNT);
}

/* ########## Second Upper: 0xFF ########## */
TEST(unsignedIntegerTest, secondUpperLimit) {
	DataItem *secondUpperLimitItem = microCBORDecode(secondUpperLimitCbor);
    EXPECT_EQ(secondUpperLimitItem->header, secondUpperLimitCbor[0]);
    EXPECT_EQ(secondUpperLimitItem->extendedCount, SECOND_UPPER_LIMIT);
    EXPECT_EQ(dataItemByteCount(secondUpperLimitItem), SECOND_BYTE_COUNT);
}

/*
################################################################
    Region 3: 0x0100-0xFFFF
################################################################
*/

/* ########## Third Lower: 0x0100 ########## */
TEST(unsignedIntegerTest, thirdLowerLimit) {
	DataItem *thirdLowerLimitItem = microCBORDecode(thirdLowerLimitCbor);
    EXPECT_EQ(thirdLowerLimitItem->header, thirdLowerLimitCbor[0]);
    EXPECT_EQ(thirdLowerLimitItem->extendedCount, THIRD_LOWER_LIMIT);
    EXPECT_EQ(dataItemByteCount(thirdLowerLimitItem), THIRD_BYTE_COUNT);
}

/* ########## Third Middle: 0x7F7F ########## */
TEST(unsignedIntegerTest, thirdMiddle) {
	DataItem *thirdMiddleItem = microCBORDecode(thirdMiddleCbor);
    EXPECT_EQ(thirdMiddleItem->header, thirdMiddleCbor[0]);
    EXPECT_EQ(thirdMiddleItem->extendedCount, THIRD_MIDDLE);
    EXPECT_EQ(dataItemByteCount(thirdMiddleItem), THIRD_BYTE_COUNT);
}

/* ########## Third Upper: 0xFFFF ########## */
TEST(unsignedIntegerTest, thirdUpperLimit) {
	DataItem *thirdUpperLimitItem = microCBORDecode(thirdUpperLimitCbor);
    EXPECT_EQ(thirdUpperLimitItem->header, thirdUpperLimitCbor[0]);
    EXPECT_EQ(thirdUpperLimitItem->extendedCount, THIRD_UPPER_LIMIT);
    EXPECT_EQ(dataItemByteCount(thirdUpperLimitItem), THIRD_BYTE_COUNT);
}

/*
################################################################
    Region 4: 0x0001_0000-0xFFFF_FFFF
################################################################
*/

/* ########## Forth Lower: 0x0001_0000 ########## */
TEST(unsignedIntegerTest, forthLowerLimit) {
	DataItem *forthLowerLimitItem = microCBORDecode(forthLowerLimitCbor);
    EXPECT_EQ(forthLowerLimitItem->header, forthLowerLimitCbor[0]);
    EXPECT_EQ(forthLowerLimitItem->extendedCount, FORTH_LOWER_LIMIT);
    EXPECT_EQ(dataItemByteCount(forthLowerLimitItem), FORTH_BYTE_COUNT);
}

/* ########## Forth Middle: 0x7FFF_7FFF ########## */
TEST(unsignedIntegerTest, forthMiddle) {
	DataItem *forthMiddleItem = microCBORDecode(forthMiddleCbor);
    EXPECT_EQ(forthMiddleItem->header, forthMiddleCbor[0]);
    EXPECT_EQ(forthMiddleItem->extendedCount, FORTH_MIDDLE);
    EXPECT_EQ(dataItemByteCount(forthMiddleItem), FORTH_BYTE_COUNT);
}

/* ########## Forth Upper: 0xFFFF_FFFF ########## */
TEST(unsignedIntegerTest, forthUpperLimit) {
	DataItem *forthUpperLimitItem = microCBORDecode(forthUpperLimitCbor);
    EXPECT_EQ(forthUpperLimitItem->header, forthUpperLimitCbor[0]);
    EXPECT_EQ(forthUpperLimitItem->extendedCount, FORTH_UPPER_LIMIT);
    EXPECT_EQ(dataItemByteCount(forthUpperLimitItem), FORTH_BYTE_COUNT);
}

/*
################################################################
    Region 5: 0x0000_0001_0000_0000-0xFFFF_FFFF_FFFF_FFFF
################################################################
*/

/* ########## Fifth Lower: 0x0000_0001_0000_0000 ########## */
TEST(unsignedIntegerTest, fifthLowerLimit) {
	DataItem *fifthLowerLimitItem = microCBORDecode(fifthLowerLimitCbor);
    EXPECT_EQ(fifthLowerLimitItem->header, fifthLowerLimitCbor[0]);
    EXPECT_EQ(fifthLowerLimitItem->extendedCount, FIFTH_LOWER_LIMIT);
    EXPECT_EQ(dataItemByteCount(fifthLowerLimitItem), FIFTH_BYTE_COUNT);
}

/* ########## Fifth Middle: 0x7FFF_FFFF_7FFF_FFFF ########## */
TEST(unsignedIntegerTest, fifthMiddle) {
	DataItem *fifthMiddleItem = microCBORDecode(fifthMiddleCbor);
    EXPECT_EQ(fifthMiddleItem->header, fifthMiddleCbor[0]);
    EXPECT_EQ(fifthMiddleItem->extendedCount, FIFTH_MIDDLE);
    EXPECT_EQ(dataItemByteCount(fifthMiddleItem), FIFTH_BYTE_COUNT);
}

/* ########## Fifth Upper: 0xFFFF_FFFF_FFFF_FFFF ########## */
TEST(unsignedIntegerTest, fifthUpperLimit) {
	DataItem *fifthUpperLimitItem = microCBORDecode(fifthUpperLimitCbor);
    EXPECT_EQ(fifthUpperLimitItem->header, fifthUpperLimitCbor[0]);
    EXPECT_EQ(fifthUpperLimitItem->extendedCount, FIFTH_UPPER_LIMIT);
    EXPECT_EQ(dataItemByteCount(fifthUpperLimitItem), FIFTH_BYTE_COUNT);
}

}
