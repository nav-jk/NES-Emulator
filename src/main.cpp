#include <cstdio>
#include "test/test.h"

int main(){
    std::printf("Running tests...\n");
    run_lda_tests();
    run_tax_tests();
    run_inx_tests();
    run_brk_tests();
    run_integration_tests();
    std::printf("All tests passed.\n");
    return 0;
}
