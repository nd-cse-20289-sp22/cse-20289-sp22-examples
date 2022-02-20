#!/usr/bin/env python3

import concurrent.futures
import os
import requests

# Constants

URL = 'https://www.reddit.com/r/pics/.json'

# Functions

def wget(url):
    print(f'Downloading {url}...')

    response = requests.get(url)
    path     = os.path.basename(url)
    with open(path, 'wb') as fs:
        fs.write(response.content)
    return path

# Main Execution

def main():
    headers  = {'User-Agent': __name__}
    response = requests.get(URL, headers=headers)

    # Extract articles (functional programming)
    articles = map(lambda c: c['data'], response.json()['data']['children'])

    # Extract urls (list comprehension)
    urls     = [article['url'] for article in articles if article['url'].endswith('.jpg')]

    # Version 1: Imperative programming
    for url in urls:
        wget(url)

    # Version 2: Functional programming (sequential)
    # list(map(wget, urls))

    # Version 3: Functional programming (parallel)
    #with concurrent.futures.ProcessPoolExecutor() as executor:
    #    executor.map(wget, urls)

if __name__ == '__main__':
    main()
