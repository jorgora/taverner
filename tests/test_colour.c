#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../headers/sql/colour/colour.h"

static void test_colour_table_creation(void **state) {
    sqlite3 *db;
    assert_int_equal(sqlite3_open(":memory:", &db), SQLITE_OK);
    assert_int_equal(colour_create(db), SQLITE_OK); // Assuming it returns an int
    sqlite3_close(db);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_colour_table_creation),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
