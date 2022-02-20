#!/usr/bin/env python3

import concurrent.futures
import os
import re

import requests

# Constants

BASE = 'https://www.bensound.com'
URL  = BASE + '/royalty-free-music/'

# Functions

def wget(url):
    p = os.path.basename(url)           # Review: os.path.basename

    print('Downloading {} to {}'.format(url, p))
    r = requests.get(url)
    with open(p, 'wb') as fs:           # Review: Writing to a file, with statement
        fs.write(r.content)

    return p

def flatten(sequence):
    for iterable in sequence:
        yield from iterable

# Main Execution

if __name__ == '__main__':
    # Download first page of Bensound
    '''
    response = requests.get(URL)
    assets   = (BASE + asset for asset in re.findall('src="(.*mp3)"', response.text))
    '''

    # Download all of Bensound
    pages    = (requests.get(URL + str(i)).text for i in range(1, 10))  # Actually 38 pages
    assets   = flatten(
                (BASE + asset for asset in re.findall('src="(.*mp3)"', page))
                    for page in pages)

    # Sequential
    '''
    list(map(wget, assets))             # Discuss: Why list?
    '''

    # Parallel                          # Discuss: concurrent.futures
    with concurrent.futures.ProcessPoolExecutor() as executor:
        executor.map(wget, assets)      # Discuss: Timing
