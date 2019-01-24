#!/bin/bash
find . -name "*.$1" -printf '%s:%p\0' | sort -t: -zrn | awk -vRS='\0' -v num=$2 -F: 'NR-1==num {exit} {print $2 " : " $1} {total = total + $1} END {print "Total size: " total}'
