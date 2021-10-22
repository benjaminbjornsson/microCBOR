#ifndef _DATA_ITEM_H_
#define _DATA_ITEM_H_

#include <stdint.h>

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
	uint64_t byteCount;
} DataItem;

#endif /* _DATA_ITEM_H_ */
