#!/usr/bin/env python3

import os
import random                                   # Discuss: random module
import sys

# Constants
                                                # Discuss: set data structure
NSFW = {'bong', 'sodomized', 'kiss', 'head-in', 'telebears'}

# Main Execution

def main():
    characters = []                             # Discuss: os.popen
    for index, line in enumerate(os.popen('cowsay -l')):
        if not index:                           # Discuss: enumerate
            continue

        for character in line.split():          # Review: str.split
            if character not in NSFW:           # Review: searching collection
                characters.append(character)    # Review: list.append
    
    selected = random.choice(characters)
    os.system(f'cowsay -f {selected}')          # Variant: check exist status

if __name__ == '__main__':
    main()
