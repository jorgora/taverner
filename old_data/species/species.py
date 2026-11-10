"""create species sql table."""

import sqlite3

from taverner.sql.species.species_list import species_list as values
from taverner.sql.sql_table import Config, SQLTable


def species_create(
    conn: sqlite3.Connection,
    name: str = "species",
    values=values
) -> SQLTable:
    """Create species sql table."""
    table = SQLTable(
        name=name,
        columns=[
            Config.id,
            "type INTEGER NOT NULL",
            Config.text("name1"),
            Config.text("name2"),
            "height_min INTEGER NOT NULL",
            "height_max INTEGER NOT NULL",
            "weight_min INTEGER NOT NULL",
            "weight_max INTEGER NOT NULL",
            "hp INTEGER NOT NULL",
            "atk INTEGER NOT NULL",
            "def INTEGER NOT NULL",
            "spc_atk INTEGER NOT NULL",
            "spc_def INTEGER NOT NULL",
            "favourite_element INTEGER NOT NULL",
        ],
        foreign_keys=[
            "FOREIGN KEY(type) REFERENCES species_type(id)",
            "FOREIGN KEY(favourite_element) REFERENCES element(id)"
        ],
        values=values,
        view_query=f"""
        SELECT
        t.id AS id,
        st.name AS type,
        t.name1 AS name1,
        t.name2 AS name2,
        t.height_min AS h_min,
        t.height_max AS h_max,
        t.weight_min  AS w_min,
        t.weight_max AS w_max,
        t.hp AS hp,
        t.atk AS atk,
        t.def AS def,
        t.spc_atk AS spc_atk,
        t.spc_def AS spc_def,
        t.favourite_element AS eid,
        e.name AS fav_element

        FROM {name} AS t
        INNER JOIN species_type AS st on t.type = st.id
        INNER JOIN element AS e on t.favourite_element = e.id
        """,
        insert_query=f"""INSERT INTO {name} (type, name1, name2, height_min, height_max, weight_min, weight_max, hp, atk, def, spc_atk, spc_def, favourite_element)
       VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ,?, ?)""",
    )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
