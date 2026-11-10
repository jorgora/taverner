"""create colour keyword list."""

import sqlite3

from taverner.sql.colour.colour_keyword_list import colour_keyword_list as values
from taverner.sql.sql_table import SQLTable, base_table_create


def colour_keyword_create(
    conn: sqlite3.Connection,
        name: str = "colour_keyword",
        values=values
) -> SQLTable:
    """Create colour keyword list."""
    cursor = conn.cursor()
    try:
        table = base_table_create(conn, cursor, name, values)
    finally:
        cursor.close()  # Ensure cursor is closed
    return table
