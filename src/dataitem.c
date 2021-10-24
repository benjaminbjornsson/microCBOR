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
