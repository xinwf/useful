#include <iostream>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <actionlib_msgs/GoalStatusArray.h>


void laserCallback(const sensor_msgs::LaserScanConstPtr &scan_ptr)
{
    sensor_msgs::LaserScan scan = *scan_ptr;
    std::cout << "scan.angle_min: " << scan.angle_min << "\n";
    std::cout << "scan.angle_max: " << scan.angle_max << "\n";
    std::cout << "scan.range_size: " << scan.ranges.size() << "\n";
    int count = 0;
    for(auto range = scan.ranges.begin(); range != scan.ranges.end(); ++range)
    {
        ++ count;
        std::cout <<count <<": "<< *range << "\n";
    }
    exit(0);
}

void moveBaseStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr& status)
{
    if (!status->status_list.empty()){
        ROS_INFO_STREAM("movebase status: " << (unsigned)status->status_list[0].status);
        // if(status->status_list[0].status == actionlib_msgs::GoalStatus::ACTIVE)
        //     ROS_INFO("Active");
        // ROS_INFO("movebase status: %d", status->status_list[0].status);
        // std::cout << (int)status->status_list[0].status << std::endl;
    }else{
        ROS_INFO_STREAM("movebase status blank");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "laser_data_parser");
    
    ros::NodeHandle nh;

    // ros::Subscriber sub = nh.subscribe("/raw_scan", 1000, laserCallback);
    ros::Subscriber sub = nh.subscribe("/move_base/status", 10, moveBaseStatusCallback);

    // ros::Time time1(0);
    // ros::Time time2(5);
    // if((time2-time1) >ros::Duration(6)) std::cout << "time is \n";

    ros::spin();

    return 0;

}