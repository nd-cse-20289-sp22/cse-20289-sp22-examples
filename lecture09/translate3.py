#!/usr/bin/env python3

# ls -l /dev | grep -v total | awk '{print $4}' | sort | uniq -c | sort -rn

import os

counts = {}
for index, line in enumerate(os.popen('ls -l /dev')):
    if not index:
        continue
    group = line.split()[3]
    counts[group] = counts.get(group, 0) + 1

for group, count in sorted(counts.items(), key=lambda p: p[1], reverse=True):
    print('{:7} {}'.format(count, group))
