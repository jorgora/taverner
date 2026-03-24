#ifndef COLOUR_H
#define COLOUR_H

#include <sqlite3.h>

typedef struct
{
    const char* name;
    int r;
    int g;
    int b;
} Colour;

//init functions
void colour_init(sqlite3* db);
void colour_insert(sqlite3* db);

//create the actual table
int colour_create(sqlite3* db);

#endif
