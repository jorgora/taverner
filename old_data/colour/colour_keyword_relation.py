"""create colour keyword relation table."""

import sqlite3

from taverner.sql.colour.colour_keyword_relation_list import (
    colour_keyword_relation_list as values,
)
from taverner.sql.sql_table import SQLTable


def colour_keyword_relation_create(
    connection: sqlite3.Connection, name: str = "colour_keyword_relation", values=values
) -> SQLTable:
    """Create colour keyword relation table."""
    table = SQLTable(
        name=name,
        columns=[
            "colour INTEGER NOT NULL",
            "keyword INTEGER NOT NULL",
        ],
        foreign_keys=[
            "FOREIGN KEY (colour) REFERENCES colour(id)",
            "FOREIGN KEY (keyword) REFERENCES colour_keyword(id)",
            "PRIMARY KEY (colour, keyword)",
        ],
        values=values,
        view_query=f"""
        SELECT
        t.colour AS cid,
        c.name AS colour,
        t.keyword AS kid,
        k.name AS keyword

        FROM {name} AS t

        INNER JOIN colour AS c ON t.colour = c.id
        INNER JOIN colour_keyword AS k ON t.keyword = k.id;
        """,
        insert_query=f"INSERT INTO {name} (colour, keyword ) VALUES (?, ?)",
    )

    cursor = connection.cursor()
    try:
        table.create(connection, cursor)
        table.change_print(connection, cursor)
    finally:
        cursor.close()
    return table
