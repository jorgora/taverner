#include <stdio.h>
#include <cmocka.h>  // Include CMocka library

#include "../headers/test_file.h"  // Include the function we are testing

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

// Test the output of print_hello_world()
static void test_print_hello_world(void **state) {
    // Redirect stdout to a buffer
    char buffer[128];
    FILE *original_stdout = stdout;
    stdout = fmemopen(buffer, sizeof(buffer), "w");

    // Call the function to test
    print_hello_world();

    // Flush stdout to ensure everything is written to the buffer
    fflush(stdout);

    // Assert the expected output
    assert_string_equal(buffer, "Hello, World!\n");

    // Restore original stdout
    stdout = original_stdout;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_print_hello_world),  // The actual test
        cmocka_unit_test(null_test_success),       // The "null" test
    };

    // Run the tests
    return cmocka_run_group_tests(tests, NULL, NULL);
}
