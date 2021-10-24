#include <stdio.h>

#include "unsignedInteger.h"
#include "decoder.h"
#include "dataitem.h"

#define	FIRST_LOWER_LIMIT	(uint64_t)0x0000000000000000
#define	FIRST_MIDDLE		(uint64_t)0x000000000000000B
#define FIRST_UPPER_LIMIT	(uint64_t)0x0000000000000017

#define SECOND_HEADER		(uint8_t)0x18
#define	SECOND_LOWER_LIMIT	(uint64_t)0x0000000000000018
#define	SECOND_MIDDLE		(uint64_t)0x0000000000000073
#define SECOND_UPPER_LIMIT	(uint64_t)0x00000000000000FF

#define THIRD_HEADER		(uint8_t)0x19
#define	THIRD_LOWER_LIMIT	(uint64_t)0x0000000000000100
#define	THIRD_MIDDLE		(uint64_t)0x0000000000007F7F
#define THIRD_UPPER_LIMIT	(uint64_t)0x000000000000FFFF

#define FORTH_HEADER		(uint8_t)0x1A
#define	FORTH_LOWER_LIMIT	(uint64_t)0x0000000000010000
#define	FORTH_MIDDLE		(uint64_t)0x000000007FFF7FFF
#define FORTH_UPPER_LIMIT	(uint64_t)0x00000000FFFFFFFF

#define FIFTH_HEADER		(uint8_t)0x1B
#define	FIFTH_LOWER_LIMIT	(uint64_t)0x0000000100000000
#define	FIFTH_MIDDLE		(uint64_t)0x7FFFFFFF7FFFFFFF
#define FIFTH_UPPER_LIMIT	(uint64_t)0xFFFFFFFFFFFFFFFF

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

