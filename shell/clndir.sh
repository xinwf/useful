#!/bin/bash

for dirItem in $(find $1 -name "*$2*")
do
    if [ -d $dirItem ]; then
        echo 'Delete '$dirItem
        rm -rf $dirItem
    fi
done