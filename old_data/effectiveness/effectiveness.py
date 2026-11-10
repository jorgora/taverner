import sqlite3

from taverner.sql.effectiveness.effectiveness_list import effectiveness_list as values
from taverner.sql.sql_table import SQLTable


def effectiveness_create(
    conn: sqlite3.Connection,
    name: str="effectiveness",
    values=values
) -> SQLTable:
    """Create effectivensss sql table."""
    table = SQLTable(
        name=name,

        columns=[
            "attacker INTEGER NOT NULL",
            "defender INTEGER NOT NULL",
            "effectiveness INTEGER NOT NULL"
        ],

        foreign_keys=[
            "FOREIGN KEY (attacker) REFERENCES element(id)",
            "FOREIGN KEY (defender) REFERENCES element(id)",
            "FOREIGN KEY (effectiveness) REFERENCES effectiveness_type(id)",
            "PRIMARY KEY (attacker, defender)"
        ],

        values=values,

        view_query=f'''
        SELECT
        t.attacker AS atk,
        e1.name AS attacker,

        t.defender AS def,
        e2.name AS defender,

        t.effectiveness AS eid,
        et.name As effectiveness

        FROM {name} AS t

        INNER JOIN element AS e1 ON t.attacker = e1.id
        INNER JOIN element AS e2 ON t.defender = e2.id
        INNER JOIN effectiveness_type AS et ON et.id = t.effectiveness;
        ''',

        insert_query = f"INSERT INTO {name} (attacker, defender, effectiveness) VALUES (?, ?, ?)"

        )

    cursor = conn.cursor()
    try:
        table.create(conn, cursor)
        table.change_print(conn, cursor)
    finally:
        cursor.close()
    return table
