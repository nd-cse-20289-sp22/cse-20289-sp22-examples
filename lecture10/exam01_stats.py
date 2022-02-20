#!/usr/bin/env python3

import csv
import requests

# Constants

URL    = 'https://yld.me/raw/cxEe'
POINTS = [5]*6
MAX    = sum(POINTS)

# Fetch data

data   = requests.get(URL).text.splitlines()    # Review: requests.get

# Compute individual scores (Imperative)

scores = []
for student in csv.reader(data):                # Review: csv.reader
    points = []                                 # Discuss: high-level goal
    for point in student:                       # Discuss: common pattern?
        points.append(float(point))             # Discuss: change to int?
    scores.append(sum(points))

print(scores)

# Compute individual scores (Functional) - Phase I

scores = []
for student in csv.reader(data):
    points = sum(map(float, student))           # Discuss: map abstraction
    scores.append(points)

print(scores)

# Compute individual scores (Functional) - Phase II

scores = map(lambda student: sum(map(float, student)), csv.reader(data))
print(list(scores))                             # Discuss: generator

# Compute individual scores (List Comprehensions) - Phase I

scores = [sum(map(float, student)) for student in csv.reader(data)]
print(scores)                                   # Discuss: list comprehension

# Compute individual scores (List Comprehensions) - Phase II

scores = [sum(float(point) for point in student) for student in csv.reader(data)]
print(scores)                                   # Discuss: generator expression

# Filter scores (Imperative)

Bs = []
for score in scores:                            # Discuss: high-level goal
    if .8*MAX <= score < .9*MAX:                # Discuss: common pattern?
        Bs.append(score)                        # Discuss: change to As?

print(len(Bs))

# Filter scores (Functional)

Bs = filter(lambda score: .8*MAX <= score < .9*MAX, scores)
print(len(list(Bs)))

# Filter scores (List Comprehensions)

Bs = [score for score in scores if .8*MAX <= score < .9*MAX]
print(len(Bs))
