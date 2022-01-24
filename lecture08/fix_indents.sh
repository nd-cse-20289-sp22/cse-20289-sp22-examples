#!/bin/sh

# Functions

usage() {
    cat <<EOF
Usage: $(basename $0)
    -t TARGET	Specifies the target conversion type (spaces|tabs)
    -w WIDTH	Specifies how many spaces corresponds to one tab
EOF
    exit $1
}

# Parse command-line options

TARGET='spaces'
WIDTH=4

while [ $# -gt 0 ]; do
    case $1 in
	-t) TARGET=$2; shift;;
	-w) WIDTH=$2; shift;;
	-h) usage 0;;
	*)  usage 1;;
    esac
    shift
done

# Main execution: filter pipeline

SPACES=""
for i in $(seq $WIDTH); do
    SPACES=$SPACES" "
done

if [ "$TARGET" = "spaces" ]; then
    sed "s|\t|$SPACES|g"
else
    sed "s|$SPACES|\t|g"
fi
