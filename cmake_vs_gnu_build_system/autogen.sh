#!/bin/sh

aclocal
autoconf
autoheader


touch INSTALL NEWS README AUTHORS ChangeLog COPYING
touch install-sh missing

automake -i

if [ ! -d _build ]; then 
    mkdir _build/
fi

