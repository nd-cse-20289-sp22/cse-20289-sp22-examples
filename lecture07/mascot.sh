#!/bin/sh

case $(uname) in
    Darwin|*BSD)
    	cowsay -f daemon "$@"
    ;;
    Linux)
    	cowsay -f tux "$@"
    ;;
    *)
    	cowsay "$@"
    ;;
esac
