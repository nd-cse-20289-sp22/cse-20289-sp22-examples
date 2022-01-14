#!/bin/sh

# Globals

PATTERN=""
KILL=0
SIGNAL="TERM"

# Functions

usage() {					    # Review: I/O redirection, Here document
    cat 1>&2 <<EOF
Usage: process-hunter PATTERN

-k	    Kill processes that match PATTERN
-s SIGNAL   Signal to use when killing processes
EOF
    exit $1					    # Discuss: Function parameters
}

search_processes () {				    # Review: Pipeline with grep
    ps aux | grep "$PATTERN"
}

list_processes() {				    # Discuss: awk and sort
    search_processes | awk '{printf "%8d %s\n", $2, $1}' | sort -k 2 -k 1n
}

kill_processes() {
    EXITCODE=0
						    # Review: for loop, command substitution
    for pid in $(search_processes | awk '{print $2}'); do
    	[ $pid -eq $$ ] && continue		    # Discuss: short ciruit evaluation

	if ! kill -$SIGNAL $pid 2> /dev/null; then  # Review: /dev/null, exit status
	    EXITCODE=$(($EXITCODE + 1))
	fi
    done

    return $EXITCODE				    # Discuss: Function return value
}

# Parse Command Line Arguments

while [ $# -gt 0 ]; do
    case $1 in
	-k) KILL=1 ;;				    # Discuss: flags
	-s) SIGNAL=$2; shift ;;			    # Discuss: shifts
	-h) usage 0 ;;
	-*) usage 1 ;;
	 *) break   ;;				    # Discuss: arguments
    esac
    shift
done

PATTERN="$@"

# Main Execution

if [ -z "$PATTERN" ]; then			    # Discuss: testing strings
    usage 1
fi

if [ $KILL -eq 0 ]; then			    # Discuss: testing integers
    list_processes
else
    kill_processes
fi
