"""data for element list."""

from taverner.sql.colour.colour_list import colour_list
from taverner.sql.move_type.move_type_list import move_type_list

c = {colour[0]: index + 1 for index, colour in enumerate(colour_list)}
mt = {move_type[0]: index + 1 for index, move_type in enumerate(move_type_list)}

element_list = [
    # name          #colour          #move_type
    ("typeless", c["colourless"], mt["typeless"]),
    ("alien", c["magenta"], mt["melee"]),
    ("air", c["silver"], mt["ranged"]),
    ("chaos", c["orange"], mt["magic"]),
    ("earth", c["brown"], mt["melee"]),
    ("electricity", c["yellow"], mt["ranged"]),
    ("evil", c["black"], mt["magic"]),
    ("fire", c["red"], mt["ranged"]),
    ("holiness", c["white"], mt["magic"]),
    ("ice", c["cyan"], mt["ranged"]),
    ("metal", c["dark grey"], mt["melee"]),
    ("mutation", c["maroon"], mt["melee"]),
    ("normal", c["grey"], mt["melee"]),
    ("plant", c["green"], mt["ranged"]),
    ("poison", c["purple"], mt["melee"]),
    ("radiation", c["lime"], mt["ranged"]),
    ("undead", c["dark green"], mt["melee"]),
    ("water", c["blue"], mt["ranged"]),
    ("fungus", c["gold"], mt["magic"]),
]
