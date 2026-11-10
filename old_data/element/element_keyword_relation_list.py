"""data for colour keyword relation table."""

from taverner.sql.element.element_keyword_list import element_keyword_list
from taverner.sql.element.element_list import element_list

e = {element[0]: index + 1 for index, element in enumerate(element_list)}
k = {keyword[0]: index + 1 for index, keyword in enumerate(element_keyword_list)}

element_keyword_relation_list = [
    (e["typeless"], k["none"]),

    (e["alien"], k["material"]),
    (e["alien"], k["unnatural"]),
    (e["alien"], k["stable"]),
    (e["alien"], k["alive"]),
    (e["alien"], k["organic"]),

    (e["air"], k["material"]),
    (e["air"], k["natural"]),
    (e["air"], k["stable"]),
    (e["air"], k["not alive"]),
    (e["air"], k["organic"]),

    (e["chaos"], k["immaterial"]),
    (e["chaos"], k["unnatural"]),
    (e["chaos"], k["unstable"]),
    (e["chaos"], k["not alive"]),
    (e["chaos"], k["organic"]),

    (e["earth"], k["material"]),
    (e["earth"], k["natural"]),
    (e["earth"], k["stable"]),
    (e["earth"], k["not alive"]),
    (e["earth"], k["organic"]),

    (e["electricity"], k["immaterial"]),
    (e["electricity"], k["unnatural"]),
    (e["electricity"], k["unstable"]),
    (e["electricity"], k["not alive"]),
    (e["electricity"], k["inorganic"]),

   (e["evil"], k["immaterial"]),
   (e["evil"], k["unnatural"]),
   (e["evil"], k["unstable"]),
   (e["evil"], k["alive"]),
   (e["evil"], k["organic"]),

   (e["fire"], k["immaterial"]),
   (e["fire"], k["natural"]),
   (e["fire"], k["unstable"]),
   (e["fire"], k["not alive"]),
   (e["fire"], k["organic"]),

   (e["holiness"], k["immaterial"]),
   (e["holiness"], k["natural"]),
   (e["holiness"], k["stable"]),
   (e["holiness"], k["alive"]),
   (e["holiness"], k["organic"]),

   (e["ice"], k["material"]),
   (e["ice"], k["natural"]),
   (e["ice"], k["stable"]),
   (e["ice"], k["not alive"]),
   (e["ice"], k["organic"]),

   (e["metal"], k["material"]),
   (e["metal"], k["natural"]),
   (e["metal"], k["stable"]),
   (e["metal"], k["not alive"]),
   (e["metal"], k["inorganic"]),

   (e["mutation"], k["material"]),
   (e["mutation"], k["unnatural"]),
   (e["mutation"], k["unstable"]),
   (e["mutation"], k["alive"]),
   (e["mutation"], k["organic"]),

   (e["normal"], k["material"]),
   (e["normal"], k["natural"]),
   (e["normal"], k["stable"]),
   (e["normal"], k["alive"]),
   (e["normal"], k["organic"]),

   (e["plant"], k["material"]),
   (e["plant"], k["natural"]),
   (e["plant"], k["stable"]),
   (e["plant"], k["alive"]),
   (e["plant"], k["organic"]),

   (e["poison"], k["material"]),
   (e["poison"], k["unnatural"]),
   (e["poison"], k["stable"]),
   (e["poison"], k["not alive"]),
   (e["poison"], k["inorganic"]),

   (e["radiation"], k["immaterial"]),
   (e["radiation"], k["unnatural"]),
   (e["radiation"], k["unstable"]),
   (e["radiation"], k["not alive"]),
   (e["radiation"], k["inorganic"]),

   (e["undead"], k["immaterial"]),
   (e["undead"], k["unnatural"]),
   (e["undead"], k["unstable"]),
   (e["undead"], k["alive"]),
   (e["undead"], k["inorganic"]),

   (e["water"], k["material"]),
   (e["water"], k["natural"]),
   (e["water"], k["stable"]),
   (e["water"], k["not alive"]),
   (e["water"], k["organic"]),

   (e["fungus"], k["material"]),
   (e["fungus"], k["natural"]),
   (e["fungus"], k["unstable"]),
   (e["fungus"], k["alive"]),
   (e["fungus"], k["organic"])
    ]
