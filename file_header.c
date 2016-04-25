// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "file_header.h"

const uint8_t signature[SIGNATURE_SIZE] = "sdb";
const uint16_t version = 1;
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


