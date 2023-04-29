#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "touch.h"

void touch_command(const char* file_name)
{
    struct utimbuf timestamps;
    time_t now;
    int status;
    int fd;

    /* Get the current time */
    now = time(NULL);

    /* Use the current time as the new access and modification dates and try to updated the file */
    timestamps.actime = now;
    timestamps.modtime = now;
    status = utime(file_name, &timestamps);

    /* Program enters here if it was not possible to update the timestamps of the file */
    if (status != 0)
    {
        /* Create the file if it does not exist with 0664 permissions */
        fd = open(file_name, O_CREAT, 0664);
        if (fd == -1)
        {
            perror("Error");
        }
        else
        {
            /* On success, notify that the file has been created and then close it */
            printf("File created successfully!\n");
            close(fd);
        }
    }
    /* Program enters here if timestamps have been updated successfully */
    else
    {
        printf("Timestamps modified successfully!\n");
    }

}
