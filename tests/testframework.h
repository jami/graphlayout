#ifndef TESTFRAMEWORK_H_
#define TESTFRAMEWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_RUNNER_MSG_GREETING "Running tests\n"
#define TEST_RUNNER_MSG_TEST_RESULT "Tests: %d Assertions: %d Failed: %d\n"
#define TEST_RUNNER_MSG_ASSERT_FAILED "Assertion failed on %s:%d!\n"
#define TEST_RUNNER_MSG_FAILED "Test (%d/%d): %s failed\n"
#define TEST_RUNNER_MSG_PASS "Test (%d/%d): %s passed\n"
#define TEST_RUNNER_MSG_ALL_PASS "All tests pass. OK!\n"
#define TEST_RUNNER_MSG_ALL_FAILED "Some tests failed. :(\n"

#define TEST_RUNNER_FAILED test_runner_global_instance.test_fail > 0 ? 1 : 0

#define TEST_RUNNER_SETUP test_runner_global_constructor()
#define TEST_RUNNER_DESTROY test_runner_global_destructor()
#define TEST_RUNNER_RUN test_runner_run()
#define TEST_RUNNER_CASE_ADD(x, n) test_runner_case_add(&x, n)

#define TEST_ASSERT(x) test_runner_op_assert((x), __LINE__, __FILE__)
#define TEST_ASSERT_EQUAL_STR(x, y) test_runner_op_assert_equal_str((x), (y), __LINE__, __FILE__)


typedef struct _test_runner_case {
    struct _test_runner_case *next_case;
    int case_failed;
    char *name;
    void (*test_case_function)();
} test_runner_case;

typedef struct _test_runner_global
{
    test_runner_case *case_list_head;
    test_runner_case *case_list_tail;
    test_runner_case *case_list_current;
    int test_count;
    int test_fail;
    int test_assert;
    FILE *outstream;
} test_runner_global;

static test_runner_global test_runner_global_instance;

void test_runner_global_constructor();
void test_runner_global_destructor();
void test_runner_run();

test_runner_case *test_runner_case_constructor();
void test_runner_case_destructor(test_runner_case*);
void test_runner_case_add(void (*)(), char*);
void test_runner_console_color(int attr, int fg, int bg);

void test_runner_op_assert(int x, int, char*);
void test_runner_op_assert_equal_str(char*, char*, int, char*);

#endif
