#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "decoder.h"

DataItem *decode(uint8_t *byteArray) {
	DataItem *dataItem = (DataItem *)malloc(sizeof(DataItem));
	dataItem->header = *byteArray++;
	dataItem->extendedCount = 0;
	dataItem->payload = NULL;
	dataItem->array = NULL;
	dataItem->keys = NULL;
	dataItem->values = NULL;
	dataItem->content = NULL;
	dataItem->byteCount = 1;

	uint8_t shortCount = dataItemShortCount(dataItem);
	if(24 <= shortCount && shortCount <= 27) {
		int i;
		dataItem->extendedCount = 0x00;
		for(i = 0; i < exp2(shortCount - 24); i++) {
			dataItem->extendedCount = dataItem->extendedCount << 8 | *byteArray++;
			dataItem->byteCount++;
		}
	}

	uint64_t count = dataItemCount(dataItem);
	uint8_t majorType = dataItem->header >> 5;
	switch(majorType) {
		case UNSIGNED_INT: case NEGATIVE_INT:
		case SPECIAL:
			break;

		case BYTE_STRING: case UTF_8:
			dataItem->payload = (uint8_t *)malloc(sizeof(uint8_t) * count);
			memcpy(dataItem->payload, byteArray, count);
			byteArray += count;
			dataItem->byteCount += count;
			break;

		case ARRAY:
		{
			dataItem->array = (DataItem **)malloc(sizeof(DataItem *) * count);
			int i;
			for(i = 0; i < count; i++) {
				dataItem->array[i] = decode(byteArray);
				byteArray += dataItem->array[i]->byteCount;
				dataItem->byteCount += dataItem->array[i]->byteCount;
			}
			break;
		}
		
		case MAP:
		{
			dataItem->keys = (DataItem **)malloc(sizeof(DataItem *) * count);
			dataItem->values = (DataItem **)malloc(sizeof(DataItem *) * count);
			int i;
			for(i = 0; i < count; i++) {
				dataItem->keys[i] = decode(byteArray);
				byteArray += dataItem->keys[i]->byteCount;
				dataItem->byteCount += dataItem->keys[i]->byteCount;

				dataItem->values[i] = decode(byteArray);
				byteArray += dataItem->values[i]->byteCount;
				dataItem->byteCount += dataItem->values[i]->byteCount;
			}
			break;
		}

		case TAG:
		{
			DataItem *tagContent = decode(byteArray);
			dataItem->content = tagContent;
			dataItem->byteCount += tagContent->byteCount;
			byteArray += tagContent->byteCount;
			break;
		}
	}

	return dataItem;
}
