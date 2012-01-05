#include <getopt.h>
#include "commandline.h"

command_line_option *command_line_option_constructor(int argc, char **argv)
{
    command_line_option *option = malloc(sizeof(command_line_option));
    option->input_file_path     = 0;
    option->output_file_path    = 0;
    option->use_model           = 0;
    option->use_verbose         = 0;
    option->use_version         = 0;

    struct option long_options[] = {
        // flags
        {"verbose", no_argument, 0, 'v'},
        {"version", no_argument, 0, 'V'},
        // parameter
        {"inputfile", required_argument, 0, 'i'},
        {"outputfile", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    while (1) {
        int option_index = 0;
        char c = getopt_long (argc, argv, "ac:", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch (c) {
            case 'V':
                option->use_version = 1;
                break;
            case 'v':
                option->use_verbose = 1;
                break;
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;

                printf("option %s", long_options[option_index].name);

                if (optarg)
                    printf(" with arg %s", optarg);

                printf("\n");
                break;
            case 'i':
                option->input_file_path = strdup(optarg);
                break;
            case 'o':
                option->output_file_path = strdup(optarg);
                break;
            case '?':
                break;
            default:
                printf("ERROR abort!\n");
                exit(1);
        }
    }

    return option;
}

void command_line_option_destruction(command_line_option *option)
{
    if (option->input_file_path) {
        free(option->input_file_path);
    }

    if (option->output_file_path) {
        free(option->output_file_path);
    }

    free(option);
}
