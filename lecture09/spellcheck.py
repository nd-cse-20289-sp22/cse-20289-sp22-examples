#!/usr/bin/env python3

import os
import sys

# Constants

PATH = '/usr/share/dict/words'                  # Discuss: words file, constants

# Functions

def load_words_as_list(path=PATH):              # Discuss: default, keyword arguments
    words = []
    for word in open(path):                     # Discuss: reading files
        words.append(word.strip())              # Review: adding to list
    return words                                # Discuss: garbage collection

def load_words_as_dict(path=PATH):
    words = {}
    for word in open(path):
        words[word.strip()] = True              # Review: adding to dictionary
    return words

def load_words_as_set(path=PATH):
    words = set()
    for word in open(path):
        words.add(word.strip())                 # Review: adding to set
    return words

def main():
    words = load_words_as_list()                # Discuss: Project Gutenberg
    #words = load_words_as_dict()               # Discuss: timing
    #words = load_words_as_set()

    for line in sys.stdin:                      # Review: standard input
        for word in line.split():               # Review: splitting strings
            if word not in words:               # Review: searching collection
                print(f'{word} is misspelled!')

# Main Execution

if __name__ == '__main__':
    main()
