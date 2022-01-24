#!/bin/sh

# Functions

find_pair() {
    echo "$2" | awk -v TARGET=$1 '
	{
	    difference = TARGET - $1

	    if ($1 in differences) {
		print difference, $1
	    } else {
		differences[difference] = $1
	    }
	}
    '
}

# Main Execution

NUMBERS=$(cat /dev/stdin)

find_pair 2020 "$NUMBERS" | tr ' ' '*' | bc
