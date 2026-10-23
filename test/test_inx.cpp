#include "test/test.h"

static void inx_increments(){
    reset_cpu();
    cpu.register_x = 5;
    uint_8 prog[] = {INX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 6);
}

static void inx_overflow(){
    reset_cpu();
    cpu.register_x = 0xFF;
    uint_8 prog[] = {INX, INX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 1);
}

static void inx_zero_flag_on_wrap(){
    reset_cpu();
    cpu.register_x = 0xFF;
    uint_8 prog[] = {INX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 0);
    CHECK((cpu.status & FLAG_ZERO) == FLAG_ZERO);
}

static void inx_negative_flag(){
    reset_cpu();
    cpu.register_x = 0x7F;
    uint_8 prog[] = {INX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 0x80);
    CHECK((cpu.status & FLAG_NEGATIVE) == FLAG_NEGATIVE);
}

void run_inx_tests(){
    inx_increments();
    inx_overflow();
    inx_zero_flag_on_wrap();
    inx_negative_flag();
    std::printf("  [ok] INX\n");
}
