"""move type sql table."""

import sqlite3

from taverner.sql.move_type.move_type_list import move_type_list as values
from taverner.sql.sql_table import SQLTable, base_table_create


def move_type_create(
    connection: sqlite3.Connection, name="move_type", values=values
) -> SQLTable:
    """Create movetype sql table."""
    cursor = connection.cursor()  # Create cursor inside function
    try:
        table = base_table_create(connection, cursor, name, values)
    finally:
        cursor.close()  # Ensure cursor is closed
    return table
