#include "testframework.h"

void simpletest() {
    int foo = 1;
    TEST_ASSERT(foo);
    TEST_ASSERT_EQUAL_STR("abc", "abc");
}

void simpletest2() {
    TEST_ASSERT_EQUAL_STR("abc", "abc1");
}

int main()
{
    TEST_RUNNER_SETUP;
    TEST_RUNNER_CASE_ADD(simpletest, "Test nummer 1");
    TEST_RUNNER_CASE_ADD(simpletest2, "Test nummer 2");
    TEST_RUNNER_RUN;
    TEST_RUNNER_DESTROY;
    return TEST_RUNNER_FAILED;
}
