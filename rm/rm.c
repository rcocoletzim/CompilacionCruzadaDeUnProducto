#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <sys/sendfile.h>
#include <dirent.h>

#include "argument_processing.h"
#include "rm.h"

static void remove_file(char* path)
{
    struct stat src_sb;
    if (stat(path, &src_sb) != -1) { 
        if((src_sb.st_mode  & S_IFMT) == S_IFDIR)
        {
            if(rmdir(path) == -1)
            {
                fprintf(stderr,"Directory %s must be empty\n", path);
            }
        }
        else
        {
            remove(path);
        }
    }
    else
    {    
        fprintf(stderr, "file %s does not exist\n", path);
    } 
}

static void delete_recursive_files(const char *source)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(source)))
    {
        fprintf(stderr,"source: %s\n",source);
        perror("opendir");
        return;
    }
        

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_type == DT_DIR) {
            char src_path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(src_path, sizeof(src_path), "%s/%s", source, entry->d_name);
            delete_recursive_files(src_path);
        } else {
            char src_file_path[1024];
            snprintf(src_file_path, sizeof(src_file_path), "%s/%s", source, entry->d_name);
            remove_file(src_file_path);
        }
    }
    closedir(dir);
    remove_file((char *)source);
}



void processing_cases_rm(int argc, char* argv, int flags)
{   
    if((flags & CP_RECURSIVE_OPT ) == CP_RECURSIVE_OPT)
    {
        // struct stat src_sb;
        // //Recursive flags set
        // if(argc == 3)
        // {
        //     if (stat(argv, &src_sb) != -1) {
                    
        //         if((src_sb.st_mode  & S_IFMT) == S_IFDIR)
        //         {
        //             delete_recursive_files(argv);
        //         }
        //         else
        //         {
        //             remove_file(argv);
        //         }
        //     }
        // }
        // else if (argc > 3)
        // {
        //     int counter;
            
        //     for(counter = 2; counter < argc; counter++)
        //     {
        //         if (stat(argv[counter], &src_sb) != -1) {
                    
        //             if((src_sb.st_mode  & S_IFMT) == S_IFDIR)
        //             {
        //                 delete_recursive_files(argv[counter]);
        //             }
        //             else
        //             {
        //                 remove_file(argv[counter]);
        //             }
        //         }
        //     }
        // } 
    }
    else
    {
        //case1: rm FILE1/DIRECTORY 
        if(argc == 2)
        {
           remove_file(argv);
        }
        //case2: cp FILE1 FILE2 ... FILEN
        // else if( argc > 2)
        // {
        //     int counter;
        //     for(counter = 1; counter < argc; counter++)
        //     {
        //         remove_file(argv[counter]);
        //     }
        // }
    }
}

