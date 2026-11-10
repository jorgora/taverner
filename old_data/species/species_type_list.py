from taverner.sql.element.element_list import element_list
from taverner.sql.species.species_family_list import species_family_list

f = {family[0]: index+1 for index, family in enumerate(species_family_list)}
e = {element[0]: index+1 for index, element in enumerate(element_list)}

species_type_list = [
    ("typeless", f["none"], e["typeless"]),
    ("cat",      f["feline"], e["fire"]),
    ("lynx",     f["feline"], e["ice"]),
    ("tiger",    f["feline"], e["evil"]),
    ("wildcat",  f["feline"], e["fire"]),
    ("leopard",  f["feline"], e["fire"]),
    ("lion",     f["feline"], e["holiness"]),
    ("hyena",    f["feline"], e["earth"]),
    ("aardvark", f["aardvark"], e["alien"]),

    ("smalldog", f["canine"], e["water"]),
    ("dog",      f["canine"], e["water"]),
    ("wilddog",  f["canine"], e["poison"]),
    ("wolf",     f["canine"], e["evil"]),
    ("fox",      f["canine"], e["plant"]),
    ("bear",     f["canine"], e["ice"])
]
