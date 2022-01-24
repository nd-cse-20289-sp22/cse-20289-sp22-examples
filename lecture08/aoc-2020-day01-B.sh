#!/bin/sh

# Functions

find_triple() {
    echo "$3" | awk -v NUMBER=$1 -v TARGET=$2 '
	{
	    difference = TARGET - $1

	    if ($1 in differences) {
		print NUMBER, $1, difference
	    } else {
		differences[difference] = $1
	    }
	}
    '
}

# Main Execution

NUMBERS=$(cat /dev/stdin)

for number in $NUMBERS; do
    find_triple $number $((2020 - $number)) "$NUMBERS" | tr ' ' '*' | bc
done | uniq
