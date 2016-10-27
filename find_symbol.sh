#!/bin/sh

if [ $# != 2 ];then
  echo "Usage: find_symbol.sh <path> <symbol>" 
  echo "     : find_symbol.sh /usr/lib printf" 
  exit
fi

GREP_SO_LIST=`find $1 -type f -name '*.so'`

for i in $GREP_SO_LIST
do
    #echo $i
    nm --defined-only -A $i 2>&1 | grep -i $2 | grep -iv 'no symbols'
done

 
