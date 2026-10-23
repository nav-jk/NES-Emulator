#pragma once

#include <cstdio>
#include <cstdlib>
#include "include/opcodes.h"
#include "include/memory.h"

#define CHECK(cond) do { \
    if (!(cond)) { \
        std::printf("FAIL: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
        std::exit(1); \
    } \
} while (0)

// Resets CPU registers/flags before each test.
inline void reset_cpu(){
    cpu = CPU();
}

// Each test file exposes one entry point.
void run_lda_tests();
void run_tax_tests();
void run_inx_tests();
void run_brk_tests();
void run_integration_tests();
