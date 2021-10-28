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
	
	uint8_t majorType = dataItemMajorType(dataItem);
	switch(majorType) {
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
}

void dataItemRemoveElementAtIndex(DataItem *array, uint64_t index) {
	uint64_t count = dataItemCount(array);
	DataItem **newArray = (DataItem **)malloc(sizeof(DataItem *) * (count - 1));
	
	DataItem *element;
	for(int i = 0; i < count; i++) {
		if(i == index) {
			element = array->array[i];
		} else {
			newArray[i > index ? i - 1 : i] = array->array[i];
		}
	}
	
	free(array->array);
	array->array = newArray;

	dataItemUpdateCount(array, count - 1);
	dataItemFree(element);
}

void dataItemAppendElement(DataItem *array, DataItem *element) {
	dataItemInsertElementAtIndex(array, element, dataItemCount(array));
}

void dataItemInsertKeyValueAtIndex(DataItem *map, DataItem *key, DataItem *value, uint64_t index) {
	uint64_t count = dataItemCount(map);

	DataItem **newKeys = (DataItem **)malloc(sizeof(DataItem *) * (count + 1));
	DataItem **newValues = (DataItem **)malloc(sizeof(DataItem *) * (count + 1));
	newKeys[index] = key;
	newValues[index] = value;
	for(int i = 0; i < count; i++) {
		newKeys[i >= index ? i + 1 : i] = map->keys[i];
		newValues[i >= index ? i + 1 : i] = map->values[i];
	}

	free(map->keys);
	free(map->values);
	map->keys = newKeys;
	map->values = newValues;
}

void dataItemRemoveKeyValueAtKey(DataItem *map, DataItem *key) {
	uint64_t count = dataItemCount(map);
	DataItem **newKeys = (DataItem **)malloc(sizeof(DataItem *) * (count - 1));
	DataItem **newValues = (DataItem **)malloc(sizeof(DataItem *) * (count - 1));

	DataItem *keyToRemove, *valueToRemove;
	bool removed = false;
	for(int i = 0; i < count; i++) {
		if(dataItemEqual(key, map->keys[i])) {
			keyToRemove = map->keys[i];
			valueToRemove = map->values[i];
			removed = true;
		} else {
			newKeys[removed ? i - 1 : i] = map->keys[i];
			newValues[removed ? i - 1 : i] = map->values[i];
		}
	}

	free(map->keys);
	free(map->values);
	map->keys = newKeys;
	map->values = newValues;

	dataItemUpdateCount(map, count - 1);
	dataItemFree(keyToRemove);
	dataItemFree(valueToRemove);
}

bool dataItemKeyExists(DataItem *map, DataItem *key) {
	uint64_t count = dataItemCount(map);
	for(uint64_t i = 0; i < count; i++) {
		if(dataItemEqual(key, map->keys[i]))
			return true;
	}

	return false;
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
	
	dataItemInsertKeyValueAtIndex(map, key, value, index);
	dataItemUpdateCount(map, count + 1);
}

void dataItemChangeValueAtKey(DataItem *map, DataItem *key, DataItem *value) {
	uint64_t count = dataItemCount(map);
	for(uint64_t i = 0; i < count; i++) {
		if(dataItemEqual(key, map->keys[i])) {
			dataItemFree(map->values[i]);
			map->values[i] = value;
			return;
		}
	}

	dataItemFree(value);
}

bool dataItemEqual(DataItem *item1, DataItem *item2) {
	if(item1->header != item2->header)
		return false;
	
	if(item1->extendedCount != item2->extendedCount)
		return false;
	
	uint64_t count = dataItemCount(item1);
	uint8_t majorType = dataItemMajorType(item1);
	switch (majorType)
	{
		case BYTE_STRING: case UTF_8:
			for(int i = 0; i < count; i++) {
				if(item1->payload[i] != item2->payload[i])
					return false;
			}

			if(item1->array != NULL | item2->array != NULL)
				return false;
			if(item1->keys != NULL | item2->keys != NULL)
				return false;
			if(item1->values != NULL | item2->values != NULL)
				return false;
			if(item1->content != NULL | item2->content != NULL)
				return false;
			break;
		
		case ARRAY:
			for(int i = 0; i < count; i++) {
				if(!dataItemEqual(item1->array[i], item2->array[i]))
					return false;
			}

			if(item1->payload != NULL | item2->payload != NULL)
				return false;
			if(item1->keys != NULL | item2->keys != NULL)
				return false;
			if(item1->values != NULL | item2->values != NULL)
				return false;
			if(item1->content != NULL | item2->content != NULL)
				return false;
			break;
		
		case MAP:
			for(int i = 0; i < count; i++) {
				if(!dataItemEqual(item1->keys[i], item2->keys[i]))
					return false;
				if(!dataItemEqual(item1->values[i], item2->values[i]))
					return false;
			}

			if(item1->payload != NULL | item2->payload != NULL)
				return false;
			if(item1->array != NULL | item2->array != NULL)
				return false;
			if(item1->content != NULL | item2->content != NULL)
				return false;
			break;
		
		case TAG:
			if(!dataItemEqual(item1->content, item2->content))
				return false;

			if(item1->payload != NULL | item2->payload != NULL)
				return false;
			if(item1->array != NULL | item2->array != NULL)
				return false;
			if(item1->keys != NULL | item2->keys != NULL)
				return false;
			if(item1->values != NULL | item2->values != NULL)
				return false;
			break;
		
		default:
			if(item1->payload != NULL | item2->payload != NULL)
				return false;
			if(item1->array != NULL | item2->array != NULL)
				return false;
			if(item1->keys != NULL | item2->keys != NULL)
				return false;
			if(item1->values != NULL | item2->values != NULL)
				return false;
			if(item1->content != NULL | item2->content != NULL)
				return false;
	}
	
	if(dataItemByteCount(item1) != dataItemByteCount(item2))
		return false;
	
	return true;
}

void dataItemFree(DataItem *dataItem) {
	uint64_t count = dataItemCount(dataItem);
	uint8_t majorType = dataItemMajorType(dataItem);
	switch (majorType) {
		case UNSIGNED_INT: case NEGATIVE_INT:
		case SPECIAL:
			break;

		case BYTE_STRING: case UTF_8:
			if(count > 0)
				free(dataItem->payload);
			break;
		
		case ARRAY:
			for(int i = 0; i < count; i++) {
				dataItemFree(dataItem->array[i]);
			}
			break;
			free(dataItem->array);
		
		case MAP:
			for(int i = 0; i < count; i++) {
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

