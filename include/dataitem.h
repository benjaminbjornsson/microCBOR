#ifndef _DATA_ITEM_H_
#define _DATA_ITEM_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define	UNSIGNED_INT	0x00
#define	NEGATIVE_INT	0x01
#define	BYTE_STRING		0x02
#define	UTF_8			0x03
#define	ARRAY			0x04
#define	MAP				0x05
#define	TAG				0x06
#define	SPECIAL			0x07

typedef struct DataItem {
	uint8_t header;
	uint64_t extendedCount;
	uint8_t *payload;
	struct DataItem **array;
	struct DataItem **keys;
	struct DataItem **values;
	struct DataItem *content;
} DataItem;

/*
	#######################################
	Generic Functions
	#######################################
*/

uint8_t dataItemMajorType(DataItem *dataItem);

uint8_t dataItemShortCount(DataItem *dataItem);

uint64_t dataItemCount(DataItem *dataItem);

void dataItemUpdateCount(DataItem *dataItem, uint64_t count);

uint64_t dataItemByteCount(DataItem *dataItem);

bool dataItemEqual(DataItem *item1, DataItem *item2);

bool dataItemLessThanOrEqual(DataItem *key1, DataItem *key2);

void dataItemFree(DataItem *dataItem);

/*
	#######################################
	Array Functions
	#######################################
*/

void dataItemArrayInsertElementAtIndex(DataItem *array, DataItem *element, uint64_t index);

void dataItemArrayRemoveElementAtIndex(DataItem *array, uint64_t index);

void dataItemArrayAppendElement(DataItem *array, DataItem *element);

/*
	#######################################
	Map Functions
	#######################################
*/

void dataItemMapInsertKeyValueAtIndex(DataItem *map, DataItem *key, DataItem *value, uint64_t index);

void dataItemMapChangeValueAtKey(DataItem *map, DataItem *key, DataItem *value);

bool dataItemMapKeyExists(DataItem *map, DataItem *key);

void dataItemMapInsertKeyValue(DataItem *map, DataItem *key, DataItem *value);

void dataItemMapRemoveKeyValueAtKey(DataItem *map, DataItem *key);


#endif /* _DATA_ITEM_H_ */
