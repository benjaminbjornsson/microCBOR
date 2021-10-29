/*
 * Copyright 2021 Benjamin Björnsson
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

	uint8_t shortCount = dataItemShortCount(dataItem);
	if(24 <= shortCount && shortCount <= 27) {
		dataItem->extendedCount = 0x00;
		for(uint64_t i = 0; i < exp2(shortCount - 24); i++) {
			dataItem->extendedCount = dataItem->extendedCount << 8 | *byteArray++;
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
			break;

		case ARRAY:
		{
			dataItem->array = (DataItem **)malloc(sizeof(DataItem *) * count);
			uint64_t i;
			for(i = 0; i < count; i++) {
				dataItem->array[i] = decode(byteArray);
				byteArray += dataItemByteCount(dataItem->array[i]);
			}
			break;
		}
		
		case MAP:
		{
			dataItem->keys = (DataItem **)malloc(sizeof(DataItem *) * count);
			dataItem->values = (DataItem **)malloc(sizeof(DataItem *) * count);
			uint64_t i;
			for(i = 0; i < count; i++) {
				dataItem->keys[i] = decode(byteArray);
				byteArray += dataItemByteCount(dataItem->keys[i]);

				dataItem->values[i] = decode(byteArray);
				byteArray += dataItemByteCount(dataItem->values[i]);
			}
			break;
		}

		case TAG:
		{
			DataItem *tagContent = decode(byteArray);
			dataItem->content = tagContent;
			byteArray += dataItemByteCount(tagContent);
			break;
		}
	}

	return dataItem;
}
