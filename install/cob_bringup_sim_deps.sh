#!/bin/bash

# autopnp 
# sudo apt-get remove -y ros-kinetic-moveit-ros-move-group ros-kinetic-libpcan ros-kinetic-cob-srvs ros-kinetic-cob-navigation-global \
#         ros-kinetic-pr2-controllers-msgs ros-kinetic-moveit-ros-planning-interface ros-kinetic-cob-bringup 

# cob_bringup_sim
sudo apt-get install -y ros-kinetic-cob-supported-robots ros-kinetic-cob-description ros-kinetic-cob-calibration-data \
        ros-kinetic-cob-base-controller-utils ros-kinetic-cob-script-server ros-kinetic-cob-monitoring ros-kinetic-cob-bms-driver \
        ros-kinetic-canopen-motor-node ros-kinetic-twist-mux ros-kinetic-cob-base-velocity-smoother ros-kinetic-cob-dashboard \
        ros-kinetic-cob-teleop