#!/bin/bash
cur_path=$(cd "$(dirname "$0")";pwd)
i=0
for dir in `ls $cur_path`
do

    if [ -d $cur_path"/"$dir ]
    then 
    ((i=$i+1))
    # echo $i
    #cp $cur_path"/"$dir"/"* $cur_path"/"${i}".jpg"
	cp $cur_path"/"$dir"/"* $cur_path
    # rmdir $cur_path"/"$dir
    fi
done
