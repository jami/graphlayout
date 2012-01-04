#include "testframework.h"

void test_runner_global_constructor()
{
    test_runner_global_instance.test_count        = 0;
    test_runner_global_instance.test_fail         = 0;
    test_runner_global_instance.case_list_head    = 0;
    test_runner_global_instance.case_list_tail    = 0;
    test_runner_global_instance.case_list_current = 0;
    test_runner_global_instance.test_assert       = 0;
    test_runner_global_instance.outstream         = stdout;
}

void test_runner_global_destructor()
{
    test_runner_case *tmp_case, *test_case = test_runner_global_instance.case_list_head;
    while (test_case) {
        tmp_case = test_case->next_case;
        test_runner_case_destructor(test_case);
        test_case = tmp_case;
    }

    fprintf(
        test_runner_global_instance.outstream,
        TEST_RUNNER_MSG_TEST_RESULT,
        test_runner_global_instance.test_count,
        test_runner_global_instance.test_assert,
        test_runner_global_instance.test_fail
    );

    if (test_runner_global_instance.test_fail) {
        fprintf(
            test_runner_global_instance.outstream,
            TEST_RUNNER_MSG_ALL_FAILED
        );
    } else {
        fprintf(
            test_runner_global_instance.outstream,
            TEST_RUNNER_MSG_ALL_PASS
        );
    }
}

void test_runner_run()
{
    void (*case_cb)();

    fprintf(test_runner_global_instance.outstream, TEST_RUNNER_MSG_GREETING);

    if (test_runner_global_instance.case_list_head == 0) {
        return;
    }

    int counter = 1;
    test_runner_case *tmp_case, *test_case = test_runner_global_instance.case_list_head;
    while (test_case) {
        tmp_case = test_case->next_case;

        test_runner_global_instance.case_list_current = test_case;
        case_cb = test_case->test_case_function;

        case_cb();

        if (test_case->case_failed) {
            test_runner_console_color(1, 1, 8);
            fprintf(
                test_runner_global_instance.outstream,
                TEST_RUNNER_MSG_FAILED,
                counter,
                test_runner_global_instance.test_count,
                test_case->name
            );
            test_runner_console_color(0, 8, 8);
        } else {
            test_runner_console_color(1, 2, 8);
            fprintf(
                test_runner_global_instance.outstream,
                TEST_RUNNER_MSG_PASS,
                counter,
                test_runner_global_instance.test_count,
                test_case->name
            );
            test_runner_console_color(0, 8, 8);
        }

        test_runner_global_instance.case_list_current = 0;
        test_case = tmp_case;
        counter++;
    }
}

test_runner_case *test_runner_case_constructor()
{
    test_runner_case *test_case = (test_runner_case*)malloc(sizeof(test_runner_case));
    test_case->name = 0;
    test_case->test_case_function = 0;
    test_case->case_failed = 0;

    return test_case;
}

void test_runner_case_destructor(test_runner_case *test_case)
{
    if (test_case->name) {
        free(test_case->name);
    }

    if (test_case) {
        free(test_case);
    }
}

void test_runner_case_add(void (*cb)(), char *name)
{
    test_runner_case *test_case = test_runner_case_constructor();
    test_case->name = strdup(name);
    test_case->test_case_function = cb;

    if (test_runner_global_instance.case_list_tail == 0) {
        test_runner_global_instance.case_list_tail = test_case;
        test_runner_global_instance.case_list_head = test_case;
    } else {
        test_runner_global_instance.case_list_tail->next_case = test_case;
        test_runner_global_instance.case_list_tail = test_case;
    }

    test_runner_global_instance.test_count++;
}

void test_runner_console_color(int attr, int fg, int bg)
{
    if (test_runner_global_instance.outstream != stdout) {
        return;
    }

    char command[13];
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    fprintf(test_runner_global_instance.outstream, "%s", command);
}

void test_runner_op_assert(int x, int line, char *file)
{
    test_runner_global_instance.test_assert++;

    if (!x) {
        test_runner_console_color(1, 1, 8);
        fprintf(
            test_runner_global_instance.outstream,
            TEST_RUNNER_MSG_ASSERT_FAILED,
            file,
            line
        );
        test_runner_console_color(0, 8, 8);

        test_runner_global_instance.case_list_current->case_failed = 1;
        test_runner_global_instance.test_fail++;
    }
}

void test_runner_op_assert_equal_str(char *a, char *b, int line, char *file)
{
    test_runner_op_assert(strcmp(a, b) == 0, line, file);
}

