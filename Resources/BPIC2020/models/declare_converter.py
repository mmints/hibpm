#!/usr/bin/env python3

import sys
import csv

if len(sys.argv) != 2:
    print("None or Wrong input!")

in_path = sys.argv[1]

csv_suffix = ".csv"

if csv_suffix not in in_path:
    print("The input file is not a CSV. Please check your input and/or change the ending to '.csv'.")

filename = open(in_path, 'r')
file = csv.reader(filename, delimiter=";")

constraints = []

for col in file:
    constraints.append(col[0])

constraints.remove(constraints[0])

for constraint in constraints:
    constraint = constraint.replace("'", "")
    constraint = constraint.replace(" ", "_")
    constraint = constraint.replace("(", "('")
    constraint = constraint.replace(")", "')")
    constraint = constraint.replace(",_", "','")
    print(constraint)