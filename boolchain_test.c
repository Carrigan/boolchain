#include <stdio.h>
#include "boolchain.h"
#include "minunit.h"
#include "boolchainmock.h"

// Definitions
#define BC_SIZE 20   

// Testables
bc_t bc;
bool bools[BC_SIZE];

// Test Table

// Minunit Test Definition
int tests_run = 0;

// mu_assert("error, could not get", bar == 5);

// Test string
bool expected_bools[] = { true, false, true, true, false };

bc_error_t bc_build(bc_t *p_bc, uint8_t p_size) {
    bcm_init(p_size);
    return boolchain_init(p_bc, bools, BC_SIZE, bcm_read, bcm_write);
}

static char *test_initialize() {
    bc_error_t result;

    bcm_init(BC_SIZE / 2);
    result = boolchain_init(&bc, NULL, BC_SIZE, bcm_read, bcm_write);
    mu_assert("init error - null buffer should fail", result == BOOLCHAIN_NULL_BUFFER);

    result = bc_build(&bc, BC_SIZE + 1);
    mu_assert("init error - exceeding the max bool count should fail", result == BOOLCHAIN_TOO_MANY_NODES);

    result = bc_build(&bc, BC_SIZE / 2);
    printf("%d", result);
    mu_assert("init error - valid initialization failed", result == BOOLCHAIN_OK);    
    return 0;
}

static char *test_count() {
    bc_error_t result = bc_build(&bc, BC_SIZE / 2);
    uint8_t node_count = BC_SIZE / 2;
    bcm_init(node_count);
    mu_assert("count error - reading the count failed", boolchain_count(&bc) == node_count);
    return 0;
}

static char *test_get() {
    bc_error_t result = bc_build(&bc, BC_SIZE / 2);
    uint8_t node_count = BC_SIZE / 2;
    bcm_init(node_count);
    bcm_set_data(expected_bools, sizeof(expected_bools) / sizeof(bool));

    boolchain_capture(&bc);
    for (int i = 0; i < sizeof(expected_bools) / sizeof(bool); i++) {
        bool signal_in;
        mu_assert("get error - get failed", boolchain_get(&bc, i, &signal_in) == BOOLCHAIN_OK);
        mu_assert("get error - wrong value", signal_in == expected_bools[i]);
    }

    return 0;
}

static char * boolchain_tests() {
    mu_run_test(test_initialize);
    mu_run_test(test_count);
    mu_run_test(test_get);
    return 0;
}

int main(int argc, char **argv) {
    char *result = boolchain_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
