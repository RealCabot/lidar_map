#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/PointCloud.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"
#include "laser_geometry/laser_geometry.h"

using namespace std;

ros::Subscriber get_laser;

void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_in){
    bool turn_r = 0;
    bool turn_l = 0;
    ROS_INFO("New Range");
    for(int i=0; i<scan_in->ranges.size(); i++){
            float dist = scan_in->ranges[i];
            if (i < scan_in->ranges.size()/2){
                if (dist <= 0.07){
                    ROS_INFO("Right: %f", dist);
                    turn_l = 1;
                }
            }
            if (i > scan_in->ranges.size()/2){
                if (dist <= 0.06){
                    ROS_INFO("Left: %f", dist);
                    turn_r = 1;
                }
            }

        }
        ROS_INFO("turn right: %d, turn left: %d", turn_r, turn_l);
        turn_r = 0;
        turn_l = 0;

}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "detect_node");
    ros::NodeHandle n;
    ros::Subscriber get_laser = n.subscribe("scan", 100, laser_callback);

    ros::Rate loop_rate(50);
    ROS_INFO("in main");

    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }

}


