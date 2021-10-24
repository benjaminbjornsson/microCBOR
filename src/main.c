#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "decoder.h"
#include "encoder.h"
#include "utils.h"
#include "dataitem.h"

uint8_t integer[] = { 0x01 };
uint8_t string[] = { 0x61, 0x61 };
uint8_t array[] = { 0x83, 0x01, 0x02, 0x03 };
uint8_t map[] = { 0xA2, 0x01, 0x61, 0x61, 0x02, 0x61, 0x62 };

int main() {
	DataItem *dataItem1 = decode(integer);
	dbg_buff_print(encode(dataItem1), dataItem1->byteCount);

	DataItem *dataItem2 = decode(string);
	dbg_buff_print(encode(dataItem2), dataItem2->byteCount);

	DataItem *dataItem3 = decode(array);
	dbg_buff_print(encode(dataItem3), dataItem3->byteCount);

	DataItem *dataItem4 = decode(map);
	dbg_buff_print(encode(dataItem4), dataItem4->byteCount);

	dataItemInsertKeyValue(dataItem4, dataItem2, dataItem3);
	dbg_buff_print(encode(dataItem4), dataItem4->byteCount);
}
