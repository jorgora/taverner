#ifndef COLOUR_KEYWORD_H
#define COLOUR_KEYWORD_H

#include <sqlite3.h>

typedef struct
{
    const char* name;
} Colour_keyword;

// create empty table
int colour_keyword_init(sqlite3* db);

// insert data into table
int colour_keyword_insert(sqlite3* db);

// init then insert data into table
int colour_keyword_create(sqlite3* db);

// return id given a name
int colour_keyword_get_id(sqlite3* db, const char* name);

#endif



