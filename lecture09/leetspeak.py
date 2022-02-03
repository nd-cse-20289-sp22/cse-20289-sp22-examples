#!/usr/bin/env python3

import sys

# Functions

def leetspeak_list(text):
    ''' Translate each line of text into leetspeak using list '''
    mapping = [
        ('a', '4'),
        ('e', '3'),
        ('i', '1'),
        ('o', '0'),
    ]

    result = ''
    for letter in text:
        next_letter = letter
        for n, v in mapping:
            if letter == n:
                next_letter = v
        result += next_letter
    return result

def leetspeak_dict(text):
    ''' Translate each line of text into leetspeak using dict '''
    mapping = {
        'a': '4',
        'e': '3',
        'i': '1',
        'o': '0',
    }

    result = ''
    for letter in text:
        result += mapping.get(letter, letter)
    return result

# Main Execution

def main():
    for line in sys.stdin:
        print(leetspeak_list(line.rstrip()))

if __name__ == '__main__':
    main()
