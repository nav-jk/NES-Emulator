#pragma once

#include "utils/types.h"
#include "utils/config.h"

#define BRK 0x00
#define LDA 0xA9   // LDA #imm  (2 bytes, 2 cycles)
#define TAX 0xAA   // TAX       (1 byte,  2 cycles)
#define INX 0xE8   // INX       (1 byte,  2 cycles)

#define FLAG_ZERO     0b00000010
#define FLAG_NEGATIVE 0b10000000

struct CPU {
    uint_8  register_a = 0;
    uint_8  register_x = 0;
    uint_8  status = 0;
    uint_16 program_counter = 0;
    bool    halted = false;   // set by BRK
};

extern CPU cpu;

// Copies `program` into memory starting at `start`, and points the PC there.
void load_program(const uint_8 *program, uint_16 length, uint_16 start = 0x8000);

// Fetch -> decode -> execute exactly one instruction.
// Adds the cycles the instruction consumed to `cycles`.
void cycle_1_instruction(uint_8 opcode, uint_8 &cycles);

// Runs until BRK. Returns total cycles consumed.
unsigned long run();
