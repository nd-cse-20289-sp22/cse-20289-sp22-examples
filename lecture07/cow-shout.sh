#!/bin/sh

# Globals

UPPERCASE=0
COWFILE="default"

# Functions

usage() {				    # Review: I/O redirection, here doc 
    cat 1>&2 <<EOF			    
Usage: shout [FLAGS] MESSAGE
-u	    Uppercase the MESSAGE
-c COWFILE  Which cow to use
EOF
    exit $1
}

# Parse Command Line Arguments

while [ $# -gt 0 ]; do
    case $1 in
	-u) UPPERCASE=1 ;;		    # Discuss: flags
	-c) COWFILE=$2; shift ;;	    # Discuss: double shifts
	-h) usage 0 ;;
	-*) usage 1 ;;
	 *) break ;;
    esac
    shift
done

MESSAGE="$@"

# Main Execution

if [ -z "$MESSAGE" ]; then		    # Discuss: testing strings
    usage 1
fi

if [ $UPPERCASE -eq 0 ]; then		    # Discuss: testing integers
    cowsay -f $COWFILE $MESSAGE
else					    # Discuss: translate / filters
    echo $MESSAGE | tr a-z A-Z | cowsay -f $COWFILE 
fi
