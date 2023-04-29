#ifndef ARGUMENT_PROCESSING
#define ARGUMENT_PROCESSING


#include<unistd.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdio.h>
#include<string.h>

#include<stdbool.h>
#include <getopt.h>

#define COMMAND_RM  "rm"
#define COMMAND_CP  "cp"

#define CP_RECURSIVE_OPT 0x00000001
#define RM_RECURSIVE_OPT 0x00000001

typedef enum command_t {
    rm,
    cp,
    undefined
} command_type;

const char * first_argument_processing(const char * const arg);
bool supported_command(const char * const arg);
int supported_options_cp(int argc, char** argv);
int supported_options_rm(int argc, char** argv);

#endif