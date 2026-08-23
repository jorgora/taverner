#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "../headers/sql/colour/colour.h"
#include "../headers/sql/colour/colour_keyword.h"
#include "../headers/sql/colour/colour_keyword_relation.h"

// Handle command-line arguments and print them
void handle_cmd_args(int argc, char** argv)
{
    if (argc > 1)
    {
        printf("Command-line Arguments\n");
        for (int i = 1; (int)i < argc; i++)
        {
            printf("\tArg(%d):\t%s\n", i, argv[i]);
        }

        printf("\n");
    }
}

void colour_print(sqlite3* db)
{
    printf("colour_get_id('colourless') = %d\n", colour_get_id(db, "colourless"));
    printf("colour_get_id('black') =  %d\n", colour_get_id(db, "black"));
    printf("colour_get_id('white') =  %d\n", colour_get_id(db, "white"));
    printf("colour_get_id('ERROR_COLOUR') =  %d\n\n", colour_get_id(db, "ERROR_COLOUR"));
}

void colour_keyword_print(sqlite3* db)
{
    printf("colour_keyword_get_id('none') = %d\n", colour_keyword_get_id(db, "none"));
    printf("colour_keyword_get_id('light') =  %d\n", colour_keyword_get_id(db, "light"));
    printf("colour_keyword_get_id('greyscale') =  %d\n", colour_keyword_get_id(db, "greyscale"));
    printf("colour_keyord_get_id('ERROR_COLOUR_KEYWORD') =  %d\n\n", colour_keyword_get_id(db, "ERROR_COLOUR_KEYWORD"));
}

int main(int argc, char** argv)
{
    // Handle command-line arguments
    handle_cmd_args(argc, argv);

    // create db pointer
    sqlite3* db;

    // use pointer to open databse
    int rc = sqlite3_open("taverner.db", &db);

    // handle database not openning
    if (rc)
    {
        // if fail, exit
        fprintf(stderr, "open database fail: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // if success, run program
    printf("open database success\n");

    // create colour table
    colour_create(db);
    colour_print(db);

    // create colour_keyword table
    colour_keyword_create(db);
    colour_keyword_print(db);

    // create colour_keyword_relation_table
    colour_keyword_relation_create(db);

    // close database
    sqlite3_close(db);

    // end program
    return EXIT_SUCCESS;
}
