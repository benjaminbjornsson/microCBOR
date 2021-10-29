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
#include "dataitem.h"

#define	INVALID_INDEX	-1

/*
	#######################################
	Helper Functions
	#######################################
*/

uint64_t dataItemIndexOfItem(DataItem **array, DataItem *item, uint64_t count) {
	for(uint64_t i = 0; i < count; i++)	{
		if(dataItemEqual(item, array[i]))
			return i;
	}

	return INVALID_INDEX;
}

DataItem **dataItemInsertAtIndex(DataItem **dataItem, DataItem *element, uint64_t index, uint64_t length) {
	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (length + 1));

	newArray[index] = element;
	for(uint64_t i = 0; i < length; i++) {
		newArray[i >= index ? i + 1 : i] = dataItem[i];
	}

	free(dataItem);

	return newArray;
}

DataItem **dataItemRemoveAtIndex(DataItem **dataItem, uint64_t index, uint64_t length) {
	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (length - 1));
	
	DataItem *element;
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

void dataItemSetCount(DataItem *dataItem, uint64_t count) {
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
}

/*
	#######################################
	Generic Functions
	#######################################
*/

uint8_t dataItemMajorType(DataItem *dataItem) {
	return (dataItem->header >> 5);
}

uint8_t dataItemShortCount(DataItem *dataItem) {
	return (dataItem->header & 0x1F);
}

uint64_t dataItemCount(DataItem *dataItem) {
    uint8_t shortCount = dataItem->header & 0x1F;
    if(24 <= shortCount && shortCount <= 27) {
        return dataItem->extendedCount;
    } else {
        return shortCount;
    }
}

uint64_t dataItemByteCount(DataItem *dataItem) {
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

bool dataItemEqual(DataItem *item1, DataItem *item2) {
	if(item1->header != item2->header)
		return false;
	
	if(item1->extendedCount != item2->extendedCount)
		return false;
	
	uint64_t count = dataItemCount(item1);
	switch (dataItemMajorType(item1))
	{
		case BYTE_STRING: case UTF_8:
			for(uint64_t i = 0; i < count; i++) {
				if(item1->payload[i] != item2->payload[i])
					return false;
			}
			break;
		
		case ARRAY:
			for(uint64_t i = 0; i < count; i++) {
				if(!dataItemEqual(item1->array[i], item2->array[i]))
					return false;
			}
			break;
		
		case MAP:
			for(uint64_t i = 0; i < count; i++) {
				if(!dataItemEqual(item1->keys[i], item2->keys[i]))
					return false;
				if(!dataItemEqual(item1->values[i], item2->values[i]))
					return false;
			}
			break;
		
		case TAG:
			if(!dataItemEqual(item1->content, item2->content))
				return false;
			break;
	}
	
	if(dataItemByteCount(item1) != dataItemByteCount(item2))
		return false;
	
	return true;
}

bool dataItemLessThanOrEqual(DataItem *key1, DataItem *key2) {
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

void dataItemFree(DataItem *dataItem) {
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
			for(uint64_t i = 0; i < count; i++) {
				dataItemFree(dataItem->array[i]);
			}
			break;
			free(dataItem->array);
		
		case MAP:
			for(uint64_t i = 0; i < count; i++) {
				dataItemFree(dataItem->keys[i]);
				dataItemFree(dataItem->values[i]);
			}
			break;
			free(dataItem->keys);
			free(dataItem->values);
		
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

void dataItemArrayInsertElementAtIndex(DataItem *array, DataItem *element, uint64_t index) {
	uint64_t count = dataItemCount(array);

	array->array = dataItemInsertAtIndex(array->array, element, index, count);

	dataItemSetCount(array, count + 1);
}

void dataItemArrayRemoveElementAtIndex(DataItem *array, uint64_t index) {
	uint64_t count = dataItemCount(array);

	array->array = dataItemRemoveAtIndex(array->array, index, count);

	dataItemSetCount(array, count - 1);
}

void dataItemArrayAppendElement(DataItem *array, DataItem *element) {
	dataItemArrayInsertElementAtIndex(array, element, dataItemCount(array));
}

/*
	#######################################
	Map Functions
	#######################################
*/

void dataItemMapRemoveKey(DataItem *map, DataItem *key) {
	uint64_t count = dataItemCount(map);
	uint64_t index = dataItemIndexOfItem(map->keys, key, count);
	if(index == INVALID_INDEX)
		return;

	map->keys = dataItemRemoveAtIndex(map->keys, index, count);
	map->values = dataItemRemoveAtIndex(map->values, index, count);

	dataItemSetCount(map, count - 1);
}

uint64_t dataItemMapIndexOfKey(DataItem *map, DataItem *key) {
	uint64_t count = dataItemCount(map);
	return dataItemIndexOfItem(map->keys, key, count);
}

void dataItemMapInsertKeyValue(DataItem *map, DataItem *key, DataItem *value) {
	uint64_t index = 0;

	uint64_t count = dataItemCount(map);
	for(uint64_t i = 0; i < count; i++) {
		if(dataItemLessThanOrEqual(key, map->keys[i]))
			break;
		index++;
	}

	map->keys = dataItemInsertAtIndex(map->keys, key, index, count);
	map->values = dataItemInsertAtIndex(map->values, value, index, count);
	
	dataItemSetCount(map, count + 1);
}

void dataItemMapChangeValueAtKey(DataItem *map, DataItem *key, DataItem *value) {
	for(uint64_t i = 0; i < dataItemCount(map); i++) {
		if(dataItemEqual(key, map->keys[i])) {
			dataItemFree(map->values[i]);
			map->values[i] = value;
			return;
		}
	}

	dataItemFree(value);
}
