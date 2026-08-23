#ifndef COLOUR_H
#define COLOUR_H

#include <sqlite3.h>

// colour struct
typedef struct
{
    const char* name;
    int r;
    int g;
    int b;
} Colour;

// create empty table
int colour_init(sqlite3* db);

// insert data into table
int colour_insert(sqlite3* db);

// init then insert data into table
int colour_create(sqlite3* db);

// return id given a name
int colour_get_id(sqlite3* db, const char* name);

#endif
