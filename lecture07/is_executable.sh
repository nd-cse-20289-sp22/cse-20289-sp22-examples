#!/bin/sh

# Check if each command line argument is executable

NONEXECUTABLE=""

for arg in $@; do
    if [ ! -x "$arg" ]; then
	NONEXECUTABLE="$NONEXECUTABLE $arg"
    fi
done

echo "The following files are not executable:$NONEXECUTABLE"
