#pragma once

#include "./utils/types.h"
#include "./utils/config.h"

#define LDA 0xA9
#define TAX 0xAA
#define INX 0xE8
#define BRK 0x00

#define FLAG_ZERO     0b00000010
#define FLAG_NEGATIVE 0b10000000

struct CPU {
    uint_8  register_a = 0;
    uint_8  register_x = 0;
    uint_8  status = 0;
    uint_16 program_counter = 0;
    bool    halted = false;
};

inline void update_zero_and_negative_flags(CPU &cpu, uint_8 result) {
    if (result == 0) cpu.status |= FLAG_ZERO;
    else             cpu.status &= ~FLAG_ZERO;

    if (result & FLAG_NEGATIVE) cpu.status |= FLAG_NEGATIVE;
    else                        cpu.status &= ~FLAG_NEGATIVE;
}


inline void cycle_1_instruction(CPU &cpu, const uint_8 *program,
                                uint_8 opcode, uint_8 &cycles) {
    switch (opcode) {
        case LDA: {                                   // LDA #imm
            uint_8 param = program[cpu.program_counter++];
            cpu.register_a = param;
            update_zero_and_negative_flags(cpu, cpu.register_a);
            cycles += 2;
            break;
        }
        case TAX:                                     // A -> X
            cpu.register_x = cpu.register_a;
            update_zero_and_negative_flags(cpu, cpu.register_x);
            cycles += 2;
            break;

        case INX:                                     // X++ (wraps at 0xFF)
            cpu.register_x++;
            update_zero_and_negative_flags(cpu, cpu.register_x);
            cycles += 2;
            break;

        case BRK:
            cpu.halted = true;
            cycles += 7;
            break;

        default:
            // Unimplemented opcode
            cpu.halted = true;
            break;
    }
}

// Fetch -> decode -> execute loop
inline void interpret(CPU &cpu, const uint_8 *program) {
    uint_8 cycles = 0;
    cpu.program_counter = 0;
    cpu.halted = false;

    while (!cpu.halted) {
        uint_8 opcode = program[cpu.program_counter++];
        cycle_1_instruction(cpu, program, opcode, cycles);
    }
}