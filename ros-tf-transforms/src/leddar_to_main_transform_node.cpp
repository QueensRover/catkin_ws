#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#define ORIGIN_TO_CAMERA 0.568325
#define ROVER_FRAME "rover"
#define LEDDAR_FRAME "leddar"

int main(int argc, char **argv){
    ros::init(argc, argv, "leddar_main_tf");
    ros::NodeHandle nh;

    tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion quaternion;
    
    ros::Rate rate(30);

    while(ros::ok()){
        transform.setOrigin(tf::Vector3(ORIGIN_TO_CAMERA,0,0));
        quaternion.setRPY(0,0,0);
        transform.setRotation(quaternion);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), ROVER_FRAME, LEDDAR_FRAME));
        rate.sleep();
    }
    return 0;
}