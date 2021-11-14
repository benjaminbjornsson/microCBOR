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
	union {
		uint8_t *payload;
		struct DataItem **array;
		struct {
			struct DataItem **keys;
			struct DataItem **values;
		};
		struct DataItem *content;
	};
} DataItem;

/*
	#######################################
	Generic Functions
	#######################################
*/

uint8_t dataItemMajorType(DataItem *dataItem);

uint8_t dataItemShortCount(DataItem *dataItem);

uint64_t dataItemCount(DataItem *dataItem);

uint64_t dataItemSetCount(DataItem *dataItem, uint64_t count);

uint64_t dataItemByteCount(DataItem *dataItem);

bool dataItemEqual(DataItem *dataItem1, DataItem *dataItem2);

bool dataItemLessThanOrEqual(DataItem *key1, DataItem *key2);

DataItem *dataItemCopy(DataItem *dataItem);

void dataItemFree(DataItem *dataItem);

/*
	#######################################
	Array Functions
	#######################################
*/

uint64_t dataItemArrayInsertElementAtIndex(DataItem *array, DataItem *element, uint64_t index);

uint64_t dataItemArrayRemoveElementAtIndex(DataItem *array, uint64_t index);

uint64_t dataItemArrayAppendElement(DataItem *array, DataItem *element);

/*
	#######################################
	Map Functions
	#######################################
*/

uint64_t dataItemMapRemoveKey(DataItem *map, DataItem *key);

uint64_t dataItemMapIndexOfKey(DataItem *map, DataItem *key);

uint64_t dataItemMapInsertKeyValue(DataItem *map, DataItem *key, DataItem *value);

uint8_t dataItemMapChangeValueAtKey(DataItem *map, DataItem *key, DataItem *value);

#endif /* _DATA_ITEM_H_ */
