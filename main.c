//
//  main.c
//  sdb
//
//  Created by Quenio on 24/04/16.
//  Copyright © 2016 Quenio dos Santos. All rights reserved.
//

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

int read_command(char *command, int max_length)
{
    printf("sdb> ");
    char format[32];
    snprintf(format, sizeof(format), "%%%ds", max_length);
    return scanf(format, command);
}

const int max_command_length = 10;

void process_commands()
{
    char command[max_command_length];

    while (read_command(command, max_command_length))
    {
        printf("Command: %s\n", command);
        if (strncmp(command, "quit", max_command_length) == 0)
        {
            return;
        }
    }
}

struct Header
{
    uint8_t file_id[3];
    uint16_t file_version;
};
typedef struct Header Header;
Header header;

const uint8_t file_id[sizeof(header.file_id)] = "sdb";
const size_t header_size = sizeof(header.file_id) + sizeof(header.file_version);
const size_t header_count = 1;

size_t read_header(FILE *file, Header *header)
{
    return fread(header, header_size, header_count, file);
}

size_t write_header(FILE *file, Header *header)
{
    memcpy(header->file_id, file_id, sizeof(file_id));
    header->file_version = 1;
    return fwrite(header, header_size, header_count, file);
}

bool check_header(Header *header)
{
    return memcmp(header->file_id, file_id, sizeof(file_id)) == 0;
}

bool process_header(FILE *file, Header *header)
{
    if (read_header(file, header))
    {
        if (check_header(header))
        {
            printf("Simple DB header found. File version: %d\n", header->file_version);
            return true;
        }
        else
        {
            printf("Simple DB header not found.\n");
            return false;
        }
    }
    else if (write_header(file, header))
    {
        printf("Created Simple DB file.\n");
        return true;
    }
    else
    {
        printf("Could not write to Simple DB file.\n");
        return false;
    }
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
