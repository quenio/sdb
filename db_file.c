// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include "db_file.h"

FILE *open_db(const char *file_path)
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
