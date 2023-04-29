
#include "argument_processing.h"

const char * first_argument_processing(const char * const arg)
{
    const char *delim = "/";
    char *prev_token;
    char *token = strtok((char *)arg, delim);
    while(token) {
        prev_token = token;
        token = strtok(NULL, delim);
    }
    return prev_token;
}

bool supported_command(const char * const command)
{
    command_type _command = undefined;
    if(strcmp(COMMAND_RM,command) == 0)
    {
        _command = rm;
    }
    else if(strcmp(COMMAND_CP,command) == 0)
    {
        _command = cp;
    }
    return (_command != undefined)?true:false;
}

int supported_options_cp(int argc, char** argv)
{
    int opt;
    int flags = 0U;

    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch (opt) {
        case 'r':
            flags  |= CP_RECURSIVE_OPT;
            break;
        default:
            fprintf(stderr, " %s : Option not supported\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    return flags;
}

int supported_options_rm(int argc, char** argv)
{
    int opt;
    int flags = 0U;

    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch (opt) {
        case 'r':
            flags  |= RM_RECURSIVE_OPT;
            break;
        default:
            fprintf(stderr, " %s : Option not supported\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    return flags;
}