#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/JointState.h>
#include "cui_encoders/arm_pos_enc_vals.h"

#define ROVER_FRAME "rover"
#define SHOULDER_FRAME "shoulder"
#define ELBOW_FRAME "elbow"
#define WRIST_FRAME "wrist"
#define FIRST_LINK_LEN 0.124
#define SECOND_LINK_LEN 0.09
#define ORIGIN_TO_BASE_Y 0.25 //change this ------------------------------------------------------------
#define ORIGIN_TO_BASE_X 0.0
#define ORIGIN_TO_BASE_Z 0.05
#define PAN_ANGLE_OFFSET 0.0
#define SHOULDER_ANGLE_OFFSET 0.0
#define ELBOW_ANGLE_OFFSET 0.0
#define WRIST_ANGLE_OFFSET 0.0

float angle[4] = {0,0,0,0};
void angle_callback(cui_encoders::arm_pos_enc_vals msg){
    angle[0] = msg.pan;
    angle[1] = msg.shoulder;
    angle[2] = msg.elbow;
    angle[3] = msg.wrist;


    tf::TransformBroadcaster br;
    tf::Transform shoulder_transform;
    tf::Quaternion shoulder_quaternion;

    shoulder_transform.setOrigin(tf::Vector3(ORIGIN_TO_BASE_X, ORIGIN_TO_BASE_Y, ORIGIN_TO_BASE_Z));
    shoulder_quaternion.setRPY(0, angle[1] + SHOULDER_ANGLE_OFFSET, angle[0] + PAN_ANGLE_OFFSET);
    shoulder_transform.setRotation(shoulder_quaternion);
    br.sendTransform(tf::StampedTransform(shoulder_transform, ros::Time::now(), ROVER_FRAME, SHOULDER_FRAME));

    tf::Transform elbow_transform;
    tf::Quaternion elbow_quaternion;

    elbow_transform.setOrigin(tf::Vector3(0,0,FIRST_LINK_LEN));
    elbow_quaternion.setRPY(0, angle[2] + ELBOW_ANGLE_OFFSET, 0);
    elbow_transform.setRotation(elbow_quaternion);
    br.sendTransform(tf::StampedTransform(elbow_transform, ros::Time::now(), SHOULDER_FRAME, ELBOW_FRAME));

    tf::Transform wrist_transform;
    tf::Quaternion wrist_quaternion;

    wrist_transform.setOrigin(tf::Vector3(0,0,SECOND_LINK_LEN));
    wrist_quaternion.setRPY(0,angle[3] + WRIST_ANGLE_OFFSET, 0 );
    wrist_transform.setRotation(wrist_quaternion);
    br.sendTransform(tf::StampedTransform(wrist_transform, ros::Time::now(), ELBOW_FRAME, WRIST_FRAME));







}


int main(int argc, char** argv){
    ros::init(argc, argv, "end_of_arm_main_tf");
    ros::NodeHandle nh;

    ros::Subscriber angleSub = nh.subscribe("/encoders/arm_control/joint_states", 1, &angle_callback);
    ros::Rate rate(10);
    ros::spin();


}