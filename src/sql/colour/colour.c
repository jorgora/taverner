#include <sqlite3.h>
#include <stdio.h>

#include "../../../headers/sql/colour/colour.h"

Colour colour_data[] = {
    {"colourless", 255, 255, 255},
    {"black", 0, 0, 0},
    {"white", 255, 255, 255},
    {"light grey", 192, 192, 192},
    {"grey", 128, 128, 128},
    {"dark grey", 64, 64, 64},
    {"onyx", 53, 56, 57},
    {"jet", 52, 52, 52},
    {"oxford blue", 0, 33, 71},
    {"navy", 0, 0, 128},
    {"midnight blue", 25, 25, 112},
    {"sapphire", 15, 82, 186},
    {"blue", 0, 0, 255},
    {"azure", 0, 127, 255},
    {"steel blue", 70, 130, 180},
    {"royal blue", 65, 105, 225},
    {"cyan", 0, 255, 255},
    {"turquoise", 64, 224, 208},
    {"sky blue", 135, 206, 235},
    {"light blue", 173, 216, 230},
    {"teal", 0, 128, 128},
    {"maroon", 139, 0, 0},
    {"red", 255, 0, 0},
    {"rusty red", 183, 65, 14},
    {"ruby", 224, 17, 95},
    {"salmon", 250, 128, 114},
    {"hot pink", 255, 105, 180},
    {"pink", 255, 182, 193},
    {"rose", 255, 0, 127},
    {"peach", 255, 218, 185},
    {"dark green", 0, 100, 0},
    {"green", 0, 128, 0},
    {"sea green", 46, 139, 87},
    {"apple green", 141, 182, 0},
    {"emerald", 80, 200, 120},
    {"lime", 96, 255, 96},
    {"light green", 144, 238, 144},
    {"yellow", 255, 255, 0},
    {"dark yellow", 204, 204, 0},
    {"amber", 255, 191, 0},
    {"lavender", 230, 230, 250},
    {"purple", 128, 0, 128},
    {"indigo", 75, 0, 130},
    {"bluebell", 162, 162, 208},
    {"violet", 138, 43, 226},
    {"magenta", 255, 0, 255},
    {"orange", 255, 165, 0},
    {"dark orange", 255, 140, 0},
    {"tan", 210, 180, 140},
    {"brown", 165, 42, 42},
    {"dark brown", 101, 67, 33},
    {"chrome", 160, 160, 160},
    {"silver", 192, 192, 192},
    {"gold", 239, 191, 4},
    {"brass", 181, 166, 66},
    {"platinum", 229, 228, 226}
};

// create empty table
void colour_init(sqlite3* db)
{
    const char* create_table_sql = 
        "CREATE TABLE IF NOT EXISTS colour ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "r INTEGER NOT NULL CHECK(r >= 0 AND r <= 255), "
        "g INTEGER NOT NULL CHECK(g >= 0 AND g <= 255), "
        "b INTEGER NOT NULL CHECK(b >= 0 AND b <= 255));";

    char* err_msg = 0;

    int rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);

    //handle sql error
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        printf("Table created successfully\n");
    }
}

// put the colours into the table
void colour_insert(sqlite3* db)
{
    const char* insert_sql = "INSERT INTO colour (name, r, g, b) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);

    //handle sql error
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement\n");
        return;
    }

    // Loop through the colour data and insert each colour
    for (size_t i = 0; i < sizeof(colour_data) / sizeof(colour_data[0]); i++)
    {
        sqlite3_bind_text(stmt, 1, colour_data[i].name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, colour_data[i].r);
        sqlite3_bind_int(stmt, 3, colour_data[i].g);
        sqlite3_bind_int(stmt, 4, colour_data[i].b);

        rc = sqlite3_step(stmt);

        //handle insert error
        if (rc != SQLITE_DONE)
        {
            printf("Failed to insert data: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_reset(stmt);
    }

    //commit changes to the actual actual
    sqlite3_finalize(stmt);

    printf("Colours inserted successfully\n");
}

// function both inits and inserts data
int colour_create(sqlite3* db)
{
    colour_init(db);
    colour_insert(db);
    return 0;
}
