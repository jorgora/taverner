#ifndef COLOUR_KEYWORD_RELATION_H
#define COLOUR_KEYWORD_RELATION_H

#include <sqlite3.h>

// colour keyword relation trut
typedef struct
{
    const char* colour;
    const char* keyword;
} ColourKeywordRelation;

// create empty table
int colour_keyword_relation_init(sqlite3* db);

// insert data into table
int colour_keyword_relation_insert(sqlite3* db);

// init then insert data into table. create view
int colour_keyword_relation_create(sqlite3* db);

#endif
