#!/bin/sh

# Globals

N=1
SHOUT=0

# Functions

usage() {				    # Review: I/O redirection, here doc
    cat 1>&2 <<EOF
Usage: repeat [-n N -s] MESSAGE
    -n N    Repeat MESSAGE N times (default is 1)
    -s      Shout MESSAGE (uppercase)
EOF
    exit $1
}

shout() {
    if [ $SHOUT -eq 0 ]; then		    # Discuss: testing integers
    	echo $@				    # Discuss: function arguments
    else
    	echo $@ | tr a-z A-Z		    # Discuss: translate
    fi
}

# Parse Command Line Arguments

while [ $# -gt 0 ]; do
    case $1 in
	-n) N=$2; shift ;;		    # Discuss: double shift
	-s) SHOUT=1 ;;			    # Discuss: flags
	-h) usage 0 ;;
	-*) usage 1 ;;
	 *) break ;;
    esac
    shift
done

MESSAGE=$@

# Main Execution

if [ -z "$MESSAGE" ]; then		    # Discuss: testing strings
    usage 1
fi

for i in $(seq $N); do
    shout "$@"
done
