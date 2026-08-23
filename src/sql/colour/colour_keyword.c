#include <sqlite3.h>
#include <stdio.h>

#include "../../../headers/sql/colour/colour_keyword.h"

typedef enum {
    COLOUR_KEYWORD_NAME_BIND = 1
} ColourBindParam;


// Database string configuration constant
static const int STR_AUTO_LENGTH = -1;

static const Colour_keyword colour_keyword_data[] = {
    {"none"},

    {"light"},
    {"greyscale"},
    {"dark"},
    {"primary additive"},
    {"primary subtractive"},
    {"metallic"},
    {"earthy"},
    {"vivid"},
    {"muted"},
    {"pastel"},
    {"soft"},
    {"shadowy"},
    {"cool"},
    {"bold"},
    {"neon"},
    {"autumnal"},
    {"romantic"},
    {"gem-toned"},
    {"sky-toned"},
    {"fruit-toned"},
    {"meat-toned"},
    {"flower-toned"},
    {"warm"},

    // to tie all the shades of a colour together
    {"black"},
    {"white"},
    {"blue"},
    {"red"},
    {"purple"},
    {"pink"},
    {"green"},
    {"yellow"},
    {"orange"},
    {"brown"},
};

// create empty table
int colour_keyword_init(sqlite3* db)
{
    // sqlite create table query
    const char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS colour_keyword ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE CHECK(length(name) BETWEEN 1 AND 64));";

    // execute sqlite function (store result in int)
    // the nulls are callback function and callback args
    int return_code = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    // handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_init fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // exit
    printf("colour_keyword_init sucess\n");
    return return_code;
}


// insert data into table
int colour_keyword_insert(sqlite3* db)
{
    //sqlite insert query
    const char* insert_sql = "INSERT INTO colour_keyword (name) VALUES (?)";

    // pointer to store sqlite statement object
    sqlite3_stmt* stmt;

    // prepare sqlite statement (store result in int)
    // prepare for repeated use (sqlite3_step)
    // prepare does not return an errmsg
    int return_code = sqlite3_prepare_v2(db, insert_sql, STR_AUTO_LENGTH, &stmt, NULL);

    // handle errors
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_insert prepare fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // Begin transaction (avoids numerous individuals writes)
    return_code = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    // handle errors
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_insert transaction fail: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return return_code;
    }

    // Loop through colour data and insert each colour
    for (size_t i = 0; i < sizeof(colour_keyword_data) / sizeof(colour_keyword_data[0]); i++)
    {
        sqlite3_bind_text(stmt, COLOUR_KEYWORD_NAME_BIND, colour_keyword_data[i].name, STR_AUTO_LENGTH, SQLITE_STATIC);

        // insert one row of sqlite
        return_code = sqlite3_step(stmt);

        // error handling
        if (return_code != SQLITE_DONE)
        {
            // rollback
            fprintf(stderr, "colour_keyword_insert step fail after '%s': %s\n", colour_keyword_data[i].name, sqlite3_errmsg(db));
            printf("rolling back changes\n");
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
            sqlite3_finalize(stmt);
            return return_code;
        }

        // prepare for another sqlite_step(stmt)
        return_code = sqlite3_reset(stmt);

        // error handling
        if (return_code != SQLITE_OK)
        {
            // rollback
            fprintf(stderr, "colour_keyword_insert reset fail after '%s': %s\n", colour_keyword_data[i].name, sqlite3_errmsg(db));
            printf("rolling back changes\n");
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
            sqlite3_finalize(stmt);
            return return_code;
        }

        // explicitly set all parameters back to NULL (not necessary currently, may be removed)
        sqlite3_clear_bindings(stmt);
    }

    // commit transaction
    return_code = sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);

    // handle errors
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_insert commit fail: %s\n", sqlite3_errmsg(db));
        sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
        sqlite3_finalize(stmt);
        return return_code;
    }

    //commit changes to database
    sqlite3_finalize(stmt);

    //exit function
    printf("colour_keyword_insert success\n");
    return return_code;
}

// init then insert data into table
int colour_keyword_create(sqlite3* db)
{
    // init colour table
    int return_code = colour_keyword_init(db);

    // handle errors
    if (return_code != SQLITE_OK)
    {

        fprintf(stderr, "colour_keyword_create fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // insert colour data into colour table
    return_code = colour_keyword_insert(db);

    // handle errors
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_create fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // exit function
    printf("colour_keyword_create success\n");
    return return_code;
}

// return id given a name
int colour_keyword_get_id(sqlite3* db, const char* name)
{
    // sqlite colour_get_id query
    const char* sql_query =
        "SELECT id "
        "FROM colour_keyword "
        "WHERE name = ?;";

    // pointer to store sqlite statement object
    sqlite3_stmt* stmt;

    int return_code = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    // handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "colour_keyword_get_id prepare fail: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return_code = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    // handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr,"colour_keyword_get_id bind fail: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    return_code = sqlite3_step(stmt);

    if (return_code == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }

    // if it returns nothing
    if (return_code == SQLITE_DONE)
    {
        fprintf(stderr, "colour_keyword_get_id: colour '%s' not found\n", name);
        sqlite3_finalize(stmt);
        return -1;
    }

    fprintf(stderr, "colour_keyword_get_id step fail: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return -1;
}
