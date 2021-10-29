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
