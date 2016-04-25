// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define PROMPT "sdb> "
#define FORMAT "%%%ds"

const size_t format_size = 32;
const int max_command_length = 10;

int read_command(char *command, int max_length)
{
    printf(PROMPT);
    char format[format_size];
    snprintf(format, sizeof(format), FORMAT, max_length);
    return scanf(format, command);
}

bool is_command(char *actual_command, char *expected_command)
{
    return strncmp(actual_command, expected_command, max_command_length) == 0;
}

void process_commands()
{
    char command[max_command_length];

    while (read_command(command, max_command_length))
    {
        printf("Command: %s\n", command);
        if (is_command(command, "quit"))
        {
            return;
        }
    }
}


