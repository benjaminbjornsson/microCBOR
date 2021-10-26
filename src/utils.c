#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

void dbg_buff_print(uint8_t *buff, int count) {
	int i;
	for(i = 0; i < count; i++) {
		printf("%02X ", *buff++);
	}
	printf("\n");
}

bool compareByteArray(uint8_t *first, uint8_t *second, int count) {
	for(int i = 0; i < count; i++) {
		if(first[i] != second[i])
			return false;
	}

	return true;
}