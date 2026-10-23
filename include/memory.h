#pragma once

#include "utils/types.h"
#include "utils/config.h"


extern uint_8 memory[TOTAL_MEMORY];

uint_8 access_memory(uint_16 address);
void modify_memory(uint_16 address, uint_8 data);
