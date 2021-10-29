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

	uint8_t shortCount = dataItem->header & 0x1F;

	uint64_t count;
	if(24 <= shortCount && shortCount <= 27) {
		count = dataItem->extendedCount;
	} else {
		count = shortCount;
	}

	uint8_t *cbor = (uint8_t *)malloc(sizeof(uint8_t) * dataItemByteCount(dataItem));
	uint8_t *cbor_ptr = cbor;

	*cbor_ptr++ = dataItem->header;

	if(24 <= shortCount && shortCount <= 27) {
		uint8_t extendedBytes = exp2(shortCount - 24);
		for(int i = 0; i < extendedBytes; i++) {
			int shiftCount = ((extendedBytes - 1 - i) * 8);
			uint64_t mask = (uint64_t)0xFF << shiftCount;
			*cbor_ptr++ = (dataItem->extendedCount & mask) >> shiftCount;
		}
	}

	uint8_t majorType = dataItemMajorType(dataItem);
	switch(majorType) {
		case UNSIGNED_INT: case SPECIAL:
		case NEGATIVE_INT:
			break;

		case BYTE_STRING: case UTF_8:
		{
			for(int i = 0; i < count; i++) {
				*cbor_ptr++ = dataItem->payload[i];
			}
			break;
		}

		case ARRAY:
		{	
			for(int i = 0; i < count; i++) {
				uint8_t *item = encode(dataItem->array[i]);
				for(int j = 0; j < dataItemByteCount(dataItem->array[i]); j++) {
					*cbor_ptr++ = *item++;
				}
			}
			break;
		}
		
		case MAP:
		{
			for(int i = 0; i < count; i++) {
				uint8_t *key = encode(dataItem->keys[i]);
				for(int j = 0; j < dataItemByteCount(dataItem->keys[i]); j++) {
					*cbor_ptr++ = *key++;
				}

				uint8_t *value = encode(dataItem->values[i]);
				for(int j = 0; j < dataItemByteCount(dataItem->values[i]); j++) {
					*cbor_ptr++ = *value++;
				}
			}
			break;
		}

		case TAG:
		{
			DataItem *content = dataItem->content;
			uint8_t *contentCbor = encode(content);
			for(int i = 0; i < dataItemByteCount(content); i++) {
				*cbor_ptr++ = *contentCbor++;
			}
			break;
		}
	}
	return cbor;
}
