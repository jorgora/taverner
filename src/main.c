#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "../headers/test_file.h"

// Handle command-line arguments and print them
void handle_cmd_args(int argc, char** argv)
{
    if (argc > 1)
    {
        printf("Command-line Arguments\n");
        for (int i = 1; i < argc; i++)
        {
            printf("\tArg(%d):\t%s\n", i, argv[i]);
        }

        printf("\n");
    }
}

int main(int argc, char** argv)
{
    // Handle command-line arguments
    handle_cmd_args(argc, argv);

    // Call the function from test_file.c to print "Hello, World!"
    print_hello_world();

    return EXIT_SUCCESS;
}
