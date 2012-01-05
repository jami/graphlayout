#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

typedef struct _command_line_option
{
    char *input_file_path;
    char *output_file_path;
    int use_model;
    int use_verbose;
    int use_version;
} command_line_option;

command_line_option *command_line_option_constructor(int, char**);
void command_line_option_destruction(command_line_option*);

#endif
