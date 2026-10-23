#include "test/test.h"

static void lda_immediate_load_data(){
    reset_cpu();
    uint_8 prog[] = {LDA, 0x05, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_a == 0x05);
    CHECK((cpu.status & FLAG_ZERO) == 0);
    CHECK((cpu.status & FLAG_NEGATIVE) == 0);
}

static void lda_zero_flag(){
    reset_cpu();
    uint_8 prog[] = {LDA, 0x00, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_a == 0x00);
    CHECK((cpu.status & FLAG_ZERO) == FLAG_ZERO);
}

static void lda_negative_flag(){
    reset_cpu();
    uint_8 prog[] = {LDA, 0x80, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_a == 0x80);
    CHECK((cpu.status & FLAG_NEGATIVE) == FLAG_NEGATIVE);
    CHECK((cpu.status & FLAG_ZERO) == 0);
}

static void lda_clears_flags_on_later_load(){
    reset_cpu();
    uint_8 prog[] = {LDA, 0x00, LDA, 0x01, BRK};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_a == 0x01);
    CHECK((cpu.status & FLAG_ZERO) == 0);
    CHECK((cpu.status & FLAG_NEGATIVE) == 0);
}

static void lda_advances_pc_and_cycles(){
    reset_cpu();
    uint_8 prog[] = {LDA, 0x05, BRK};
    load_program(prog, sizeof prog);
    unsigned long cycles = run();
    CHECK(cpu.program_counter == 0x8000 + 3);
    CHECK(cycles == 2 + 7);   // LDA (2) + BRK (7)
}

void run_lda_tests(){
    lda_immediate_load_data();
    lda_zero_flag();
    lda_negative_flag();
    lda_clears_flags_on_later_load();
    lda_advances_pc_and_cycles();
    std::printf("  [ok] LDA\n");
}
