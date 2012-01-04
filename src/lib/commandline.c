#include "commandline.h"

command_line_option *command_line_option_constructor(int argc, char **argv)
{
    command_line_option *option = malloc(sizeof(command_line_option));

    return option;
}

void command_line_option_destruction(command_line_option *option)
{
    free(option);
}
