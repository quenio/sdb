// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#pragma once

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>

#include "packed_structs.h"

#define SIGNATURE_SIZE 3

packed_struct Header
{
    uint8_t signature[SIGNATURE_SIZE];
    uint16_t version;
};
typedef struct Header Header;

bool process_header(FILE *file, Header *header);
