"""create effectiveness type list."""

import sqlite3

from taverner.sql.effectiveness.effectiveness_type_list import (
    effectiveness_type_list as values,
)
from taverner.sql.sql_table import SQLTable, base_table_create


def effectiveness_type_create(
    connection: sqlite3.Connection, name: str = "effectiveness_type", values=values
) -> SQLTable:
    """Create effectiveness type list."""
    cursor = connection.cursor()
    try:
        table = base_table_create(connection, cursor, name, values)
    finally:
        cursor.close()  # Ensure cursor is closed
    return table
