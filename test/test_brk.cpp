#include "test/test.h"

static void brk_halts_cpu(){
    reset_cpu();
    uint_8 prog[] = {BRK, LDA, 0x42};   // LDA after BRK must never run
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.halted);
    CHECK(cpu.register_a == 0);
}

static void unknown_opcode_halts_cpu(){
    reset_cpu();
    uint_8 prog[] = {0xFF, LDA, 0x42};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.halted);
    CHECK(cpu.register_a == 0);
}

void run_brk_tests(){
    brk_halts_cpu();
    unknown_opcode_halts_cpu();
    std::printf("  [ok] BRK / unknown opcode\n");
}
