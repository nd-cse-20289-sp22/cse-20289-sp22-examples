#!/usr/bin/env python3

import os

# Functions

def fizzbuzz(start=1, stop=100):
    ''' 
    >>> fizzbuzz(1, 5)
    1
    2
    Fizz
    4
    Buzz
    
    >>> fizzbuzz(12, 15)
    Fizz
    13
    14
    FizzBuzz
    '''
    for number in range(start, stop + 1):
        if number % 3 == 0 and number % 5 == 0:
            print('FizzBuzz')
        elif number % 3 == 0:
            print('Fizz')
        elif number % 5 == 0:
            print('Buzz')
        else:
            print(number)

# Main Execution

if __name__ == '__main__':
    fizzbuzz()
