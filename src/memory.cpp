#include "include/memory.h"

uint_8 memory[TOTAL_MEMORY] = {0};

uint_8 access_memory(uint_16 address){
    return memory[address];
}

void modify_memory(uint_16 address, uint_8 data){
    memory[address] = data;
}
