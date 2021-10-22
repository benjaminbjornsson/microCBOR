#include <stdint.h>
#include "decoder.h"
#include "encoder.h"

uint8_t array[] = { 0xA1, 0x61, 0x31, 0x01 };

int main() {
	DataItem *dataItem = decode(array);
}
