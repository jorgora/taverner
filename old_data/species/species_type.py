import sqlite3

from taverner.sql.species.species_type_list import species_type_list as values
from taverner.sql.sql_table import Config, SQLTable


def species_type_create(
        conn: sqlite3.Connection,
        name: str="species_type",
        values=values
) -> SQLTable:
    table = SQLTable(
        name=name,

        columns=[
            Config.id,
            Config.name(),
            "family INTEGER NOT NULL",
            "favourite_element INTEGER NOT NULL"
        ],

        foreign_keys=[
            "FOREIGN KEY(family) REFERENCES species_family(id)",
            "FOREIGN KEY(favourite_element) REFERENCES element(id)",
        ],

        values=values,

        view_query=f'''
        SELECT
        t.id AS id,

        t.name AS name,

        t.family AS fid,
        f.name AS family,

        t.favourite_element AS eid,
        e.name AS fav_element


        from {name} AS t
        INNER JOIN species_family AS f ON t.family = f.id
        INNER JOIN element AS e ON t.favourite_element = e.id
        ''',

        insert_query = f"INSERT INTO {name} (name, family, favourite_element) VALUES (?, ?, ?)"
    )

    """Create colour keyword list."""
    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
