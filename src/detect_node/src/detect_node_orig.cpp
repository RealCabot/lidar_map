#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "sensor_msgs/PointCloud.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"
#include "laser_geometry/laser_geometry.h"
#include <sstream>

class LaserScanToPointCloud{

public:

    ros::NodeHandle n_;
    laser_geometry::LaserProjection projector_;
    tf::TransformListener listener_;
    message_filters::Subscriber<sensor_msgs::LaserScan> laser_sub_;
    tf::MessageFilter<sensor_msgs::LaserScan> laser_notifier_;
    ros::Publisher scan_pub_;

    LaserScanToPointCloud(ros::NodeHandle n) :
            n_(n),
            laser_sub_(n_, "/scan", 10),
            laser_notifier_(laser_sub_,listener_, "/map", 10)
    {
        laser_notifier_.registerCallback(
                boost::bind(&LaserScanToPointCloud::scanCallback, this, _1));
        laser_notifier_.setTolerance(ros::Duration(0.01));
        //laser_notifier_->setTolerance(ros::Duration(0.01));
        scan_pub_ = n_.advertise<sensor_msgs::PointCloud>("/my_cloud",1);
    }

    void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_in)
    {
        sensor_msgs::PointCloud cloud;
        for(int i=0; i<scan_in->ranges.size(); i++){
            float dist = scan_in->ranges[i];
            ROS_INFO("%f: ", dist);

        }

        try
        {
            projector_.transformLaserScanToPointCloud(
                    "/map",*scan_in, cloud,listener_);


        }
        catch (tf::TransformException& e)
        {
            std::cout << e.what();
            ROS_INFO("here");
            return;
        }

        // Do something with cloud.
        //std::stringstream ss;
        //std::vector<float> clouds = cloud.points.;


        //for (int i=0; i<10; i++){
        //    ROS_INFO("%f", cloud.channels[i]);
        //}
        //ss << cloud.points[0] << ' ';

        //ROS_INFO("%s", ss.str());
        for(int i=0; i<cloud.points.size(); i++){
            float x_pt = cloud.points[i].x;
            float y_pt = cloud.points[i].y;
            float z_pt = cloud.points[i].z;
            ROS_INFO("x: %f, y: %f, z: %f", x_pt, y_pt, z_pt);
            static tf::TransformBroadcaster br;
            tf::Transform transform;
            transform.setOrigin(tf::Vector3(x_pt, y_pt, z_pt));

            //Put here a publish to mapping node if x,y,or z passes a certain point


        }

        scan_pub_.publish(cloud);

    }
};

int main(int argc, char** argv)
{

    ros::init(argc, argv, "detect_node");
    ros::NodeHandle n;
    LaserScanToPointCloud lstopc(n);

    ros::spin();

    return 0;
}