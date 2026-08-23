#ifndef SQL_UTILS_H
#define SQL_UTILS_H

#include <sqlite3.h>

int sql_exec(const char* name, sqlite3* db, const char* query);

#endif
