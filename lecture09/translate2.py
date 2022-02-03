#!/usr/bin/env python3

# curl -sL https://yld.me/raw/c1Dd | cut -d , -f 1 | grep -Eo '^B.*' | sort

import requests

response   = requests.get('https://yld.me/raw/c1Dd')
last_names = []
for line in response.text.splitlines():
    last_name = line.split(',')[0]
    if last_name.startswith('B'):
        last_names.append(last_name)

for last_name in sorted(last_names):
    print(last_name)
