#!/bin/bash

using_ali_source()
{
    if [ ! -f "/etc/apt/sources.list.old" ]; then
         mv /etc/apt/sources.list /etc/apt/sources.list.old
         sh -c 'echo \
"# deb cdrom:[Ubuntu 16.04 LTS _bionic Xerus_ - Release amd64 (20160420.1)]/ bionic main restricted
deb-src http://archive.ubuntu.com/ubuntu bionic main restricted #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ bionic universe
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates universe
deb http://mirrors.aliyun.com/ubuntu/ bionic multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse #Added by software-properties
deb http://archive.canonical.com/ubuntu bionic partner
deb-src http://archive.canonical.com/ubuntu bionic partner
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted multiverse universe #Added by software-properties
deb http://mirrors.aliyun.com/ubuntu/ bionic-security universe
deb http://mirrors.aliyun.com/ubuntu/ bionic-security multiverse" > /etc/apt/sources.list'
         apt update
    fi
}

add_ros_source_and_base()
{
    echo "Add ros source ..."
    using_ustc_source=$1
    if [ ! -f "/etc/apt/sources.list.d/ros-latest.list" ]; then
        if [ $using_ustc_source == true ]; then
             sh -c 'echo "deb http://mirrors.ustc.edu.cn/ros/ubuntu/ bionic main" > /etc/apt/sources.list.d/ros-latest.list'
            wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - |  apt-key add -
            #  apt-key adv --keyserver hkp://pool.sks-keyservers.net --recv-key 0xB01FA116
        else
             sh -c 'echo "deb http://packages.ros.org/ros/ubuntu bionic main" > /etc/apt/sources.list.d/ros-latest.list'
             apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
        fi
         apt update
    else
        echo "Ros source has been added."
    fi
     apt update
     apt-get install ros-melodic-ros-base -y
}

install_basic_deps()
{
     apt-get install -y python-rosnode python-catkin-tools rosbash rospack-tools ros-melodic-xacro ros-melodic-joint-state-publisher ros-melodic-dynamic-robot-state-publisher
     apt-get install -y ros-melodic-bfl # depends by robot_pose_ekf
     apt-get install -y ros-melodic-map-msgs # depends by costmap_2d
     apt-get install -y ros-melodic-pcl-conversions # depends by costmap_2d
     apt-get install -y ros-melodic-costmap-prohibition-layer
     apt-get install -y ros-melodic-costmap-converter ros-melodic-mbf-costmap-core ros-melodic-mbf-msgs ros-melodic-libg2o ros-melodic-tf-conversions # depend by teb_local_planner
     apt-get install -y ros-melodic-rosbridge-suite 
     apt-get install -y ros-melodic-rosconsole
     apt-get install -y ros-melodic-serial
     apt-get install -y ros-melodic-gmapping 
     apt-get install -y ros-melodic-laser-filters
     apt-get install -y ros-melodic-tf2-sensor-msgs
     apt-get install -y ros-melodic-ecl-threads # depends by yocs_velocity_smoother
     apt-get install -y libbullet-dev libsdl1.2-dev libsdl-image1.2 libsdl-image1.2-dev # depends by map_server
}

install_fuse_odom_deps()
{
     apt-get install -y ros-melodic-robot-localization
}

install_new_localization_deps()
{
     apt-get install -y ros-melodic-mrpt-localization
}

install_teaching_mode_deps()
{
     apt-get install -y ros-melodic-tf ros-melodic-geometry-msgs ros-melodic-dynamic-reconfigure ros-melodic-nav-msgs ros-melodic-pluginlib ros-melodic-actionlib ros-melodic-angles ros-melodic-interactive-markers
}

install_path_gen_deps()
{
    echo "Install room exploration deps ..."
    apt install -y ros-melodic-cob-map-accessibility-analysis \
    coinor-libcoinutils-dev ros-melodic-libdlib ros-melodic-move-base-msgs\
    ros-melodic-opengm coinor-libcbc-dev coinor-libcgl-dev \
    coinor-libclp-dev coinor-libosi-dev coinor-libcoinutils-dev #ros-melodic-libconcorde-tsp-solver
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
    checkStr="/opt/ros/melodic/setup.bash"
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
        sh -c 'echo "source /opt/ros/melodic/setup.bash" >> $HOME/.bashrc'
        echo "Add source statement to bashrc"
    else
        echo "source statement has been added to .bashrc"
    fi      
}

enable_ssh_server()
{
     apt-get install -y openssh-server
     service sshd start
}

#using_ali_source

#using_ustc_source=true
#add_ros_source_and_base $using_ustc_source

install_project_deps

#set_ros_env
#
#enable_ssh_server
