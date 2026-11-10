
from taverner.sql.species.species_family_list import species_family_list as values
from taverner.sql.sql_table import SQLTable, base_table_create


def species_family_create(
        connection,
        name="species_family",
        values=values
) -> SQLTable:
    """Create species family list."""
    cursor = connection.cursor()
    try:
        table = base_table_create(connection, cursor, name, values)
    finally:
        cursor.close()  # Ensure cursor is closed
    return table
