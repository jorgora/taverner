#include <sqlite3.h>
#include <stdio.h>

#include "../../../headers/sql/colour/colour_keyword_relation.h"
#include "../../../headers/sql/colour/colour.h"
#include "../../../headers/sql/colour/colour_keyword.h"
#include "../../../headers/sql/sql_utils.h"


typedef enum {
    COLOUR_KEYWORD_RELATION_COLOUR_BIND = 1,
    COLOUR_KEYWORD_RELATION_KEYWORD_BIND = 2
} ColourKeywordRelationBindParam;


// Database string configuration constant
static const int STR_AUTO_LENGTH = -1;

// Relation data to insert into sqlite table
static const ColourKeywordRelation colour_keyword_relation_data[] = {

    // Neutral colours
    {"colourless", "none"},

    //black
    {"black", "dark"},
    {"black", "greyscale"},
    {"black", "shadowy"},
    {"black", "black"},

    //white
    {"white", "light"},
    {"white", "greyscale"},
    {"white", "white"},

    // grey
    {"light grey", "light"},
    {"light grey", "greyscale"},

    {"grey", "greyscale"},

    {"dark grey", "dark"},
    {"dark grey", "greyscale"},
    {"dark grey", "shadowy"},

    // black
    {"onyx", "dark"},
    {"onyx", "greyscale"},
    {"onyx", "shadowy"},
    {"onyx", "black"},

    {"jet", "dark"},
    {"jet", "greyscale"},
    {"jet", "shadowy"},
    {"jet", "black"},

    // blue
    {"oxford blue", "dark"},
    {"oxford blue", "cool"},
    {"oxford blue", "blue"},

    {"navy", "dark"},
    {"navy", "cool"},
    {"navy", "blue"},

    {"midnight blue", "dark"},
    {"midnight blue", "cool"},
    {"midnight blue", "blue"},

    {"sapphire", "vivid"},
    {"sapphire", "gem-toned"},
    {"sapphire", "cool"},
    {"sapphire", "blue"},

    {"blue", "primary additive"},
    {"blue", "cool"},
    {"blue", "vivid"},
    {"blue", "blue"},

    {"azure", "vivid"},
    {"azure", "cool"},
    {"azure", "blue"},
    {"azure", "sky-toned"},

    {"steel blue", "muted"},
    {"steel blue", "cool"},
    {"steel blue", "blue"},

    {"royal blue", "vivid"},
    {"royal blue", "cool"},
    {"royal blue", "blue"},

    {"cyan", "primary subtractive"},
    {"cyan", "vivid"},
    {"cyan", "bold"},
    {"cyan", "neon"},
    {"cyan", "cool"},
    {"cyan", "blue"},

    {"turquoise", "vivid"},
    {"turquoise", "cool"},
    {"turquoise", "blue"},

    {"sky blue", "light"},
    {"sky blue", "cool"},
    {"sky blue", "sky-toned"},
    {"sky blue", "blue"},

    {"light blue", "light"},
    {"light blue", "cool"},
    {"light blue", "pastel"},
    {"light blue", "sky-toned"},
    {"light blue", "blue"},

    {"teal", "cool"},
    {"teal", "muted"},
    {"teal", "blue"},

    // red
    {"maroon", "dark"},
    {"maroon", "muted"},
    {"maroon", "red"},

    {"red", "primary additive"},
    {"red", "vivid"},
    {"red", "bold"},
    {"red", "red"},

    {"rusty red", "earthy"},
    {"rusty red", "muted"},
    {"rusty red", "autumnal"},
    {"rusty red", "red"},

    {"ruby", "vivid"},
    {"ruby", "gem-toned"},
    {"ruby", "red"},

    {"rose", "vivid"},
    {"rose", "romantic"},
    {"rose", "bold"},
    {"rose", "red"},

    // pink
    {"salmon", "light"},
    {"salmon", "pastel"},
    {"salmon", "soft"},
    {"salmon", "pink"},

    {"hot pink", "vivid"},
    {"hot pink", "bold"},
    {"hot pink", "romantic"},
    {"hot pink", "pink"},

    {"pink", "light"},
    {"pink", "pastel"},
    {"pink", "soft"},
    {"pink", "romantic"},
    {"pink", "pink"},

    {"peach", "light"},
    {"peach", "pastel"},
    {"peach", "soft"},
    {"peach", "fruit-toned"},
    {"peach", "pink"},

    // green
    {"dark green", "dark"},
    {"dark green", "cool"},
    {"dark green", "green"},

    {"green", "primary additive"},
    {"green", "vivid"},
    {"green", "green"},

    {"sea green", "cool"},
    {"sea green", "muted"},
    {"sea green", "green"},

    {"apple green", "vivid"},
    {"apple green", "fruit-toned"},
    {"apple green", "green"},

    {"emerald", "vivid"},
    {"emerald", "gem-toned"},
    {"emerald", "cool"},
    {"emerald", "green"},

    {"lime", "vivid"},
    {"lime", "bold"},
    {"lime", "neon"},
    {"lime", "fruit-toned"},
    {"lime", "green"},

    {"light green", "light"},
    {"light green", "pastel"},
    {"light green", "soft"},
    {"light green", "green"},

    // yellow
    {"yellow", "primary subtractive"},
    {"yellow", "vivid"},
    {"yellow", "bold"},
    {"yellow", "yellow"},

    {"dark yellow", "dark"},
    {"dark yellow", "muted"},
    {"dark yellow", "yellow"},

    {"amber", "vivid"},
    {"amber", "warm"},
    {"amber", "autumnal"},

    // purple
    {"lavender", "light"},
    {"lavender", "pastel"},
    {"lavender", "soft"},
    {"lavender", "romantic"},
    {"lavender", "purple"},

    {"purple", "vivid"},
    {"purple", "bold"},
    {"purple", "purple"},

    {"indigo", "dark"},
    {"indigo", "cool"},
    {"indigo", "gem-toned"},

    {"bluebell", "pastel"},
    {"bluebell", "soft"},
    {"bluebell", "cool"},

    {"violet", "vivid"},
    {"violet", "bold"},
    {"violet", "romantic"},
    {"violet", "purple"},

    {"magenta", "primary subtractive"},
    {"magenta", "vivid"},
    {"magenta", "bold"},
    {"magenta", "purple"},

    // orange
    {"orange", "vivid"},
    {"orange", "bold"},
    {"orange", "fruit-toned"},
    {"orange", "orange"},

    {"dark orange", "dark"},
    {"dark orange", "autumnal"},
    {"dark orange", "orange"},

    // brown
    {"tan", "light"},
    {"tan", "muted"},
    {"tan", "earthy"},
    {"tan", "brown"},

    {"brown", "dark"},
    {"brown", "earthy"},
    {"brown", "brown"},

    {"dark brown", "dark"},
    {"dark brown", "earthy"},
    {"dark brown", "shadowy"},
    {"dark brown", "brown"},

    // metal
    {"chrome", "metallic"},
    {"chrome", "cool"},

    {"silver", "metallic"},
    {"silver", "light"},

    {"gold", "metallic"},
    {"gold", "bold"},
    {"gold", "yellow"},

    {"brass", "metallic"},
    {"brass", "earthy"},
    {"brass", "brown"},

    {"platinum", "metallic"},
    {"platinum", "light"},
    {"platinum", "cool"}
};

