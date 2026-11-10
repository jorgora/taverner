"""create element keyword list."""

import sqlite3

from taverner.sql.element.element_keyword_list import element_keyword_list as values
from taverner.sql.sql_table import SQLTable, base_table_create


def element_keyword_create(
    connection: sqlite3.Connection, name: str = "element_keyword", values=values
) -> SQLTable:
    """Create colour keyword list."""
    cursor = connection.cursor()
    try:
        table = base_table_create(connection, cursor, name, values)
    finally:
        cursor.close()  # Ensure cursor is closed
    return table
