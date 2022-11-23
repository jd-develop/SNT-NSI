#!/usr/bin/env python3
# coding:utf-8
ACCENTS = "àáâãäåæçèéêëìíîïñòóôõöøùúûüýÿāăąćĉċčďđēĕėęěĝğġģĥħĩīĭįĵķĺļľŀłńņňŋōŏőœŕŗřśŝşšţťŧũūŭůűųŵŷźżž"
ACCENTS_UP = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÑÒÓÔÕÖØÙÚÛÜÝŸĀĂĄĆĈĊČĎĐĒĔĖĘĚĜĞĠĢĤĦĨĪĬĮĴĶĹĻĽĿŁŃŅŇŊŌŎŐŒŔŖŘŚŜŞŠŢŤŦŨŪŬŮŰŲŴŶŹŻŽ"


def upper(chaine):
    res = ""
    for c in chaine:
        if ord(c) in range(0x61, 0x7B):
            res += chr(ord(c) - 0x20)
        elif c in ACCENTS:
            lower_i = ACCENTS.index(c)
            res += ACCENTS_UP[lower_i]
        else:
            res += c
    return res


def lower(chaine):
    res = ""
    for c in chaine:
        if ord(c) in range(0x41, 0x5B):
            res += chr(ord(c) + 0x20)
        elif c in ACCENTS_UP:
            upper_i = ACCENTS_UP.index(c)
            res += ACCENTS[upper_i]
        else:
            res += c
    return res


print(upper("Bonjour le monde !"))
print(upper("Never gonna give you up !"))
print(upper("Never gonna let you down !"))
print(upper("Never gonna run around and desert you !"))
print(upper("Never gonna give you up !"))
print(upper("Never gonna say goodbye !"))
print(upper("Never gonna say tell a lie and hurt you !"))
print(upper("Čéĉî èŝţ ùñ tëxtė âņòŕmăłêměňť àçćēŋŧųé..."))
print(upper("àáâãäåæçèéêëìíîïñòóôõöøùúûüýÿāăąćĉċčďđēĕėęěĝğġģĥħĩīĭįĵķĺļľŀłńņňŋōŏőœŕŗřśŝşšţťŧũūŭůűųŵŷźżž"))

print(lower("BONJOUR LE MONDE !"))
print(lower("NEVER GONNA GIVE YOU UP !"))
print(lower("NEVER GONNA LET YOU DOWN !"))
print(lower("NEVER GONNA RUN AROUND AND DESERT YOU !"))
print(lower("NEVER GONNA GIVE YOU UP !"))
print(lower("NEVER GONNA SAY GOODBYE !"))
print(lower("NEVER GONNA SAY TELL A LIE AND HURT YOU !"))
print(lower("ČÉĈÎ ÈŜŢ ÙÑ TËXTĖ ÂŅÒŔMĂŁÊMĚŇŤ ÀÇĆĒŊŦŲÉ..."))
print(lower("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÑÒÓÔÕÖØÙÚÛÜÝŸĀĂĄĆĈĊČĎĐĒĔĖĘĚĜĞĠĢĤĦĨĪĬĮĴĶĹĻĽĿŁŃŅŇŊŌŎŐŒŔŖŘŚŜŞŠŢŤŦŨŪŬŮŰŲŴŶŹŻŽ"))
