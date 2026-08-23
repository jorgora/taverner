#include <sqlite3.h>
#include <stdio.h>

#include "../../../headers/sql/colour/colour.h"
#include "../../../headers/sql/sql_utils.h"

// enum to show binds in function (remove magic number)
typedef enum {
    COLOUR_NAME_BIND = 1,
    COLOUR_R_BIND = 2,
    COLOUR_G_BIND = 3,
    COLOUR_B_BIND = 4
} ColourBindParam;

// Database string configuration constant
static const int STR_AUTO_LENGTH = -1;

// colour data to insert into sqlite table
static const Colour colour_data[] = {
//  {name               R,   G,   B},
    {"colourless",    255, 255, 255},
    {"black",           0,   0,   0},
    {"white",         255, 255, 255},
    {"light grey",    192, 192, 192},
    {"grey",          128, 128, 128},
    {"dark grey",      64,  64,  64},
    {"onyx",           53,  56,  57},
    {"jet",            52,  52,  52},
    {"oxford blue",     0,  33,  71},
    {"navy",            0,   0, 128},
    {"midnight blue",  25,  25, 112},
    {"sapphire",       15,  82, 186},
    {"blue",            0,   0, 255},
    {"azure",           0, 127, 255},
    {"steel blue",     70, 130, 180},
    {"royal blue",     65, 105, 225},
    {"cyan",            0, 255, 255},
    {"turquoise",      64, 224, 208},
    {"sky blue",      135, 206, 235},
    {"light blue",    173, 216, 230},
    {"teal",            0, 128, 128},
    {"maroon",        139,   0,   0},
    {"red",           255,   0,   0},
    {"rusty red",     183,  65,  14},
    {"ruby",          224,  17,  95},
    {"salmon",        250, 128, 114},
    {"hot pink",      255, 105, 180},
    {"pink",          255, 182, 193},
    {"rose",          255,   0, 127},
    {"peach",         255, 218, 185},
    {"dark green",      0, 100,   0},
    {"green",           0, 128,   0},
    {"sea green",      46, 139,  87},
    {"apple green",   141, 182,   0},
    {"emerald",        80, 200, 120},
    {"lime",           96, 255,  96},
    {"light green",   144, 238, 144},
    {"yellow",        255, 255,   0},
    {"dark yellow",   204, 204,   0},
    {"amber",         255, 191,   0},
    {"lavender",      230, 230, 250},
    {"purple",        128,   0, 128},
    {"indigo",         75,   0, 130},
    {"bluebell",      162, 162, 208},
    {"violet",        138,  43, 226},
    {"magenta",       255,   0, 255},
    {"orange",        255, 165,   0},
    {"dark orange",   255, 140,   0},
    {"tan",           210, 180, 140},
    {"brown",         165,  42,  42},
    {"dark brown",    101,  67,  33},
    {"chrome",        160, 160, 160},
    {"silver",        192, 192, 192},
    {"gold",          239, 191,   4},
    {"brass",         181, 166,  66},
    {"platinum",      229, 228, 226}
};

// create empty table
int colour_init(sqlite3* db)
{
    // sqlite create_table query
    const char* create_table_query =
        "CREATE TABLE IF NOT EXISTS colour ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE CHECK(length(name) BETWEEN 1 AND 64), "
        "r INTEGER NOT NULL CHECK(r >= 0 AND r <= 255), "
        "g INTEGER NOT NULL CHECK(g >= 0 AND g <= 255), "
        "b INTEGER NOT NULL CHECK(b >= 0 AND b <= 255));";

    return sql_exec("colour_init", db, create_table_query);
}

// insert date into table
int colour_insert(sqlite3* db)
{
    //sqlite insert query
    const char* insert_sql = "INSERT INTO colour (name, r, g, b) VALUES (?, ?, ?, ?)";

    // pointer to store sqlite statement object
    sqlite3_stmt* stmt;

    // prepare sqlite statement (store result in int)
    // prepare for repeated use (sqlite3_step)
    // prepare does not return an errmsg
    int return_code = sqlite3_prepare_v2(db, insert_sql, STR_AUTO_LENGTH, &stmt, NULL);

    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "ERROR: colour_insert prepare fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // Begin transaction (avoids numerous individuals writes)
    return_code = sql_exec("colour_insert_begin_transaction", db, "BEGIN TRANSACTION;");

    // Loop through colour data and insert each colour
    for (size_t i = 0; i < sizeof(colour_data) / sizeof(colour_data[0]); i++)
    {
        sqlite3_bind_text(stmt, COLOUR_NAME_BIND, colour_data[i].name, STR_AUTO_LENGTH, SQLITE_STATIC);
        sqlite3_bind_int(stmt, COLOUR_R_BIND, colour_data[i].r);
        sqlite3_bind_int(stmt, COLOUR_G_BIND, colour_data[i].g);
        sqlite3_bind_int(stmt, COLOUR_B_BIND, colour_data[i].b);

        // insert one row of sqlite
        return_code = sqlite3_step(stmt);

        if (return_code != SQLITE_DONE)
        {
            // rollback
            fprintf(stderr, "ERROR: colour_insert step fail after '%s': %s\n", colour_data[i].name, sqlite3_errmsg(db));
            return_code = sql_exec("colour_insert_rollback", db, "ROLLBACK;");
            sqlite3_finalize(stmt);
            return return_code;
        }

        // prepare for another sqlite_step(stmt)
        return_code = sqlite3_reset(stmt);

        if (return_code != SQLITE_OK)
        {
            // rollback
            fprintf(stderr, "ERROR: colour_insert reset fail after '%s': %s\n", colour_data[i].name, sqlite3_errmsg(db));
            return_code = sql_exec("colour_insert_rollback", db, "ROLLBACK;");
            sqlite3_finalize(stmt);
            return return_code;
        }

        // explicitly set all parameters back to NULL (not necessary currently, may be removed)
        sqlite3_clear_bindings(stmt);
    }

    // commit transaction
    return_code = sql_exec("colour_insert_commit", db, "COMMIT");

    //commit changes to database
    sqlite3_finalize(stmt);

    //exit function
    printf("colour_insert success\n");
    return return_code;
}

// init then insert data into table
int colour_create(sqlite3* db)
{
    // init colour table
    int return_code = colour_init(db);

    if (return_code != SQLITE_OK)
    {

        fprintf(stderr, "ERROR: colour_create fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // insert colour data into colour table
    return_code = colour_insert(db);

    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "ERROR: colour_create fail: %s\n", sqlite3_errmsg(db));
        return return_code;
    }

    // exit function
    printf("colour_create success\n");
    return return_code;
}

// return id given a name
int colour_get_id(sqlite3* db, const char* name)
{
    // sqlite colour_get_id query
    const char* sql_query =
        "SELECT id "
        "FROM colour "
        "WHERE name = ?;";

    // pointer to store sqlite statement object
    sqlite3_stmt* stmt;

    int return_code = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "ERROR: colour_get_id prepare fail: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return_code = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (return_code != SQLITE_OK)
    {
        fprintf(stderr,"ERROR: colour_get_id bind fail: %s\n", sqlite3_errmsg(db));
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

    if (return_code == SQLITE_DONE)
    {
        fprintf(stderr, "ERROR: colour_get_id: colour '%s' not found\n", name);
        sqlite3_finalize(stmt);
        return -1;
    }

    fprintf(stderr, "ERROR: colour_get_id step fail: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return -1;
}
