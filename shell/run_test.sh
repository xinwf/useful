#!/bin/bash
if [ $# -eq 0 ]; then
    echo "You should input a param, how many times you want to run test."
    exit 1;
fi

source /root/re/setup.bash

# start_client='roslaunch ipa_room_exploration room_exploration_client.launch customized_area:=true reuse_click_point:=true \
#                 click_point:="280,630 260,1055 320,1060 345,636" goal_eps:=1.0 path_eps:=20 execute_path:=true test_time:='

for i in $(seq 1 $1)
do
    roslaunch ipa_room_exploration room_exploration_client.launch customized_area:=true reuse_click_point:=true \
                click_point:="280,630 260,1055 320,1060 345,636" goal_eps:=1.0 path_eps:=20 execute_path:=true test_time:=$i
    # echo $start_client
    while [[ ! -e $HOME/$i ]]
    do
        # echo "sleep"
        sleep 5s
    done
done