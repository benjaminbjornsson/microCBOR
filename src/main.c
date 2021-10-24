#include <stdint.h>

#include "decoder.h"
#include "encoder.h"
#include "utils.h"
#include "dataitem.h"

uint8_t integer[] = { 0x0F };
uint8_t string[] = { 0x61, 0x61 };
uint8_t array[] = { 0x83, 0x01, 0x02, 0x03 };
uint8_t map[] = { 0xA2, 0x01, 0x61, 0x61, 0x02, 0x61, 0x62 };

/*
void dataItemInsertKeyValue(DataItem *map, DataItem *key, DataItem *value) {
	
}
*/

int main() {
	DataItem *dataItem1 = decode(integer);
	dbg_buff_print(encode(dataItem1), dataItem1->byteCount);

	DataItem *dataItem2 = decode(string);
	dbg_buff_print(encode(dataItem2), dataItem2->byteCount);

	DataItem *dataItem3 = decode(array);
	dbg_buff_print(encode(dataItem3), dataItem3->byteCount);

	DataItem *dataItem4 = decode(map);
	dbg_buff_print(encode(dataItem4), dataItem4->byteCount);

	dataItemInsertElementAtIndex(dataItem3, dataItem1, 1);
	dbg_buff_print(encode(dataItem3), dataItem3->byteCount);

	dataItemInsertElementAtIndex(dataItem3, dataItem2, 2);
	dbg_buff_print(encode(dataItem3), dataItem3->byteCount);

	dataItemInsertElementAtIndex(dataItem3, dataItem4, 3);
	dbg_buff_print(encode(dataItem3), dataItem3->byteCount);
}
