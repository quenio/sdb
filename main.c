// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdio.h>

#include "file_header.h"
#include "db_file.h"
#include "commands.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sdb path/file.db\n");
    }
    else
    {
        const char *file_path = argv[1];

        FILE *file = open_db(file_path);
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
