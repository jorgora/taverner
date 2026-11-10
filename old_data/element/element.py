"""create element sql list."""

import sqlite3

from taverner.sql.element.element_list import element_list as values
from taverner.sql.sql_table import Config, SQLTable


def element_create(
    conn: sqlite3.Connection, name: str = "element", values=values
) -> SQLTable:
    """Create element sql table."""
    table = SQLTable(
        name=name,
        columns=[
            Config.id,
            Config.name(),
            "colour INTEGER NOT NULL",
            "move_type INTEGER NOT NULL",
        ],
        foreign_keys=[],
        values=values,
        view_query=f"""
        SELECT
        t.id AS id,
        t.name AS name,
        t.colour AS colour,
        t.move_type AS move_type

        FROM {name} AS t
        """,
        insert_query=f"""INSERT INTO {name} (name, colour, move_type) VALUES (?, ?, ?)""",
    )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
