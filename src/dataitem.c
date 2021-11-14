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
#include <assert.h>
#include "dataitem.h"
#include "decoder.h"
#include "encoder.h"

#define	INVALID_INDEX	(0xFFFFFFFFFFFFFFFF)

/*
	#######################################
	Helper Functions
	#######################################
*/

uint64_t dataItemIndexOfItem(DataItem **array, DataItem *item, uint64_t count) {
	assert(array != NULL);
	assert(item != NULL);

	for(uint64_t i = 0; i < count; i++)	{
		assert(array[i] != NULL);
		if(dataItemEqual(item, array[i]))
			return i;
	}

	return INVALID_INDEX;
}

DataItem **dataItemInsertAtIndex(DataItem **dataItem, DataItem *element, uint64_t index, uint64_t length, uint8_t *err) {
	assert(dataItem != NULL);
	assert(element != NULL);
	assert(index <= length);

	DataItem *elementCopy = dataItemCopy(element);
	if(elementCopy == NULL) {
		*err = 1;
		return dataItem;
	}

	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (length + 1));

	newArray[index] = elementCopy;
	for(uint64_t i = 0; i < length; i++) {
		newArray[i >= index ? i + 1 : i] = dataItem[i];
	}

	free(dataItem);

	return newArray;
}

DataItem **dataItemRemoveAtIndex(DataItem **dataItem, uint64_t index, uint64_t length, uint8_t *err) {
	assert(dataItem != NULL);
	assert(index < length);

	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (length - 1));
	if(newArray == NULL) {
		*err = 1;
		return dataItem;
	}
	
	DataItem *element = NULL;
	for(uint64_t i = 0; i < length; i++) {
		if(i == index) {
			element = dataItem[i];
		} else {
			newArray[i > index ? i - 1 : i] = dataItem[i];
		}
	}

	dataItemFree(element);
	free(dataItem);

	return newArray;
}

uint64_t dataItemSetCount(DataItem *dataItem, uint64_t count) {
	assert(dataItem != NULL);

	uint8_t shortCount;
	if (0 <= count && count <= 23) {
		shortCount = count;
		dataItem->extendedCount = 0;
	} else if (24 <= count && count <= 0xFF) {
		shortCount = 24;
		dataItem->extendedCount = count;
	} else if (0x0100 <= count && count <= 0xFFFF) {
		shortCount = 25;
		dataItem->extendedCount = count;
	} else if (0x10000 <= count && count <= 0xFFFFFFFF) {
		shortCount = 26;
		dataItem->extendedCount = count;
	} else if (0x100000000 <= count && count <= 0xFFFFFFFFFFFFFFFF) {
		shortCount = 27;
		dataItem->extendedCount = count;
	}

	dataItem->header = (dataItem->header & 0xE0) | (shortCount & 0x1F);

	return count;
}

/*
	#######################################
	Generic Functions
	#######################################
*/

uint8_t dataItemMajorType(DataItem *dataItem) {
	assert(dataItem != NULL);

	return (dataItem->header >> 5);
}

uint8_t dataItemShortCount(DataItem *dataItem) {
	assert(dataItem != NULL);

	return (dataItem->header & 0x1F);
}

uint64_t dataItemCount(DataItem *dataItem) {
	assert(dataItem != NULL);

    uint8_t shortCount = dataItemShortCount(dataItem);
    if(24 <= shortCount && shortCount <= 27) {
        return dataItem->extendedCount;
    } else {
        return shortCount;
    }
}

