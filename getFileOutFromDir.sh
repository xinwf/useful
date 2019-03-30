#!/bin/bash
cur_path=$(cd "$(dirname "$0")";pwd)
for dir in `ls $cur_path`
do
    if [ -d $cur_path"/"$dir ]
    then 
	mv $cur_path"/"$dir"/"* $cur_path
    fi
done
