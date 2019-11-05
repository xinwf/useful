#!/bin/bash

using_ali_source()
{
    sudo mv /etc/apt/sources.list /etc/apt/sources.list.old
    sudo sh -c 'echo \
"# deb cdrom:[Ubuntu 16.04 LTS _Xenial Xerus_ - Release amd64 (20160420.1)]/ xenial main restricted
deb-src http://archive.ubuntu.com/ubuntu xenial main restricted #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ xenial main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ xenial main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ xenial-updates main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-updates main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ xenial universe
deb http://mirrors.aliyun.com/ubuntu/ xenial-updates universe
deb http://mirrors.aliyun.com/ubuntu/ xenial multiverse
deb http://mirrors.aliyun.com/ubuntu/ xenial-updates multiverse
deb http://mirrors.aliyun.com/ubuntu/ xenial-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-backports main restricted universe multiverse #Added by software-properties
deb http://archive.canonical.com/ubuntu xenial partner
deb-src http://archive.canonical.com/ubuntu xenial partner
deb http://mirrors.aliyun.com/ubuntu/ xenial-security main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-security main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ xenial-security universe
deb http://mirrors.aliyun.com/ubuntu/ xenial-security multiverse" > /etc/apt/sources.list'
    sudo apt update
}

add_ros_source_and_base()
{
    echo "Add ros source ..."
    if [ ! -f "/etc/apt/sources.list.d/ros-latest.list" ]; then
        sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
        sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
        sudo apt update
    else
        echo "Ros source has been added."
    fi
    sudo apt update
    sudo apt-get install ros-kinetic-ros-base -y
}

install_basic_deps()
{
    sudo apt-get install -y ros-kinetic-bfl # depends by robot_pose_ekf
    sudo apt-get install -y ros-kinetic-map-msgs # depends by costmap_2d
    sudo apt-get install -y ros-kinetic-costmap-converter ros-kinetic-mbf-costmap-core ros-kinetic-mbf-msgs ros-kinetic-libg2o ros-kinetic-tf-conversions # depend by teb_local_planner
    sudo apt-get install -y ros-kinetic-rosbridge-suite 
    sudo apt-get install -y ros-kinetic-rosconsole
    sudo apt-get install -y ros-kinetic-serial
    sudo apt-get install -y ros-kinetic-gmapping 
    sudo apt-get install -y ros-kinetic-laser-filters
    sudo apt-get install -y ros-kinetic-tf2-sensor-msgs
    sudo apt-get install -y ros-kinetic-ecl-threads # depends by yocs_velocity_smoother
    sudo apt-get install -y libbullet-dev libsdl1.2-dev libsdl-image1.2 libsdl-image1.2-dev # depends by map_server
}

install_fuse_odom_deps()
{
    sudo apt-get install -y ros-kinetic-robot-localization
}

install_new_localization_deps()
{
    sudo apt-get install -y ros-kinetic-mrpt-localization
}

install_teaching_mode_deps()
{
    sudo apt-get install -y ros-kinetic-tf ros-kinetic-geometry-msgs ros-kinetic-dynamic-reconfigure ros-kinetic-nav-msgs ros-kinetic-pluginlib ros-kinetic-actionlib ros-kinetic-angles ros-kinetic-interactive-markers
}

install_path_gen_deps()
{
    echo "Install room exploration deps ..."
    sudo apt install -y ros-kinetic-cob-map-accessibility-analysis \
    coinor-libcoinutils-dev ros-kinetic-libdlib ros-kinetic-move-base-msgs\
    ros-kinetic-opengm coinor-libcbc-dev coinor-libcgl-dev \
    coinor-libclp-dev coinor-libosi-dev coinor-libcoinutils-dev ros-kinetic-libconcorde-tsp-solver
}

install_project_deps()
{
    install_basic_deps

    install_fuse_odom_deps
    
    install_new_localization_deps

    install_teaching_mode_deps

    install_path_gen_deps
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
        sh -c 'echo "source /opt/ros/kinetic/setup.bash" >> $HOME/.bashrc'
        echo "Add source statement to bashrc"
    else
        echo "source statement has been added to .bashrc"
    fi      
}

enable_ssh_server()
{
    sudo apt-get install -y openssh-server
    sudo service sshd start
}

using_ali_source

add_ros_source_and_base

install_project_deps

set_ros_env

enable_ssh_server
