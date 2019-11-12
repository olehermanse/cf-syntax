// Unit test / mocking framework, cmocka:
#include <cmocka.h>

// Functionality we are testing:
#include <parse_lib.h>

#include <stdlib.h>

static void parse_test_cf(void **data) {
    {
        PolicyFile *policy = ParseFile("../../examples/00_empty.cf");
        assert_true(policy != NULL);
        free(policy);
    }
    {
        PolicyFile *policy = ParseFile("../../examples/01_body_empty.cf");
        assert_true(policy != NULL);
        free(policy);
    }
    {
        PolicyFile *policy = ParseFile("../../examples/02_body_curly.x.cf");
        assert_true(policy == NULL);
    }
    {
        PolicyFile *policy = ParseFile("../../examples/03_body_string.x.cf");
        assert_true(policy == NULL);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(parse_test_cf),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
