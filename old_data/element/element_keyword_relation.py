"""create element keyword relation table."""

import sqlite3

from taverner.sql.element.element_keyword_relation_list import (
    element_keyword_relation_list as values,
)
from taverner.sql.sql_table import SQLTable


def element_keyword_relation_create(
    connection: sqlite3.Connection, name: str = "element_keyword_relation", values=values
) -> SQLTable:
    """Create colour keyword relation table."""
    table = SQLTable(
        name=name,
        columns=[
            "element INTEGER NOT NULL",
            "keyword INTEGER NOT NULL",
        ],
        foreign_keys=[
            "FOREIGN KEY (element) REFERENCES element(id)",
            "FOREIGN KEY (keyword) REFERENCES element_keyword(id)",
            "PRIMARY KEY (element, keyword)",
        ],
        values=values,
        view_query=f"""
        SELECT
        t.element AS eid,
        e.name AS element,
        t.keyword AS kid,
        k.name AS keyword

        FROM {name} AS t

        INNER JOIN element AS e ON t.element = e.id
        INNER JOIN element_keyword AS k ON t.keyword = k.id;
        """,
        insert_query=f"INSERT INTO {name} (element, keyword ) VALUES (?, ?)",
    )

    cursor = connection.cursor()
    try:
        table.create(connection, cursor)
        table.change_print(connection, cursor)
    finally:
        cursor.close()
    return table
