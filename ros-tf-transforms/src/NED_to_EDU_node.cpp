#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

ros::Publisher pub;

void imu_callback(sensor_msgs::Imu msg_){
    sensor_msgs::Imu msg = msg_;
    float y = msg.angular_velocity.x;
    msg.angular_velocity.x = msg.angular_velocity.y;
    msg.angular_velocity.y = y;
    msg.angular_velocity.z *= -1;

    y = msg.linear_acceleration.x;
    msg.linear_acceleration.x = msg.linear_acceleration.y;
    msg.linear_acceleration.y = y;
    msg.linear_acceleration.z *= -1;

    y = msg.orientation.x;
    msg.orientation.x = msg.orientation.y;
    msg.orientation.y = y;
    msg.orientation.z *= -1;

    for(unsigned row = 0; row < 3; ++ row) {
        for(unsigned col = 0; col < 3; ++ col) {
            msg.orientation_covariance[row * 3 + col] = (row == col? 0.002: 0.);  // +-2.5deg
            msg.angular_velocity_covariance[row * 3 + col] = (row == col? 0.003: 0.);  // +-3deg/s
            msg.linear_acceleration_covariance[row * 3 + col] = (row == col? 0.60: 0.);  // +-80mg
        }
    }
    msg.header.frame_id = "rover";

    pub.publish(msg);


}

int main(int argc, char ** argv){
    ros::init(argc, argv, "NED_to_EDU");
    ros::NodeHandle nh;
    pub = nh.advertise<sensor_msgs::Imu>("/imu/enu",1);
    ros::Subscriber sub = nh.subscribe("/imu",1,imu_callback);
    ros::Rate rate(10);
    ros::spin();
}
