#!/usr/bin/env python3

import csv
import requests

# Constants

URL      = 'https://yld.me/raw/cxEe'
POINTS   = [5]*6                                # Discuss: multiplying list
MAX      = sum(POINTS)
SECTIONS = (
    'Commands',
    'Shell and Files',
    'Processes and Networking',
    'Pipelines',
    'Shell Scripting',
    'Filters'
)

# Fetch data

response = requests.get(URL)                    # Review: requests.get
scores   = []
sections = [0] * len(SECTIONS)                  # Discuss: multiplying list

# Compute individual scores
                                                # Discuss: csv.reader, text
for row in csv.reader(response.text.splitlines()):
    score = 0
    for section, point in enumerate(row):       # Review: enumerate
        score             += float(point)
        sections[section] += float(point)

    scores.append(score)

# Summarize score statistics

average = sum(scores)/len(scores)               # Discuss: sum
median  = sorted(scores)[len(scores)//2]        # Discuss: sorted, //
maximum = max(scores)                           # Discuss: max

print(f'AVERAGE: {average:5.2f} ({average/MAX * 100:5.2f}%)')
print(f'MEDIAN:  {median:5.2f} ({median/MAX * 100:5.2f}%)')
print(f'MAXIMUM: {maximum:5.2f} ({maximum/MAX * 100:5.2f}%)')
print()                                         # Review: f-strings, formatting

# Summarize section statistics

for index, section in enumerate(SECTIONS):
    average = sections[index]/len(scores)
    percent = average / POINTS[index] * 100
    print(f'{section:>25}: {average:5.2f} / {POINTS[index]} ({percent:5.2f}%)')