bool encodeUnsignedInteger() {
	/*	################################################################
		Region 1: 0x00-0x17
		################################################################ */

	// #### First Lower: 0x00 ####
	DataItem *firstLowerLimitItem = decode(firstLowerLimitCbor);
	if(firstLowerLimitItem->header != firstLowerLimitCbor[0]) {
		printf("encodeUnsignedInteger: firstLowerLimitItem->header should be 0x00\n");
		return false;
	}

	if(firstLowerLimitItem->byteCount != 1) {
		printf("encodeUnsignedInteger: firstLowerLimitItem->byteCount should be 1\n");
		return false;
	}

	// #### First Lower: 0x0B ####
	DataItem *firstMiddleItem = decode(firstMiddleCbor);
	if(firstMiddleItem->header != firstMiddleCbor[0]) {
		printf("encodeUnsignedInteger: firstMiddleItem->header should be 0x0D\n");
		return false;
	}

	if(firstMiddleItem->byteCount != 1) {
		printf("encodeUnsignedInteger: firstMiddleItem->byteCount should be 1\n");
		return false;
	}

	// #### First Lower: 0x17 ####
	DataItem *firstUpperLimitItem = decode(firstUpperLimitCbor);
	if(firstUpperLimitItem->header != firstUpperLimitCbor[0]) {
		printf("encodeUnsignedInteger: firstUpperLimitItem->header should be 0x17\n");
		return false;
	}

	if(firstUpperLimitItem->byteCount != 1) {
		printf("encodeUnsignedInteger: firstUpperLimitItem->byteCount should be 1\n");
		return false;
	}

	/*	################################################################
		Region 2: 0x18-0xFF
		################################################################ */

	// #### Second Lower: 0x18 ####
	DataItem *secondLowerLimitItem = decode(secondLowerLimitCbor);
	if(secondLowerLimitItem->header != SECOND_HEADER) {
		printf("encodeUnsignedInteger: secondLowerLimitItem->header should be %02X\n", SECOND_HEADER);
		return false;
	}

	if(secondLowerLimitItem->extendedCount != SECOND_LOWER_LIMIT) {
		printf("encodeUnsignedInteger: secondLowerLimitItem->extendedCount should be %016llX\n", SECOND_LOWER_LIMIT);
		return false;
	}

	if(secondLowerLimitItem->byteCount != 2) {
		printf("encodeUnsignedInteger: secondLowerLimitItem->byteCount should be 1\n");
		return false;
	}

	// #### Second Middle: 0x74 ####
	DataItem *secondMiddleItem = decode(secondMiddleCbor);
	if(secondMiddleItem->header != SECOND_HEADER) {
		printf("encodeUnsignedInteger: secondMiddleItem->header should be %02X\n", SECOND_HEADER);
		return false;
	}

	if(secondMiddleItem->extendedCount != SECOND_MIDDLE) {
		printf("encodeUnsignedInteger: secondLowerLimitItem->extendedCount should be %016llX\n", SECOND_MIDDLE);
		return false;
	}

	if(secondMiddleItem->byteCount != 2) {
		printf("encodeUnsignedInteger: secondMiddleItem->byteCount should be 2\n");
		return false;
	}

	// #### Second Upper: 0xFF ####
	DataItem *secondUpperLimitItem = decode(secondUpperLimitCbor);
	if(secondUpperLimitItem->header != SECOND_HEADER) {
		printf("encodeUnsignedInteger: secondUpperLimitItem->header should be 0x17\n");
		return false;
	}

	if(secondUpperLimitItem->extendedCount != SECOND_UPPER_LIMIT) {
		printf("encodeUnsignedInteger: secondLowerLimitItem->extendedCount should be %016llX\n", SECOND_UPPER_LIMIT);
		return false;
	}

	if(secondUpperLimitItem->byteCount != 2) {
		printf("encodeUnsignedInteger: secondUpperLimitItem->byteCount should be 1\n");
		return false;
	}

	/*	################################################################
		Region 3: 0x0100-0xFFFF
		################################################################ */

	// #### Third Lower: 0x0100 ####
	DataItem *thirdLowerLimitItem = decode(thirdLowerLimitCbor);
	if(thirdLowerLimitItem->header != THIRD_HEADER) {
		printf("encodeUnsignedInteger: thirdLowerLimitItem->header should be %02X\n", THIRD_HEADER);
		return false;
	}

	if(thirdLowerLimitItem->extendedCount != THIRD_LOWER_LIMIT) {
		printf("encodeUnsignedInteger: thirdLowerLimitItem->extendedCount should be %016llX\n", THIRD_LOWER_LIMIT);
		return false;
	}

	if(thirdLowerLimitItem->byteCount != 3) {
		printf("encodeUnsignedInteger: thirdLowerLimitItem->byteCount should be 4\n");
		return false;
	}

	// #### Third Middle: 0x7F7F ####
	DataItem *thirdMiddleItem = decode(thirdMiddleCbor);
	if(thirdMiddleItem->header != THIRD_HEADER) {
		printf("encodeUnsignedInteger: thirdMiddleItem->header should be %02X\n", THIRD_HEADER);
		return false;
	}

	if(thirdMiddleItem->extendedCount != THIRD_MIDDLE) {
		printf("encodeUnsignedInteger: thirdLowerLimitItem->extendedCount should be %016llX\n", THIRD_MIDDLE);
		return false;
	}

	if(thirdMiddleItem->byteCount != 3) {
		printf("encodeUnsignedInteger: thirdMiddleItem->byteCount should be 4\n");
		return false;
	}

	// #### Second Upper: 0xFFFF ####
	DataItem *thirdUpperLimitItem = decode(thirdUpperLimitCbor);
	if(thirdUpperLimitItem->header != THIRD_HEADER) {
		printf("encodeUnsignedInteger: thirdUpperLimitItem->header should be %02X\n", THIRD_HEADER);
		return false;
	}

	if(thirdUpperLimitItem->extendedCount != THIRD_UPPER_LIMIT) {
		printf("encodeUnsignedInteger: thirdUpperLimitItem->extendedCount should be %016llX\n", THIRD_UPPER_LIMIT);
		return false;
	}

	if(thirdUpperLimitItem->byteCount != 3) {
		printf("encodeUnsignedInteger: thirdUpperLimitItem->byteCount should be 4\n");
		return false;
	}

	/*	################################################################
		Region 4: 0x0001_0000-0xFFFF_FFFF
		################################################################	*/

	// #### Forth Lower: 0x0001_0000 ####
	DataItem *forthLowerLimitItem = decode(forthLowerLimitCbor);
	if(forthLowerLimitItem->header != FORTH_HEADER) {
		printf("encodeUnsignedInteger: forthLowerLimitItem->header should be %02X\n", FORTH_HEADER);
		return false;
	}

	if(forthLowerLimitItem->extendedCount != FORTH_LOWER_LIMIT) {
		printf("encodeUnsignedInteger: forthLowerLimitItem->extendedCount should be %016llX\n", FORTH_LOWER_LIMIT);
		return false;
	}

	if(forthLowerLimitItem->byteCount != 5) {
		printf("encodeUnsignedInteger: forthLowerLimitItem->byteCount should be 4\n");
		return false;
	}

	// #### Forth Middle: 0x7FFF_7FFF ####
	DataItem *forthMiddleItem = decode(forthMiddleCbor);
	if(forthMiddleItem->header != FORTH_HEADER) {
		printf("encodeUnsignedInteger: forthMiddleItem->header should be %02X\n", FORTH_HEADER);
		return false;
	}

	if(forthMiddleItem->extendedCount != FORTH_MIDDLE) {
		printf("encodeUnsignedInteger: forthLowerLimitItem->extendedCount should be %016llX\n", FORTH_MIDDLE);
		return false;
	}

	if(forthMiddleItem->byteCount != 5) {
		printf("encodeUnsignedInteger: forthMiddleItem->byteCount should be 4\n");
		return false;
	}

	// #### Forth Upper: 0xFFFF_FFFF ####
	DataItem *forthUpperLimitItem = decode(forthUpperLimitCbor);
	if(forthUpperLimitItem->header != FORTH_HEADER) {
		printf("encodeUnsignedInteger: forthUpperLimitItem->header should be %02X\n", FORTH_HEADER);
		return false;
	}

	if(forthUpperLimitItem->extendedCount != FORTH_UPPER_LIMIT) {
		printf("encodeUnsignedInteger: forthUpperLimitItem->extendedCount should be %016llX\n", FORTH_UPPER_LIMIT);
		return false;
	}

	if(forthUpperLimitItem->byteCount != 5) {
		printf("encodeUnsignedInteger: forthUpperLimitItem->byteCount should be 4\n");
		return false;
	}

	/*	################################################################
		Region 5: 0x0000_0001_0000_0000-0xFFFF_FFFF_FFFF_FFFF
		################################################################	*/

	// #### Fifth Lower: 0x0000_0001_0000_0000 ####
	DataItem *fifthLowerLimitItem = decode(fifthLowerLimitCbor);
	if(fifthLowerLimitItem->header != FIFTH_HEADER) {
		printf("encodeUnsignedInteger: fifthLowerLimitItem->header should be %02X\n", FIFTH_HEADER);
		return false;
	}

	if(fifthLowerLimitItem->extendedCount != FIFTH_LOWER_LIMIT) {
		printf("encodeUnsignedInteger: fifthLowerLimitItem->extendedCount should be %016llX\n", FIFTH_LOWER_LIMIT);
		return false;
	}

	if(fifthLowerLimitItem->byteCount != 9) {
		printf("encodeUnsignedInteger: fifthLowerLimitItem->byteCount should be 4\n");
		return false;
	}

	// ##### Fifth Middle: 0x7FFF_FFFF_7FFF_FFFF #####
	DataItem *fifthMiddleItem = decode(fifthMiddleCbor);
	if(fifthMiddleItem->header != FIFTH_HEADER) {
		printf("encodeUnsignedInteger: fifthMiddleItem->header should be %02X\n", FIFTH_HEADER);
		return false;
	}

	if(fifthMiddleItem->extendedCount != FIFTH_MIDDLE) {
		printf("encodeUnsignedInteger: fifthLowerLimitItem->extendedCount should be %016llX\n", FIFTH_MIDDLE);
		return false;
	}

	if(fifthMiddleItem->byteCount != 9) {
		printf("encodeUnsignedInteger: fifthMiddleItem->byteCount should be 4\n");
		return false;
	}

	// ##### Fifth Upper: 0xFFFF_FFFF_FFFF_FFFF #####
	DataItem *fifthUpperLimitItem = decode(fifthUpperLimitCbor);
	if(fifthUpperLimitItem->header != FIFTH_HEADER) {
		printf("encodeUnsignedInteger: fifthUpperLimitItem->header should be %02X\n", FIFTH_HEADER);
		return false;
	}

	if(fifthUpperLimitItem->extendedCount != FIFTH_UPPER_LIMIT) {
		printf("encodeUnsignedInteger: fifthUpperLimitItem->extendedCount should be %016llX\n", FIFTH_UPPER_LIMIT);
		return false;
	}

	if(fifthUpperLimitItem->byteCount != 9) {
		printf("encodeUnsignedInteger: fifthUpperLimitItem->byteCount should be 4\n");
		return false;
	}

	return true;
}
