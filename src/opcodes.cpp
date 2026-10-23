#include "include/opcodes.h"
#include "include/memory.h"

CPU cpu;

static void update_zero_and_negative_flags(uint_8 result){
    if (result == 0) cpu.status |= FLAG_ZERO;
    else             cpu.status &= ~FLAG_ZERO;

    if (result & FLAG_NEGATIVE) cpu.status |= FLAG_NEGATIVE;
    else                        cpu.status &= ~FLAG_NEGATIVE;
}

static uint_8 fetch_byte(){
    return access_memory(cpu.program_counter++);
}

static void lda(uint_8 value){
    cpu.register_a = value;
    update_zero_and_negative_flags(cpu.register_a);
}

static void tax(){
    cpu.register_x = cpu.register_a;
    update_zero_and_negative_flags(cpu.register_x);
}

static void inx(){
    cpu.register_x++;   // uint_8 wraps 0xFF -> 0x00 naturally
    update_zero_and_negative_flags(cpu.register_x);
}

void cycle_1_instruction(uint_8 opcode, uint_8 &cycles){
    switch (opcode){
        case LDA:
            lda(fetch_byte());
            cycles += 2;
            break;

        case TAX:
            tax();
            cycles += 2;
            break;

        case INX:
            inx();
            cycles += 2;
            break;

        case BRK:
            cpu.halted = true;
            cycles += 7;
            break;

        default:
            // Unimplemented opcode: stop instead of silently running garbage.
            cpu.halted = true;
            break;
    }
}

void load_program(const uint_8 *program, uint_16 length, uint_16 start){
    for (uint_16 i = 0; i < length; i++){
        modify_memory(start + i, program[i]);
    }
    cpu.program_counter = start;
    cpu.halted = false;
}

unsigned long run(){
    unsigned long total = 0;
    while (!cpu.halted){
        uint_8 opcode = fetch_byte();
        uint_8 used = 0;
        cycle_1_instruction(opcode, used);
        total += used;
    }
    return total;
}