// Create empty table
int colour_keyword_relation_init(sqlite3* db)
{
    const char* create_table_query =
        "CREATE TABLE IF NOT EXISTS colour_keyword_relation ("
        "colour INTEGER NOT NULL, "
        "keyword INTEGER NOT NULL, "
        "FOREIGN KEY (colour) REFERENCES colour(id), "
        "FOREIGN KEY (keyword) REFERENCES colour_keyword(id), "
        "PRIMARY KEY (colour, keyword));";

    return sql_exec("colour_keyword_relation_init", db, create_table_query);
}


// Insert into table
int colour_keyword_relation_insert(sqlite3* db)
{
    const char* insert_sql =
        "INSERT INTO colour_keyword_relation "
        "(colour, keyword) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt;

    int return_code = sqlite3_prepare_v2(
        db,
        insert_sql,
        STR_AUTO_LENGTH,
        &stmt,
        NULL
    );

    // Handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(
            stderr,
            "colour_keyword_relation_insert prepare fail: %s\n",
            sqlite3_errmsg(db)
        );

        return return_code;
    }

    // Begin transaction (avoids numerous individuals writes)
    return_code = sql_exec("colour_keyword_relation_insert_begin_transaction", db, "BEGIN TRANSACTION;");

    // Loop through relation data
    size_t relation_count =
        sizeof(colour_keyword_relation_data) /
        sizeof(colour_keyword_relation_data[0]);

    for (size_t i = 0; i < relation_count; i++)
    {
        /*
         * Convert the colour name into its database ID.
         */
        int colour_id = colour_get_id(
            db,
            colour_keyword_relation_data[i].colour
        );

        if (colour_id == -1)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert: "
                "colour '%s' not found\n",
                colour_keyword_relation_data[i].colour
            );

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return SQLITE_ERROR;
        }


        /*
         * Convert the keyword name into its database ID.
         */
        int keyword_id = colour_keyword_get_id(
            db,
            colour_keyword_relation_data[i].keyword
        );

        if (keyword_id == -1)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert: "
                "keyword '%s' not found\n",
                colour_keyword_relation_data[i].keyword
            );

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return SQLITE_ERROR;
        }


        /*
         * Bind colour ID.
         */
        return_code = sqlite3_bind_int(
            stmt,
            COLOUR_KEYWORD_RELATION_COLOUR_BIND,
            colour_id
        );

        if (return_code != SQLITE_OK)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert "
                "colour bind fail: %s\n",
                sqlite3_errmsg(db)
            );

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return return_code;
        }


        /*
         * Bind keyword ID.
         */
        return_code = sqlite3_bind_int(
            stmt,
            COLOUR_KEYWORD_RELATION_KEYWORD_BIND,
            keyword_id
        );

        if (return_code != SQLITE_OK)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert "
                "keyword bind fail: %s\n",
                sqlite3_errmsg(db)
            );

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return return_code;
        }


        /*
         * Insert one relation.
         */
        return_code = sqlite3_step(stmt);

        if (return_code != SQLITE_DONE)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert "
                "step fail after '%s' -> '%s': %s\n",
                colour_keyword_relation_data[i].colour,
                colour_keyword_relation_data[i].keyword,
                sqlite3_errmsg(db)
            );

            printf("rolling back changes\n");

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return return_code;
        }


        /*
         * Prepare statement for next relation.
         */
        return_code = sqlite3_reset(stmt);

        if (return_code != SQLITE_OK)
        {
            fprintf(
                stderr,
                "colour_keyword_relation_insert "
                "reset fail after '%s' -> '%s': %s\n",
                colour_keyword_relation_data[i].colour,
                colour_keyword_relation_data[i].keyword,
                sqlite3_errmsg(db)
            );

            printf("rolling back changes\n");

            sqlite3_exec(
                db,
                "ROLLBACK;",
                NULL,
                NULL,
                NULL
            );

            sqlite3_finalize(stmt);

            return return_code;
        }


        /*
         * Clear previous IDs.
         */
        sqlite3_clear_bindings(stmt);
    }


    // Commit transaction
    return_code = sql_exec("colour_keyword_relation_insert_commit", db, "COMMIT");

    // Handle error
    if (return_code != SQLITE_OK)
    {
        sqlite3_exec(
            db,
            "ROLLBACK;",
            NULL,
            NULL,
            NULL
        );

        sqlite3_finalize(stmt);

        return return_code;
    }


    sqlite3_finalize(stmt);

    printf("colour_keyword_relation_insert success\n");

    return SQLITE_OK;
}

