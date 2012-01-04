#include <stdio.h>
#include <stdlib.h>
#include "commandline.h"

int main (int argc, char *argv[])
{
    command_line_option *option = command_line_option_constructor(argc, argv);



    command_line_option_destruction(option);
    return 0;
}
