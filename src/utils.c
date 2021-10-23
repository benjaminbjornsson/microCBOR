#include <stdio.h>
#include "utils.h"

void dbg_buff_print(uint8_t *buff, int count) {
	int i;
	for(i = 0; i < count; i++) {
		printf("%02X ", *buff++);
	}
	printf("\n");
}
