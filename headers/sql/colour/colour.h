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

// init functions
int colour_init(sqlite3* db);
int colour_insert(sqlite3* db);

// init and insert data
int colour_create(sqlite3* db);

#endif
