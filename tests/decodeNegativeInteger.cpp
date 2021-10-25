#include <gtest/gtest.h>

extern "C" {
    #include "decoder.h"
}

namespace negativeInteger {

#define FIRST_LOWER_LIMIT   (uint64_t)0x0000000000000000
#define FIRST_MIDDLE        (uint64_t)0x0000000000000000
#define FIRST_UPPER_LIMIT   (uint64_t)0x0000000000000000
#define FIRST_BYTE_COUNT    (uint64_t)1

#define SECOND_HEADER       (uint8_t)0x38
#define SECOND_LOWER_LIMIT  (uint64_t)0x0000000000000018
#define SECOND_MIDDLE       (uint64_t)0x0000000000000073
#define SECOND_UPPER_LIMIT  (uint64_t)0x00000000000000FF
#define SECOND_BYTE_COUNT   (uint64_t)2

#define THIRD_HEADER        (uint8_t)0x39
#define THIRD_LOWER_LIMIT   (uint64_t)0x0000000000000100
#define THIRD_MIDDLE        (uint64_t)0x0000000000007F7F
#define THIRD_UPPER_LIMIT   (uint64_t)0x000000000000FFFF
#define THIRD_BYTE_COUNT    (uint64_t)3

#define FORTH_HEADER        (uint8_t)0x3A
#define FORTH_LOWER_LIMIT   (uint64_t)0x0000000000010000
#define FORTH_MIDDLE        (uint64_t)0x000000007FFF7FFF
#define FORTH_UPPER_LIMIT   (uint64_t)0x00000000FFFFFFFF
#define FORTH_BYTE_COUNT    (uint64_t)5

#define FIFTH_HEADER        (uint8_t)0x3B
#define FIFTH_LOWER_LIMIT   (uint64_t)0x0000000100000000
#define FIFTH_MIDDLE        (uint64_t)0x7FFFFFFF7FFFFFFF
#define FIFTH_UPPER_LIMIT   (uint64_t)0xFFFFFFFFFFFFFFFF
#define FIFTH_BYTE_COUNT    (uint64_t)9

uint8_t firstLowerLimitCbor[]	= { 0x20 };
uint8_t firstMiddleCbor[]		= { 0x2A };
uint8_t firstUpperLimitCbor[]	= { 0x37 };

uint8_t secondLowerLimitCbor[]	= { 0x38, 0x18 };
uint8_t secondMiddleCbor[]		= { 0x38, 0x73 };
uint8_t secondUpperLimitCbor[]	= { 0x38, 0xFF };

uint8_t thirdLowerLimitCbor[]	= { 0x39, 0x01, 0x00 };
uint8_t thirdMiddleCbor[]		= { 0x39, 0x7F, 0x7F };
uint8_t thirdUpperLimitCbor[]	= { 0x39, 0xFF, 0xFF };

uint8_t forthLowerLimitCbor[]	= { 0x3A, 0x00, 0x01, 0x00, 0x00 };
uint8_t forthMiddleCbor[]		= { 0x3A, 0x7F, 0xFF, 0x7F, 0xFF };
uint8_t forthUpperLimitCbor[]	= { 0x3A, 0xFF, 0xFF, 0xFF, 0xFF };

uint8_t fifthLowerLimitCbor[]	= { 0x3B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
uint8_t fifthMiddleCbor[]		= { 0x3B, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF };
uint8_t fifthUpperLimitCbor[]	= { 0x3B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/*
################################################################
	Region 1: (-1)-(-)
################################################################
*/

/* ########## First Lower: 0x00 ########## */
TEST(negativeIntegerTest, firstLowerLimit) {
	DataItem *firstLowerLimitItem = decode(firstLowerLimitCbor);
    EXPECT_EQ(firstLowerLimitItem->header, firstLowerLimitCbor[0]);
    EXPECT_EQ(firstLowerLimitItem->byteCount, FIRST_BYTE_COUNT);
}

/* ########## First Lower: 0x0B ########## */
TEST(negativeIntegerTest, firstMiddle) {
	DataItem *firstMiddleItem = decode(firstMiddleCbor);
    EXPECT_EQ(firstMiddleItem->header, firstMiddleCbor[0]);
    EXPECT_EQ(firstMiddleItem->byteCount, FIRST_BYTE_COUNT);
}

/* ########## First Lower: 0x17 ########## */
TEST(negativeIntegerTest, firstUpperLimit) {
	DataItem *firstUpperLimitItem = decode(firstUpperLimitCbor);
    EXPECT_EQ(firstUpperLimitItem->header, firstUpperLimitCbor[0]);
    EXPECT_EQ(firstUpperLimitItem->byteCount, FIRST_BYTE_COUNT);
}

/*
################################################################
    Region 2: 0x18-0xFF
################################################################
*/

/* ########## Second Lower: 0x18 ########## */
TEST(negativeIntegerTest, secondLowerLimit) {
	DataItem *secondLowerLimitItem = decode(secondLowerLimitCbor);
    EXPECT_EQ(secondLowerLimitItem->header, secondLowerLimitCbor[0]);
    EXPECT_EQ(secondLowerLimitItem->extendedCount, SECOND_LOWER_LIMIT);
    EXPECT_EQ(secondLowerLimitItem->byteCount, SECOND_BYTE_COUNT);
}

/* ########## Second Middle: 0x74 ########## */
TEST(negativeIntegerTest, secondMiddle) {
	DataItem *secondMiddleItem = decode(secondMiddleCbor);
    EXPECT_EQ(secondMiddleItem->header, secondMiddleCbor[0]);
    EXPECT_EQ(secondMiddleItem->extendedCount, SECOND_MIDDLE);
    EXPECT_EQ(secondMiddleItem->byteCount, SECOND_BYTE_COUNT);
}

/* ########## Second Upper: 0xFF ########## */
TEST(negativeIntegerTest, secondUpperLimit) {
	DataItem *secondUpperLimitItem = decode(secondUpperLimitCbor);
    EXPECT_EQ(secondUpperLimitItem->header, secondUpperLimitCbor[0]);
    EXPECT_EQ(secondUpperLimitItem->extendedCount, SECOND_UPPER_LIMIT);
    EXPECT_EQ(secondUpperLimitItem->byteCount, SECOND_BYTE_COUNT);
}

/*
################################################################
    Region 3: 0x0100-0xFFFF
################################################################
*/

/* ########## Third Lower: 0x0100 ########## */
TEST(negativeIntegerTest, thirdLowerLimit) {
	DataItem *thirdLowerLimitItem = decode(thirdLowerLimitCbor);
    EXPECT_EQ(thirdLowerLimitItem->header, thirdLowerLimitCbor[0]);
    EXPECT_EQ(thirdLowerLimitItem->extendedCount, THIRD_LOWER_LIMIT);
    EXPECT_EQ(thirdLowerLimitItem->byteCount, THIRD_BYTE_COUNT);
}

/* ########## Third Middle: 0x7F7F ########## */
TEST(negativeIntegerTest, thirdMiddle) {
	DataItem *thirdMiddleItem = decode(thirdMiddleCbor);
    EXPECT_EQ(thirdMiddleItem->header, thirdMiddleCbor[0]);
    EXPECT_EQ(thirdMiddleItem->extendedCount, THIRD_MIDDLE);
    EXPECT_EQ(thirdMiddleItem->byteCount, THIRD_BYTE_COUNT);
}

/* ########## Third Upper: 0xFFFF ########## */
TEST(negativeIntegerTest, thirdUpperLimit) {
	DataItem *thirdUpperLimitItem = decode(thirdUpperLimitCbor);
    EXPECT_EQ(thirdUpperLimitItem->header, thirdUpperLimitCbor[0]);
    EXPECT_EQ(thirdUpperLimitItem->extendedCount, THIRD_UPPER_LIMIT);
    EXPECT_EQ(thirdUpperLimitItem->byteCount, THIRD_BYTE_COUNT);
}

/*
################################################################
    Region 4: 0x0001_0000-0xFFFF_FFFF
################################################################
*/

/* ########## Forth Lower: 0x0001_0000 ########## */
TEST(negativeIntegerTest, forthLowerLimit) {
	DataItem *forthLowerLimitItem = decode(forthLowerLimitCbor);
    EXPECT_EQ(forthLowerLimitItem->header, forthLowerLimitCbor[0]);
    EXPECT_EQ(forthLowerLimitItem->extendedCount, FORTH_LOWER_LIMIT);
    EXPECT_EQ(forthLowerLimitItem->byteCount, FORTH_BYTE_COUNT);
}

/* ########## Forth Middle: 0x7FFF_7FFF ########## */
TEST(negativeIntegerTest, forthMiddle) {
	DataItem *forthMiddleItem = decode(forthMiddleCbor);
    EXPECT_EQ(forthMiddleItem->header, forthMiddleCbor[0]);
    EXPECT_EQ(forthMiddleItem->extendedCount, FORTH_MIDDLE);
    EXPECT_EQ(forthMiddleItem->byteCount, FORTH_BYTE_COUNT);
}

/* ########## Forth Upper: 0xFFFF_FFFF ########## */
TEST(negativeIntegerTest, forthUpperLimit) {
	DataItem *forthUpperLimitItem = decode(forthUpperLimitCbor);
    EXPECT_EQ(forthUpperLimitItem->header, forthUpperLimitCbor[0]);
    EXPECT_EQ(forthUpperLimitItem->extendedCount, FORTH_UPPER_LIMIT);
    EXPECT_EQ(forthUpperLimitItem->byteCount, FORTH_BYTE_COUNT);
}

/*
################################################################
    Region 5: 0x0000_0001_0000_0000-0xFFFF_FFFF_FFFF_FFFF
################################################################
*/

/* ########## Fifth Lower: 0x0000_0001_0000_0000 ########## */
TEST(negativeIntegerTest, fifthLowerLimit) {
	DataItem *fifthLowerLimitItem = decode(fifthLowerLimitCbor);
    EXPECT_EQ(fifthLowerLimitItem->header, fifthLowerLimitCbor[0]);
    EXPECT_EQ(fifthLowerLimitItem->extendedCount, FIFTH_LOWER_LIMIT);
    EXPECT_EQ(fifthLowerLimitItem->byteCount, FIFTH_BYTE_COUNT);
}

/* ########## Fifth Middle: 0x7FFF_FFFF_7FFF_FFFF ########## */
TEST(negativeIntegerTest, fifthMiddle) {
	DataItem *fifthMiddleItem = decode(fifthMiddleCbor);
    EXPECT_EQ(fifthMiddleItem->header, fifthMiddleCbor[0]);
    EXPECT_EQ(fifthMiddleItem->extendedCount, FIFTH_MIDDLE);
    EXPECT_EQ(fifthMiddleItem->byteCount, FIFTH_BYTE_COUNT);
}

/* ########## Fifth Upper: 0xFFFF_FFFF_FFFF_FFFF ########## */
TEST(negativeIntegerTest, fifthUpperLimit) {
	DataItem *fifthUpperLimitItem = decode(fifthUpperLimitCbor);
    EXPECT_EQ(fifthUpperLimitItem->header, fifthUpperLimitCbor[0]);
    EXPECT_EQ(fifthUpperLimitItem->extendedCount, FIFTH_UPPER_LIMIT);
    EXPECT_EQ(fifthUpperLimitItem->byteCount, FIFTH_BYTE_COUNT);
}

}