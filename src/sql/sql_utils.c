#include <stdio.h>
#include <sqlite3.h>


#include "../../headers/sql/sql_utils.h"

// execute sqlite function (store result in int)
int sql_exec(const char* name, sqlite3* db, const char* query)
{
    // the nulls are callback function and callback args
    int return_code = sqlite3_exec(db, query, NULL, NULL, NULL);

    // handle error
    if (return_code != SQLITE_OK)
    {
        fprintf(stderr, "%s fail: %s\n", name, sqlite3_errmsg(db));
        return return_code;
    }

    // exit
    printf("%s success\n", name);
    return return_code;
}
