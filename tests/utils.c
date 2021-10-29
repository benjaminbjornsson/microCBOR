#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

void dbg_buff_print(uint8_t *buff, uint64_t count) {
	uint64_t i;
	for(i = 0; i < count; i++) {
		printf("%02X ", *buff++);
	}
	printf("\n");
}

bool compareByteArray(uint8_t *first, uint8_t *second, uint64_t count) {
	for(uint64_t i = 0; i < count; i++) {
		if(first[i] != second[i])
			return false;
	}

	return true;
}
