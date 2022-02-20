#!/usr/bin/env python3

import collections

# Structures                                    # Discuss: named tuple

Person = collections.namedtuple('Person', 'first_name last_name')

# Variables

People = [
    Person('Peter'    , 'Bui'),
    Person('Zephan'   , 'Enciso'),
    Person('Christina', 'Youn'),
    Person('Emory'    , 'Smith'),
    Person('Caleb'    , 'Bui'),
]

# Default sort                                  # Discuss: default (first_name)

for person in sorted(People):
    print(person.last_name, person.first_name)

print()

# Sort by last_name with helper function

def last_name(p):
    return p.last_name

for person in sorted(People, key=last_name):    # Discuss: key argument
    print(person.last_name, person.first_name)

print()

# Sort by last_name with lambda expression

for person in sorted(People, key=lambda p: p.last_name):
    print(person.last_name, person.first_name)

print()
f = lambda p: p.last_name                       # Discuss: lambda
print(f)
print(f(People[-1]))
print()

# Sort by last_name then first_name using two sorts

SortedPeople = sorted(People)                   # Discuss: low priority first!
SortedPeople = sorted(SortedPeople, key=lambda p: p.last_name)

for person in SortedPeople:
    print(person.last_name, person.first_name)

print()

# Sort by last_name then first_name using one sort

SortedPeople = sorted(People, key=lambda p: (p.last_name, p.first_name))
for person in SortedPeople:                     # Discuss: tuple comparison
    print(person.last_name, person.first_name)
