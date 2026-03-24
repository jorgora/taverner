#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "../headers/sql/colour/colour.h"

// Handle command-line arguments and print them
void handle_cmd_args(int argc, char** argv)
{
    if (argc > 1)
    {
        printf("Command-line Arguments\n");
        for (size_t i = 1; (int)i < argc; i++)
        {
            printf("\tArg(%d):\t%s\n", (int)i, argv[i]);
        }

        printf("\n");
    }
}

int main(int argc, char** argv)
{
    // Handle command-line arguments
    handle_cmd_args(argc, argv);

    // create db pointer
    sqlite3* db;

    //use pointer to open databse
    int rc = sqlite3_open("taverner.db", &db);

    //handle database not openning
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        printf("Opened database successfully\n");
    }

    // create colour table
    colour_create(db);

    // close database
    sqlite3_close(db);

    // end program
    return EXIT_SUCCESS;
}
