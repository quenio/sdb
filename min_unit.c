// Copyright (c) 2016 Quenio Cesar Machado dos Santos. All rights reserved.
// Original Code: http://www.jera.com/techinfo/jtns/jtn002.html#License

#include <stdio.h>

char * all_tests();

int tests_run = 0;
int tests_failed = 0;

int main(int argc, char **argv)
{
    printf("\n");

    all_tests();

    printf("\nTests Run: %d - Tests Failed: %d\n", tests_run, tests_failed);

    if (tests_failed == 0)
    {
        printf("ALL TESTS PASSED\n");
    }

    return tests_failed;
}
