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
#include <stdlib.h>
#include <math.h>
#include "encoder.h"

uint8_t *encode(DataItem *dataItem) {
	uint8_t *cbor = (uint8_t *)malloc(sizeof(uint8_t) * dataItemByteCount(dataItem));
	uint8_t *cborPtr = cbor;

	*cborPtr++ = dataItem->header;

	uint8_t shortCount = dataItemShortCount(dataItem);
	if(24 <= shortCount && shortCount <= 27) {
		uint8_t extendedBytes = exp2(shortCount - 24);
		for(uint64_t i = 0; i < extendedBytes; i++) {
			uint64_t shiftCount = ((extendedBytes - 1 - i) * 8);
			uint64_t mask = (uint64_t)0xFF << shiftCount;
			*cborPtr++ = (dataItem->extendedCount & mask) >> shiftCount;
		}
	}

	uint64_t count = dataItemCount(dataItem);
	switch(dataItemMajorType(dataItem)) {
		case UNSIGNED_INT: case SPECIAL:
		case NEGATIVE_INT:
			break;

		case BYTE_STRING: case UTF_8:
		{
			for(uint64_t i = 0; i < count; i++) {
				*cborPtr++ = dataItem->payload[i];
			}
			break;
		}

		case ARRAY:
		{	
			for(uint64_t i = 0; i < count; i++) {
				uint8_t *item = encode(dataItem->array[i]);
				uint8_t *itemPtr = item;
				for(uint64_t j = 0; j < dataItemByteCount(dataItem->array[i]); j++) {
					*cborPtr++ = *itemPtr++;
				}
				free(item);
			}
			break;
		}
		
		case MAP:
		{
			for(uint64_t i = 0; i < count; i++) {
				uint8_t *key = encode(dataItem->keys[i]);
				uint8_t *keyPtr = key;
				for(uint64_t j = 0; j < dataItemByteCount(dataItem->keys[i]); j++) {
					*cborPtr++ = *keyPtr++;
				}
				free(key);

				uint8_t *value = encode(dataItem->values[i]);
				uint8_t *valuePtr = value;
				for(uint64_t j = 0; j < dataItemByteCount(dataItem->values[i]); j++) {
					*cborPtr++ = *valuePtr++;
				}
				free(value);
			}
			break;
		}

		case TAG:
		{
			uint8_t *content = encode(dataItem->content);
			uint8_t *contentPtr = content;
			for(uint64_t i = 0; i < dataItemByteCount(dataItem->content); i++) {
				*cborPtr++ = *contentPtr++;
			}
			free(content);
			break;
		}
	}
	return cbor;
}