uint64_t dataItemByteCount(DataItem *dataItem) {
	assert(dataItem != NULL);

	uint64_t byteCount = 1;

	uint64_t count = dataItemCount(dataItem);
	if (0 <= count && count <= 23) {
	} else if (24 <= count && count <= 0xFF) {
		byteCount += 1;
	} else if (0x0100 <= count && count <= 0xFFFF) {
		byteCount += 2;
	} else if (0x10000 <= count && count <= 0xFFFFFFFF) {
		byteCount += 4;
	} else if (0x100000000 <= count && count <= 0xFFFFFFFFFFFFFFFF) {
		byteCount += 8;
	}
	
	switch(dataItemMajorType(dataItem)) {
		case UNSIGNED_INT: case NEGATIVE_INT:
		case SPECIAL:
			break;
		
		case BYTE_STRING: case UTF_8:
			byteCount += count;
			break;

		case ARRAY:
			for(uint64_t i = 0; i < count; i++) {
				byteCount += dataItemByteCount(dataItem->array[i]);
			}
			break;

		case MAP:
			for(uint64_t i = 0; i < count; i++) {
				byteCount += dataItemByteCount(dataItem->keys[i]);
				byteCount += dataItemByteCount(dataItem->values[i]);
			}
			break;

		case TAG:
			byteCount += dataItemByteCount(dataItem->content);
			break;
	}

	return byteCount;
}

bool dataItemEqual(DataItem *dataItem1, DataItem *dataItem2) {
	assert(dataItem1 != NULL);
	assert(dataItem2 != NULL);

	if(dataItem1->header != dataItem2->header)
		return false;
	
	if(dataItem1->extendedCount != dataItem2->extendedCount)
		return false;
	
	uint64_t count = dataItemCount(dataItem1);
	switch (dataItemMajorType(dataItem1))
	{
		case BYTE_STRING: case UTF_8:
			for(uint64_t i = 0; i < count; i++) {
				if(dataItem1->payload[i] != dataItem2->payload[i])
					return false;
			}
			break;
		
		case ARRAY:
			for(uint64_t i = 0; i < count; i++) {
				if(!dataItemEqual(dataItem1->array[i], dataItem2->array[i]))
					return false;
			}
			break;
		
		case MAP:
			for(uint64_t i = 0; i < count; i++) {
				if(!dataItemEqual(dataItem1->keys[i], dataItem2->keys[i]))
					return false;
				if(!dataItemEqual(dataItem1->values[i], dataItem2->values[i]))
					return false;
			}
			break;
		
		case TAG:
			if(!dataItemEqual(dataItem1->content, dataItem2->content))
				return false;
			break;
	}
	
	if(dataItemByteCount(dataItem1) != dataItemByteCount(dataItem2))
		return false;
	
	return true;
}

bool dataItemLessThanOrEqual(DataItem *key1, DataItem *key2) {
	assert(key1 != NULL);
	assert(key2 != NULL);

	uint8_t majorType1 = dataItemMajorType(key1);
	uint8_t majorType2 = dataItemMajorType(key2);
	
	if(majorType1 < majorType2) {
		return true;
	} else if(majorType1 > majorType2) {
		return false;
	}

	uint64_t count1 = dataItemCount(key1);
	uint64_t count2 = dataItemCount(key2);
	if(count1 < count2) {
		return majorType1 == NEGATIVE_INT ? false : true;
	} else if(count1 > count2) {
		return majorType1 == NEGATIVE_INT ? true : false;
	}

	switch(majorType1) {
		case UNSIGNED_INT: case SPECIAL:
		case NEGATIVE_INT:
			return false;
		case TAG:
			return dataItemLessThanOrEqual(key1->content, key2->content);
	}

	for(uint64_t i = 0; i < count1; i++) {
		if(key1->payload[i] < key2->payload[i]) {
			return true;
		} else if(key1->payload[i] > key2->payload[i]) {
			return false;
		}
	}

	return false;
}

DataItem *dataItemCopy(DataItem *dataItem) {
	assert(dataItem != NULL);

	uint8_t *CBORArray = microCBOREncode(dataItem);
	if(CBORArray == NULL)
		return NULL;
	
	return microCBORDecode(CBORArray);
}

