#include "test/test.h"

static void tax_move_a_to_x(){
    reset_cpu();
    cpu.register_a = 10;
    uint_8 prog[] = {TAX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 10);
    CHECK(cpu.register_a == 10);   // A is unchanged
}

static void tax_zero_flag(){
    reset_cpu();
    cpu.register_a = 0;
    cpu.register_x = 0x55;
    uint_8 prog[] = {TAX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 0);
    CHECK((cpu.status & FLAG_ZERO) == FLAG_ZERO);
}

static void tax_negative_flag(){
    reset_cpu();
    cpu.register_a = 0xFF;
    uint_8 prog[] = {TAX, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 0xFF);
    CHECK((cpu.status & FLAG_NEGATIVE) == FLAG_NEGATIVE);
}

void run_tax_tests(){
    tax_move_a_to_x();
    tax_zero_flag();
    tax_negative_flag();
    std::printf("  [ok] TAX\n");
}
