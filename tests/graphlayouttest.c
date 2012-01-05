#include "config.h"
#include "testframework.h"
#include "commandline.h"
#include "document.h"

void graph_test_run();

void graph_test()
{
    graph_test_run();
}

void commandline_test()
{
    int argc;
    /**
     * check single version flag
     */
    /*char *argv_1[] = {
        "program_bin"
        "--verbose",
    };*/
    argc = 2;/*
    command_line_option *option = command_line_option_constructor(argc, argv_1);
    TEST_ASSERT(option->input_file_path == 0);
    TEST_ASSERT(option->output_file_path == 0);
    TEST_ASSERT(option->use_verbose == 1);
    command_line_option_destruction(option);*/
}

void layoutdocument_test()
{
    layout_document *document = layout_document_constructor();
    TEST_ASSERT(document != 0);

    char filename[] = "test_graph_file1.grp";
    char filepath[] = TESTDATAPATH;
    strcat(filepath, filename);

    layout_document_read_file(document, filepath);

    //layout_document_dump(document);

    layout_document_destructor(document);
}

void simpletest() {
    int foo = 1;
    TEST_ASSERT(foo);
    TEST_ASSERT_EQUAL_STR("abc", "abc");
}

void simpletest2() {
    TEST_ASSERT(1 == 1);
    TEST_ASSERT('c' == 'c');
}

int main()
{
    TEST_RUNNER_SETUP;
    TEST_RUNNER_CASE_ADD(graph_test, "graph elements");
    TEST_RUNNER_CASE_ADD(commandline_test, "commandline");
    TEST_RUNNER_CASE_ADD(layoutdocument_test, "layoutdocument");
    TEST_RUNNER_CASE_ADD(simpletest2, "Test nummer 2");
    TEST_RUNNER_RUN;
    TEST_RUNNER_DESTROY;
    return TEST_RUNNER_FAILED;
}
