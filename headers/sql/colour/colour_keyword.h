#ifndef COLOUR_KEYWORD_H
#define COLOUR_KEYWORD_H

#include <sqlite3.h>

typedef struct
{
    const char* name;
} Colour_keyword;

//init functions
void colour_keyword_init(sqlite3* db);
void colour_keyword_insert(sqlite3* db);

//create the actual table
int colour_keyword_create(sqlite3* db);
#endif



