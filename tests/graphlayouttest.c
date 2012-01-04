#include "testframework.h"
#include "commandline.h"

void commandline_test()
{
    int argc;
    /**
     * check single version flag
     */
    char **argv_1 = {
        "-v"
    };
    argc = 1;
    command_line_option *option = command_line_option_constructor(argc, argv_1);

    command_line_option_destruction(option);
}

void simpletest() {
    int foo = 1;
    TEST_ASSERT(foo);
    TEST_ASSERT_EQUAL_STR("abc", "abc");
}

void simpletest2() {
    TEST_ASSERT(1 == 1);
    TEST_ASSERT('c' == 'c');
    TEST_ASSERT_EQUAL_STR("abc", "Abc");
}

int main()
{
    TEST_RUNNER_SETUP;
    TEST_RUNNER_CASE_ADD(commandline_test, "commandline");
    TEST_RUNNER_CASE_ADD(simpletest2, "Test nummer 2");
    TEST_RUNNER_RUN;
    TEST_RUNNER_DESTROY;
    return TEST_RUNNER_FAILED;
}
