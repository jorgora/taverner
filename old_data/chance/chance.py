"""Chance table creation utilities."""

import sqlite3

from taverner.sql.chance.chance_list import chance_list as values
from taverner.sql.sql_table import Config, SQLTable


def chance_create(
    conn: sqlite3.Connection,
    name: str = "chance",
    values=values,
) -> SQLTable:
    """Create the chance SQL table."""
    table = SQLTable(
        name=name,
        columns=[
            Config.id,
            Config.name(),
            "percent INTEGER NOT NULL",
        ],
        foreign_keys=[],
        values=values,
        view_query=f"""
        SELECT
            t.id AS id,
            t.name AS name,
            t.percent AS chance
        FROM {name} AS t
        """,
        insert_query=f"INSERT INTO {name} (name, percent) VALUES (?, ?)",
    )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()

    return table
