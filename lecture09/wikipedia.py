#!/usr/bin/env python3

import pprint
import re
import sys

import requests

# Constants

URL      = 'https://en.wikipedia.org/w/api.php' # Discuss: APIs
PARAMS   = {
    'action'  : 'query', 
    'list'    : 'search', 
    'format'  : 'json', 
    'srsearch': sys.argv[1]
}

# Main Execution

def main():
    result   = requests.get(URL, params=PARAMS) # Review: keyword arguments
    data     = result.json()                    # Discuss: json

    #pprint.pprint(data)                        # Discuss: pretty printing

    articles = data['query']['search']          # Discuss: sorting by key, lambda
    articles = sorted(data['query']['search'], key=lambda o: o['wordcount'])

    for index, entry in enumerate(articles[:5], 1):
        if index > 1:                           # Review: slicing, enumerate
            print()                             # Discuss: fence pattern

        title   = entry['title']                # Discuss: re.sub
        snippet = re.sub(r'<[^>]+>', '', entry['snippet'])
        print(f'{index:4}.\t{title}\n\t{snippet}')

if __name__ == '__main__':
    main()
