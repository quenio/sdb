#include <lzma.h>//
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
#include <arpa/inet.h>

#include "packed_structs.h"

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

const size_t signature_size = 3;
const uint8_t signature[signature_size] = "sdb";

const uint16_t version = 1;

packed_struct Header
{
    uint8_t signature[signature_size];
    uint16_t version;
};
typedef struct Header Header;

const size_t header_count = 1;

size_t read_header(FILE *file, Header *header)
{
    size_t read_count = fread(header, sizeof(Header), header_count, file);
    header->version = ntohs(header->version);
    return read_count;
}

size_t write_header(FILE *file, Header *header)
{
    memcpy(header->signature, signature, sizeof(signature));
    header->version = htons(version);
    size_t write_count = fwrite(header, sizeof(Header), header_count, file);
    header->version = version;
    return write_count;
}

bool check_header(Header *header)
{
    return memcmp(header->signature, signature, sizeof(signature)) == 0 && header->version <= version;
}

bool process_header(FILE *file, Header *header)
{
    if (read_header(file, header))
    {
        if (check_header(header))
        {
            printf("Simple DB File. Version: %d\n", header->version);
            return true;
        }
        else
        {
            printf("Not a Simple DB file. Check file path or file version.\n");
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
