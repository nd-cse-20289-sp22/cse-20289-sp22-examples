#!/bin/sh

# Download and install cmatrix

URL=https://github.com/abishekvashok/cmatrix/archive/1.2.tar.gz
PREFIX=${PREFIX:-/tmp/pub}

wget $URL
tar xvf $(basename $URL)

cd cmatrix-1.2
./configure --prefix $PREFIX
make
make install
