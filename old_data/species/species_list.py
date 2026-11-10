from taverner.sql.element.element_list import element_list
from taverner.sql.species.species_family_list import species_family_list
from taverner.sql.species.species_type_list import species_type_list

t = {type[0]: index+1 for index, type in enumerate(species_type_list)}
f = {family[0]: index+1 for index, family in enumerate(species_family_list)}
e = {element[0]: index+1 for index, element in enumerate(element_list)}

species_list = [
    #type          name1                         name2                      height(mm)  weight(g)        hp   atk  def  spa  spd  fav_element

    (t["typeless"], "typeless",                   "typeless",                100, 100,   1000,   1000,    50,  50,  50,  50,  50, e["typeless"]),


    (t["aardvark"], "aardvark",                   "orycteropus afer",        1050, 1300, 60000,  80000,   85,  80,  90,  105, 95, e["chaos"]),

   (t["cat"],      "maine coon",                 "maine coon",               250, 400,   4800,   9500,    55,  65,  45,  50,  45, e["water"]),
   (t["cat"],      "siamese",                    "maeo sayam",               290, 310,   2500,   6000,    40,  61,  54,  45,  45, e["mutation"]),
   (t["cat"],      "british shorthair",          "british shorthair",        300, 460,   3200,   7700,    67,  45,  59,  63,  40, e["chaos"]),
   (t["lynx"],     "eurasian lynx",              "lynx lynx",                600, 750,   18000,  28000,   81,  55,  78,  90,  58, e["ice"]),
   (t["lynx"],     "bobcat",                     "lynx rufus",               460, 640,   6400,   18000,   70,  85,  65,  65,  60, e["radiation"]),
   (t["wildcat"],  "ocelot",                     "leopardus pardalis",       380, 510,   7000,   15500,   61,  80,  63,  60,  63, e["plant"]),
   (t["leopard"],  "snow leopard",               "panthera uncia",           550, 650,   40000,  55000,   76,  110, 70,  81,  70, e["ice"]),
   (t["tiger"],    "siberian tiger",             "amur tiger",               750, 1070,  120000, 222000,  104, 75,  100, 110, 175, e["ice"]),
   (t["lion"],     "lion",                       "panthera leo",             900, 1200,  130000, 190000,  85,  120, 80,  85,  75, e["air"]),

   (t["smalldog"], "dachshund",                  "wiener dog",               200,  230,  9000,   12000,   50,  65,  50,  40,  40, e["evil"]),
   (t["smalldog"], "miniature pinscher",        "zwergpinscher",             250,  300,  4000,   6000,    50,  40,  40,  70,  40, e["chaos"]),
   (t["smalldog"], "Bichon Frisé",               "Bichon à Poil Frisé",      230,  300,  4500,   5000,    50,  71,  40,  40,  40, e["fire"]),
   (t["smalldog"], "pomeranian",                 "pome",                     180,  240,  1400,   3200,    38,  30,  41,  30,  41, e["evil"]),
   (t["dog"],      "Kangal Shepherd Dog",        "Kangal Çoban Köpeği",     700,  800,  48000,  60000,   65,  86,  60,  55,  60, e["plant"]),
   (t["dog"],      "dobermann",                  "dobermann",                630,  720,  35000,  45000,   65,  60,  55,  95,  55, e["electricity"]),
   (t["dog"],      "german shorthaired pointer", "deutsch kurzhaar",         584,  635,  25000,  32000,   70,  85,  70,  55,  60, e["earth"]),
   (t["dog"],      "alaskan malamute",           "alaskan malamute",         560,  660,  34000,  39000,   78,  70,  61,  50,  61, e["ice"]),
   (t["wilddog"],  "golden jackal",              "canis aureus",             350,  450,  10000,  15000,   100, 125, 90,  60,  70, e["holiness"]),
   (t["wilddog"],  "african wild dog",           "lycaon pictus",            600,  750,  18000,  36000,   70,  85,  65,  125, 65, e["earth"]),
   (t["bear"],     "grizzly bear",               "Ursus arctos horribilis",  900,  1500, 100000, 600000,  80, 116,  75,  65,  75, e["plant"]),
    (t["wolf"],     "gray wolf",                  "canis lupus",              800,  850,  55000,  80000,   93,  90,  101, 60,  81, e["ice"]),
]
