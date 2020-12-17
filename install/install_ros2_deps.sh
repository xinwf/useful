#!/bin/bash

add_ros_source(){
    echo "Add ros source ..."
    if [ ! -f "/etc/apt/sources.list.d/ros-latest.list" ]; then
        sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
        sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
        sudo apt update
    else
        echo "Ros source has been added."
    fi
}

# install ros deps
# python3-argcomplete: auto tab complete
# python3-colcon-ros: compile tool
# ros-eloquent-test-msgs: nav2_util package
# ros-eloquent-behaviortree-cpp-v3: nav2_behavior_tree package
# graphicsmagick-libmagick-dev-compat: nav2_map_server package
# ros-eloquent-gazebo-ros-pkgs: nav2_system_tests package
install_ros2_deps(){
    sudo apt install -y ros-eloquent-desktop \
    python3-argcomplete \
    python3-colcon-ros \
    ros-eloquent-test-msgs \
    ros-eloquent-behaviortree-cpp-v3 \
    graphicsmagick-libmagick-dev-compat \
    ros-eloquent-gazebo-ros-pkgs
}

set_ros_env(){
    echo "Set ros environment ..."
    file=${HOME}/.bashrc
    checkStr="/opt/ros/kinetic/setup.bash"
    key="source"
    added=false
    while read line
    do
        result1=$(echo $line | grep "${checkStr}")
        result2=$(echo $line | grep "${key}")

        if [[ $result1 != "" && $result2 != "" ]]; then
        # if [[ $line =~ $checkStr && $line =~ $key ]]; then
            added=true
        else
            continue
        fi
    done < $file

    if ! $added; then
        sh -c 'echo "source " >> $HOME/.bashrc'
        echo "Add source statement to bashrc"
    else
        echo "source statement has been added to .bashrc"
    fi      
}
