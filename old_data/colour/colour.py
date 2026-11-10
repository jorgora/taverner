"""create colour sql table."""

import sqlite3

from taverner.sql.colour.colour_list import colour_list as values
from taverner.sql.sql_table import Config, SQLTable


def colour_create(
    conn: sqlite3.Connection,
    name: str = "colour",
    values=values
) -> SQLTable:
    """Create colour sql table."""
    table = SQLTable(
        name=name,
        columns=[
            Config.id,
            Config.name(),
            "r INTEGER NOT NULL CHECK(r >= 0 AND r <= 255)",
            "g INTEGER NOT NULL CHECK(g >= 0 AND g <= 255)",
            "b INTEGER NOT NULL CHECK(b >= 0 AND b <= 255)"
        ],
        foreign_keys=[],
        values=values,
        view_query=f"""
        SELECT
        t.id AS id,
        t.name AS name,
        t.r AS r,
        t.g AS g,
        t.b AS b

        FROM {name} AS t
        """,
        insert_query=f"""INSERT INTO {name} (name,
        r, g, b) VALUES (?, ?, ?, ?)""",
    )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
