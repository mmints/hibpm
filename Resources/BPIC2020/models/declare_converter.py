#!/usr/bin/env python3

'''
This script can be used to translate CSV files that where created by MINERful.
'''

import sys
import csv

if len(sys.argv) != 2:
    print("None or Wrong input!")

in_path = sys.argv[1]
name = in_path.split(".")

filename = open(in_path, 'r')
file = csv.reader(filename, delimiter=";")

constraints = []

for col in file:
    constraints.append(col[0])

constraints.remove(constraints[0])


with open(name[0] + '.txt', 'w') as f:
    for constraint in constraints:
        constraint = constraint.replace("'", "")
        constraint = constraint.replace(" ", "_")
        constraint = constraint.replace("(", "('")
        constraint = constraint.replace(")", "')")
        constraint = constraint.replace(",_", "','")
        f.write("%s\n" % constraint)