#include <fstream>

#include <ros/ros.h>
#include <com/GetPlan.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "task_plan_req");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<com::GetPlan>("/move_base/navi_plan");
    com::GetPlan srv;
    
    // srv.request.path = "/home/xwf/tmp/path";
    // srv.request.path = "/home/xwf/tmp/path2";
    srv.request.path = "/home/xwf/tmp/path3";
    srv.request.exec_last = false;
    srv.request.type = com::GetPlan::Request::TASK;
    srv.request.goal.header.frame_id = "map";

    geometry_msgs::Pose pose;
    // pose.position.x = 11.4729;
    // pose.position.y = -3.56622;
    // double theta = 0.208645;
    // pose.position.x = 10.9639;
    // pose.position.y = -0.891894;
    // double theta = -0.184175;
    pose.position.x = 8.08995;
    pose.position.y = -2.86909;
    double theta = 3.08869;
    pose.orientation.z = std::sin(theta/2);
    pose.orientation.w = std::cos(theta/2);
    srv.request.goal.pose = pose;

    // std::ifstream ifs(srv.request.path);
    // ifs >> pose.pose.position.x >> pose.pose.position.y >> theta;
    // pose.pose.orientation.z = std::sin(theta/2);
    // pose.pose.orientation.w = std::cos(theta/2);

    if (client.call(srv))
    {
        ROS_INFO("status_code: %d", srv.response.status_code);
    }
    else
    {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }

    return 0;
}