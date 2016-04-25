// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdio.h>

#include "file_header.h"
#include "commands.h"

FILE *open_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r+");

    if (file)
    {
        printf("Opened file: %s\n", file_path);
    }
    else
    {
        file = fopen(file_path, "w");
        if (file)
        {
            printf("Created file: %s\n", file_path);
        }
        else
        {
            printf("Could not open file: %s\n", file_path);
        }
    }

    return file;
}

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sdb path/file.db\n");
    }
    else
    {
        const char *file_path = argv[1];

        FILE *file = open_file(file_path);
        if (file)
        {
            Header header;
            if (process_header(file, &header))
            {
                printf("Ready to use database.\n");
                process_commands();
            }
            else
            {
                printf("Will not touch file: %s\n", file_path);
            }

            fclose(file);
        }
    }
    return 0;
}