void dataItemFree(DataItem *dataItem) {
	assert(dataItem != NULL);

	uint64_t count = dataItemCount(dataItem);
	switch (dataItemMajorType(dataItem)) {
		case UNSIGNED_INT: case NEGATIVE_INT:
		case SPECIAL:
			break;

		case BYTE_STRING: case UTF_8:
			if(count > 0)
				free(dataItem->payload);
			break;
		
		case ARRAY:
			if(count > 0) {
				for(uint64_t i = 0; i < count; i++) {
					dataItemFree(dataItem->array[i]);
				}
				free(dataItem->array);
			}
			break;
		
		case MAP:
			if(count > 0) {
				for(uint64_t i = 0; i < count; i++) {
					dataItemFree(dataItem->keys[i]);
					dataItemFree(dataItem->values[i]);
				}
				free(dataItem->keys);
				free(dataItem->values);
			}
			break;
		
		case TAG:
			dataItemFree(dataItem->content);
			break;
	}

	free(dataItem);
}

/*
	#######################################
	Array Functions
	#######################################
*/

uint64_t dataItemArrayInsertElementAtIndex(DataItem *array, DataItem *element, uint64_t index) {
	assert(array != NULL);
	assert(element != NULL);

	uint64_t count = dataItemCount(array);
	
	uint8_t err = 0;
	array->array = dataItemInsertAtIndex(array->array, element, index, count, &err);

	if(err != 0) {
		return INVALID_INDEX;
	}

	return dataItemSetCount(array, count + 1);
}

uint64_t dataItemArrayRemoveElementAtIndex(DataItem *array, uint64_t index) {
	assert(array != NULL);

	uint64_t count = dataItemCount(array);

	uint8_t err;
	array->array = dataItemRemoveAtIndex(array->array, index, count, &err);

	if(err != 0)
		return INVALID_INDEX;
	
	return dataItemSetCount(array, count - 1);
}

uint64_t dataItemArrayAppendElement(DataItem *array, DataItem *element) {
	assert(array != NULL);
	assert(element != NULL);

	return dataItemArrayInsertElementAtIndex(array, element, dataItemCount(array));
}

/*
	#######################################
	Map Functions
	#######################################
*/

uint64_t dataItemMapRemoveKey(DataItem *map, DataItem *key) {
	assert(map != NULL);
	assert(key != NULL);

	uint64_t count = dataItemCount(map);
	uint64_t index = dataItemIndexOfItem(map->keys, key, count);
	if(index == INVALID_INDEX)
		return INVALID_INDEX;

	uint8_t err = 0;
	map->keys = dataItemRemoveAtIndex(map->keys, index, count, &err);
	if(err != 0) {
		return INVALID_INDEX;
	}

	map->values = dataItemRemoveAtIndex(map->values, index, count, &err);
	if(err != 0) {
		return INVALID_INDEX;
	}

	return dataItemSetCount(map, count - 1);
}

uint64_t dataItemMapIndexOfKey(DataItem *map, DataItem *key) {
	assert(map != NULL);
	assert(key != NULL);

	return dataItemIndexOfItem(map->keys, key, dataItemCount(map));
}

uint64_t dataItemMapInsertKeyValue(DataItem *map, DataItem *key, DataItem *value) {
	assert(map != NULL);
	assert(key != NULL);
	assert(value != NULL);

	uint64_t index = 0;

	uint64_t count = dataItemCount(map);
	for(uint64_t i = 0; i < count; i++) {
		if(dataItemLessThanOrEqual(key, map->keys[i]))
			break;
		index++;
	}

	uint8_t err = 0;
	map->keys = dataItemInsertAtIndex(map->keys, key, index, count, &err);
	if(err != 0) {
		return INVALID_INDEX;
	}

	map->values = dataItemInsertAtIndex(map->values, value, index, count, &err);
	if(err != 0) {
		return INVALID_INDEX;
	}
	
	return dataItemSetCount(map, count + 1);
}

uint8_t dataItemMapChangeValueAtKey(DataItem *map, DataItem *key, DataItem *value) {
	assert(map != NULL);
	assert(key != NULL);
	assert(value != NULL);

	DataItem *valueCopy = dataItemCopy(value);
	if(valueCopy == NULL)
		return -1;
	
	for(uint64_t i = 0; i < dataItemCount(map); i++) {
		if(dataItemEqual(key, map->keys[i])) {
			dataItemFree(map->values[i]);
			map->values[i] = valueCopy;
			return 0;
		}
	}

	return -1;
}
