#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""Creates macro in C."""

TYPES = [
    "char", "short", "int", "long", "float", "double", "bool",
]
SIGN_MODIFIERS = [
    ("", "", TYPES),
    ("signed ", "s", ["char", "short", "int", "long"]),
    ("unsigned ", "u", ["char", "short", "int", "long"]),
]
LENGTH_MODIFIERS = [
    ("", "", TYPES),
    ("long ", "l", ["long", "double"])
]


def of_macros():
    """Creates OF macros for carray project."""
    macros = []
    for t in TYPES:
        for (scmod, sabmod, sapp) in SIGN_MODIFIERS:
            for (lcmod, labmod, lapp) in LENGTH_MODIFIERS:
                if t in sapp and t in lapp:
                    ctype = scmod + lcmod + t
                    abtype = sabmod + labmod + t.capitalize()
                    macros.append("#define of_{} *({}*)"
                                  .format(abtype, ctype))
    return "\n".join(macros)


def to_macros():
    """Creates TO macros for carray project."""
    macros = []
    for t in TYPES:
        for (scmod, sabmod, sapp) in SIGN_MODIFIERS:
            for (lcmod, labmod, lapp) in LENGTH_MODIFIERS:
                if t in sapp and t in lapp:
                    ctype = scmod + lcmod + t
                    abtype = sabmod + labmod + t.capitalize()
                    lines = [
                        "{} *{}_holder;\n".format(ctype, abtype) +
                        "#define {}(expr)".format(abtype),
                        "({}_holder = malloc(sizeof({})),"
                            .format(abtype, ctype),
                        " *{}_holder = (expr), {}_holder)"
                            .format(abtype, abtype)
                    ]
                    macros.append(" \\\n    ".join(lines))
    return "\n\n".join(macros)


def main():
    """Main function."""
    print(of_macros())
    print("")
    print(to_macros())


if __name__ == "__main__":
    main()
