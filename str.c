// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdlib.h>
#include <string.h>

#include "str.h"

char * str_append(char **str, char *extra)
{
    size_t new_length = strlen(*str) + strlen(extra) + 2;
    *str = realloc(*str, new_length);
    return strcat(*str, extra);
}