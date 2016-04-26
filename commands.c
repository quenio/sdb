// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "sdb> "
#define BUFFER_FORMAT "%%%ds"
#define COMMAND_TERMINATOR ';'

const size_t format_size = 32;
const int command_buffer_length = 10;

int read_command(char **command)
{
    printf(PROMPT);

    char format[format_size];
    snprintf(format, sizeof(format), BUFFER_FORMAT, command_buffer_length - 1);

    **command = '\0';

    size_t command_length = 1;
    char buffer[command_buffer_length];
    while (scanf(format, buffer)) {
        command_length += strlen(buffer);
        *command = realloc(*command, command_length);
        strcat(*command, buffer);
        if (strrchr(*command, COMMAND_TERMINATOR) != NULL) {
            break;
        }
    }

    return strlen(*command) > 0;
}

bool is_command(char *actual_command, char *expected_command)
{
    return strncmp(actual_command, expected_command, command_buffer_length) == 0;
}

void process_commands()
{
    char *command = malloc(1);
    while (read_command(&command))
    {
        printf("Command: %s\n", command);
        if (is_command(command, "quit;"))
        {
            break;
        }
    }
    free(command);
}


