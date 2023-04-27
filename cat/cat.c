#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void cat_command(const char* path);

/*Internal Macros*/
#define ARGC_ERROR()    {   printf("More argument that it expected\n");\
                            exit(EXIT_FAILURE);\
                        }

#define PRINT_ERROR(comment)    {   printf("ERROR: %s\n",(const char*)comment);\
                                    exit(EXIT_FAILURE);\
                                }

#define ARGC_ERRORS()   {       if (argc < 2)\
                                {\
                                    PRINT_ERROR("Insufficient arguments");\
                                }\
                                else\
                                {\
                                    ARGC_ERROR();\
                                }\
}

#define DUMMY_CODE()        0U

int main(int argc, char const *argv[])
{
    printf("Hola mundo\n");
    
    cat_command("cat.c");
    return 0;
}


void cat_command(const char* path)
{
    FILE *fp;
    int character;
    struct stat file_info = {0};

    (stat(path,&file_info) == 0)?DUMMY_CODE() :(PRINT_ERROR("Unable to open or not exist")) ;

    if (S_ISDIR(file_info.st_mode) != 1)
    {
        printf("Usage: %s file\n", path);    
        fp = fopen(path, "r");
        
        if (fp == NULL) 
        {
            PRINT_ERROR("Can not open the file");
        }

        while ((character = fgetc(fp)) != EOF) 
        {
            putchar(character);
        }
        fclose(fp);
        printf("\n");
    }
    else
    {
        PRINT_ERROR("Is a directory")
    }
}