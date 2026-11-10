import sqlite3

from taverner.sql.move.move_list import move_list as values
from taverner.sql.sql_table import Config, SQLTable


def move_create(
        conn: sqlite3.Connection,
        name: str="move",
        values=values):
    table = SQLTable(
        name=name,

        columns=[
            Config.id,
            Config.name(),
            "power INTEGER NOT NULL",
            "element INTEGER NOT NULL",
            "type INTEGER NOT NULL",
            "priority INTEGER NOT NULL",
            "chance INTEGER NOT NULL",
            Config.text("description"),
        ],

        foreign_keys=[
            "FOREIGN KEY(element) REFERENCES element(id)",
            "FOREIGN KEY(type) REFERENCES move_type(id)",
            "FOREIGN key(chance) REFERENCES chance(id)"
        ],

        values=values,

        view_query=f'''
        SELECT
        t.id AS id,
        t.name AS name,
        t.power AS pow,

        t.element AS e,
        e.name AS element,

        t.type as t,
        mt.name as type,

        t.priority as priority,

        t.chance as ch,
        ch.name as chance,

        t.description as description

        FROM {name} AS t
        INNER JOIN element AS e on t.element = e.id
        INNER JOIN move_type AS mt on t.type = mt.id
        INNER JOIN chance AS ch on t.chance = ch.id
        ''',

        insert_query = f"INSERT INTO {name} (name, power, element, type, priority, chance, description) VALUES (?, ?, ?, ?, ?, ?, ?)"
    )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
