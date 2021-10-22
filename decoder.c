#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "decoder.h"

DataItem *decode(uint8_t *byteArray) {
	DataItem *dataItem = (DataItem *)malloc(sizeof(DataItem));
	dataItem->header = *byteArray++;
	dataItem->byteCount = 1;

	uint8_t shortCount = dataItem->header & 0x1F;
	if(24 <= shortCount && shortCount <= 27) {
		int i;
		dataItem->extendedCount = 0x00;
		for(i = 0; i < exp2(shortCount - 24); i++) {
			dataItem->extendedCount = dataItem->extendedCount << 8 | *byteArray++;
			dataItem->byteCount++;
		}
	}

	uint64_t count;
	if(24 <= shortCount && shortCount <= 27) {
		count = dataItem->extendedCount;
	} else {
		count = shortCount;
	}

	uint8_t majorType = dataItem->header >> 5;
	switch(majorType) {
		case UNSIGNED_INT: case SPECIAL:
		case NEGATIVE_INT: case TAG:
			printf("INT");
			break;

		case BYTE_STRING: case UTF_8:
			printf("STRING\n");
			dataItem->payload = byteArray;
			byteArray += count;
			dataItem->byteCount += count;
			break;

		case ARRAY:
		{
			printf("ARRAY\n");
			dataItem->array = (DataItem **)malloc(sizeof(DataItem *) * count);
			int i;
			for(i = 0; i < count; i++) {
				dataItem->array[i] = decode(byteArray);
				byteArray += dataItem->array[i]->byteCount;
			}
			break;
		}
		
		case MAP:
		{
			printf("MAP\n");
			dataItem->keys = (DataItem **)malloc(sizeof(DataItem *) * count);
			dataItem->values = (DataItem **)malloc(sizeof(DataItem *) * count);
			int i;
			for(i = 0; i < count; i++) {
				dataItem->keys[i] = decode(byteArray);
				byteArray += dataItem->keys[i]->byteCount;
				dataItem->values[i] = decode(byteArray);
				byteArray += dataItem->values[i]->byteCount;
			}
			break;
		}
	}

	return dataItem;
}
