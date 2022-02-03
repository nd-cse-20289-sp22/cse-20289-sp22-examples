#!/usr/bin/env python3

import sys

# Functions

def sumup():
    ''' Iterative '''
    numbers = []

    for argument in sys.argv[1:]:
        try:
            numbers.append(int(argument))
        except ValueError:
            pass

    print(f'The sum of {numbers} is {sum(numbers)}')

def sumup_fp():
    ''' Functional Programming '''
    numbers = list(map(int, filter(str.isdigit, sys.argv[1:])))
    print(f'The sum of {numbers} is {sum(numbers)}')

def sumup_lc():
    ''' List Comprehension '''
    numbers = [int(arg) for arg in sys.argv[1:] if arg.isdigit()]
    print(f'The sum of {numbers} is {sum(numbers)}')

# Main Execution

if __name__ == '__main__':
    sumup()