// Create view
int colour_keyword_relation_create_view(sqlite3* db)
{
    //create view query
    const char* sql_create_view_query =
        "CREATE VIEW IF NOT EXISTS colour_keyword_relation_view AS "
        "SELECT "
            "t.colour AS colour_id, "
            "c.name AS colour_name, "
            "t.keyword AS keyword_id, "
            "k.name AS keyword_name "
        "FROM colour_keyword_relation AS t "
        "INNER JOIN colour AS c "
            "ON t.colour = c.id "
        "INNER JOIN colour_keyword AS k "
            "ON t.keyword = k.id;";


    return sql_exec("colour_keyword_relation_create_view", db, sql_create_view_query);
 }

// Init then insert data into table. create view
int colour_keyword_relation_create(sqlite3* db)
{
    // Init relation table
    int return_code = colour_keyword_relation_init(db);

    // Handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(
            stderr,
            "colour_keyword_relation_create init fail: %s\n",
            sqlite3_errmsg(db)
        );

        return return_code;
    }


    // Insert relation data
    return_code = colour_keyword_relation_insert(db);

    // Handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(
            stderr,
            "colour_keyword_relation_create insert fail: %s\n",
            sqlite3_errmsg(db)
        );

        return return_code;
    }

    // create view
    return_code = colour_keyword_relation_create_view(db);

    // Handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(
            stderr,
            "colour_keyword_relation_create create view fail: %s\n",
            sqlite3_errmsg(db)
        );

        return return_code;
    }

    printf("colour_keyword_relation_create success\n");
    return SQLITE_OK;
}
