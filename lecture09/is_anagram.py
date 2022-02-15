#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    print(f'''Usage: {os.path.basename(sys.argv[0])} [flags]
    -i  Ignore case distinctions

This program reads in two words per line and determines if they are anagrams.
''')
    sys.exit(status)

def count_letters(string):
    ''' Returns a dictionary containing counts of each letter in string 

    >>> count_letters('aaa bb c')
    {'a': 3, 'b': 2, 'c': 1}
    '''

    counts = {}                                         # Discuss: counting pattern
    for letter in string:
        if not letter.isspace():
            counts[letter] = counts.get(letter, 0) + 1  # Discuss: get dictionary method
    return counts

def is_anagram(word1, word2):
    ''' Returns whether or not word1 and word 2 are anagrams

    >>> is_anagram('dormitory', 'dirty room')
    True
    
    >>> is_anagram('asdf', 'asdfg')
    False
    '''
    counts1 = count_letters(word1)
    counts2 = count_letters(word2)

    for key in counts1:                                 # Discuss: iterating through dictionary
        if counts1[key] != counts2.get(key, 0):
            return False

    for key in counts2:
        if counts2[key] != counts1.get(key, 0):
            return False

    return True


def main():
    # Parse command-line options
    arguments  = sys.argv[1:]                           # Review: command line arguments
    ignorecase = False

    while arguments and arguments[0].startswith('-'):
        argument = arguments.pop(0)                     # Discuss: popping from queue
        if argument == '-i':
            ignorecase = True
        elif argument == '-h':
            usage(0)
        else:
            usage(1)

    # Process standard input
    for line in sys.stdin:                              
        if ignorecase:
            line = line.lower()

        word1, word2 = line.split(' ', 2)               # Discuss: splitting string
        if is_anagram(word1, word2):
            print('ANAGRAM!')
        else:
            print('NOT ANAGRAM!')

# Main Execution

if __name__ == '__main__':
    main()

