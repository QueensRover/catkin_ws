#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Float32.h>

//all units in metres, rads
#define ORIGIN_TO_LEDDAR 0.568325
#define ROVER_FRAME "rover"
#define CAMERA_FRAME "camera"




void camera_angle_callback(std_msgs::Float32 msg){
    static tf::TransformBroadcaster br;
    tf::Transform  transform;
    transform.setOrigin(tf::Vector3(0 , ORIGIN_TO_LEDDAR , 0));
    tf::Quaternion q;
    q.setRPY(0,0,msg.data);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(), ROVER_FRAME,CAMERA_FRAME));
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "camera_main_tf");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/camera/angle/radians", 1, &camera_angle_callback);
    ros::Rate loop_rate(30);
    ros::spin();
}