#include "test/test.h"

static void five_ops_working_together(){
    reset_cpu();
    uint_8 prog[] = {0xa9, 0xc0, 0xaa, 0xe8, 0x00};
    load_program(prog, sizeof prog);
    run();
    CHECK(cpu.register_x == 0xc1);
}

void run_integration_tests(){
    five_ops_working_together();
    std::printf("  [ok] integration\n");
}
