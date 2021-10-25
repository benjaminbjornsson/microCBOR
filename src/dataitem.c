#include <stdio.h>
#include <stdbool.h>
#include "dataitem.h"

uint64_t dataItemCount(DataItem *dataItem) {
    uint8_t shortCount = dataItem->header & 0x1F;
    if(24 <= shortCount && shortCount <= 27) {
        return dataItem->extendedCount;
    } else {
        return shortCount;
    }
}

uint8_t dataItemMajorType(DataItem *dataItem) {
	return (dataItem->header >> 5);
}

uint8_t dataItemShortCount(DataItem *dataItem) {
	return (dataItem->header & 0x1F);
}

void dataItemUpdateCount(DataItem *dataItem, uint64_t count) {
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

void dataItemInsertElementAtIndex(DataItem *array, DataItem *element, uint64_t index) {
	uint64_t count = dataItemCount(array);

	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (count + 1));
	newArray[index] = element;
	for(int i = 0; i < count; i++) {
		newArray[i >= index ? i + 1 : i] = array->array[i];
	}

	free(array->array);
	array->array = newArray;

	dataItemUpdateCount(array, count + 1);
	array->byteCount += element->byteCount;
}

void dataItemAppendElement(DataItem *array, DataItem *element) {
	dataItemInsertElementAtIndex(array, element, dataItemCount(array));
}

void dataItemInsertKeyAtIndex(DataItem *map, DataItem *key, uint64_t index) {
	uint64_t count = dataItemCount(map);

	DataItem **newKeys = (DataItem **)malloc(sizeof(DataItem *) * (count + 1));
	newKeys[index] = key;
	for(int i = 0; i < count; i++) {
		newKeys[i >= index ? i + 1 : i] = map->keys[i];
	}

	free(map->keys);
	map->keys = newKeys;

	map->byteCount += key->byteCount;
}

void dataItemInsertValueAtIndex(DataItem *map, DataItem *value, uint64_t index) {
	uint64_t count = dataItemCount(map);

	DataItem **newValues = (DataItem **)malloc(sizeof(DataItem *) * (count + 1));
	newValues[index] = value;
	for(int i = 0; i < count; i++) {
		newValues[i >= index ? i + 1 : i] = map->values[i];
	}

	free(map->values);
	map->values = newValues;

	map->byteCount += value->byteCount;
	
}

bool dataItemKeyLessThanOrEqual(DataItem *key1, DataItem *key2) {
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
		case NEGATIVE_INT: case TAG:
			return false;
	}

	for(int i = 0; i < count1; i++) {
		if(key1->payload[i] < key2->payload[i]) {
			return true;
		} else if(key1->payload[i] > key2->payload[i]) {
			return false;
		}
	}

	return false;
}

void dataItemInsertKeyValue(DataItem *map, DataItem *key, DataItem *value) {
	uint64_t index = 0;

	uint64_t count = dataItemCount(map);
	for(int i = 0; i < count; i++) {
		if(dataItemKeyLessThanOrEqual(key, map->keys[i]))
			break;
		index++;
	}
	
	dataItemInsertKeyAtIndex(map, key, index);
	dataItemInsertValueAtIndex(map, value, index);
	dataItemUpdateCount(map, count + 1);
}
