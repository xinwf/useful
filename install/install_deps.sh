#!/bin/bash

# install basic
# glog deps : autoconf automake libtool
# lua 5.3.5 : libreadline-dev
install_basic(){
    sudo apt install -y curl git \
         autoconf automake libtool \
         libreadline-dev \
         libsuitesparse-dev
    mkdir ${HOME}/tmp
}

add_ros_source(){
    if [ ! -f "/etc/apt/sources.list.d/ros-latest.list" ]; then
        sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
        sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
        sudo apt update
    else
        echo "Ros source has been added."
    fi
}

install_glog(){
    if [ ! -d "/usr/local/include/glog" ]; then
        cd ${HOME}/tmp
        git clone https://github.com/google/glog.git
        cd glog
        bash autogen.sh && ./configure && make -j4 && sudo make install
        # cd -
    else
        echo "Glog has been installed."
    fi
}

install_gflag(){
    if [ ! -f "/usr/local/include/gflags/gflags.h" ]; then
        # cur_dir=$(cd "$(dirname "$0")";pwd)
        cd ${HOME}/tmp
        git clone https://github.com/gflags/gflags.git
        cd gflags
        mkdir build && cd build && cmake .. && make -j4 && sudo make install
        # cd ${cur_dir}
    else
        echo "Gflag has been installed."
    fi
}

install_lua(){
    if [ ! -f "/usr/local/include/lua.h" ]; then
        cd ${HOME}/tmp
        curl -R -O http://www.lua.org/ftp/lua-5.3.5.tar.gz
        tar zxf lua-5.3.5.tar.gz
        sed -i 's/MYCFLAGS=/MYCFLAGS=-fPIC/g' $(cd "$(dirname "$0")";pwd)/lua-5.3.5/src/Makefile
        cd lua-5.3.5 && make linux -j4 && sudo make install
        # cd -
    else
        echo "Lua has been installed."
    fi
}

install_protobuf3_4_1(){
    if [ ! -d "/usr/local/include/google/protobuf" ]; then
        # cur_dir=$(cd "$(dirname "$0")";pwd)
        cd ${HOME}/tmp

        VERSION="3.4.1"

        curl -R -o protobuf-${VERSION}.tar.gz https://codeload.github.com/protocolbuffers/protobuf/tar.gz/v${VERSION}
        tar zxf protobuf-${VERSION}.tar.gz
        cd protobuf-${VERSION}
        ./autogen.sh && ./configure && make -j4 && sudo make install
        # cd ${cur_dir}
    else
        echo "Protobuf has been installed."
    fi
}

# install ros deps
# auto_charge: ros-kinetic-serial
# ecl_mobile_robot: ros-kinetic-ecl-mobile-robot
# battery: ros-kinetic-ecl-command-line ros-kinetic-ecl-devices ros-kinetic-ecl-sigslots ros-kinetic-ecl-streams 
# hokuyo_node : ros-kinetic-driver-base
# fake_localization : ros-kinetic-angles
# init_pose : libbullet-dev libsdl1.2-dev libsdl-image1.2-dev
# follow_waypoints: ros-kinetic-move-base-msgs ros-kinetic-smach
# room exploration: ros-kinetic-cob-map-accessibility-analysis \
#    coinor-libcoinutils-dev ros-kinetic-libdlib \
#    ros-kinetic-opengm coinor-libcbc-dev coinor-libcgl-dev \
#    coinor-libclp-dev coinor-libosi-dev coinor-libcoinutils-dev 
# kobuki_bumper2pc: ros-kinetic-kobuki-msgs
# robot_pose_ekf : ros-kinetic-bfl
# turtlebot_teleop : ros-kinetic-teleop-twist-joy
# teb_local_planner : ros-kinetic-costmap-converter
install_ros_deps(){
    sudo apt install -y ros-kinetic-desktop-full \
    ros-kinetic-serial \
    ros-kinetic-ecl-mobile-robot \
    ros-kinetic-ecl-command-line ros-kinetic-ecl-devices ros-kinetic-ecl-sigslots ros-kinetic-ecl-streams \
    ros-kinetic-driver-base \
    libbullet-dev libsdl1.2-dev libsdl-image1.2-dev \
    ros-kinetic-move-base-msgs \
    ros-kinetic-kobuki-msgs \
    ros-kinetic-cob-map-accessibility-analysis \
    coinor-libcoinutils-dev ros-kinetic-libdlib \
    ros-kinetic-opengm coinor-libcbc-dev coinor-libcgl-dev \
    coinor-libclp-dev coinor-libosi-dev coinor-libcoinutils-dev \
    ros-kinetic-bfl \
    ros-kinetic-teleop-twist-joy \
    ros-kinetic-costmap-converter ros-kinetic-libg2o
}

set_ros_env(){
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
        sh -c 'echo "source /opt/ros/kinetic/setup.bash" >> $HOME/.bashrc'
        echo "Add source statement to bashrc"
    fi      
}

#glog lua protobuf needed by ist_slam

# add_ros_source
# install_basic
# install_glog
install_gflag
# install_lua
# install_protobuf3_4_1
# install_ros_deps
# set_ros_env
