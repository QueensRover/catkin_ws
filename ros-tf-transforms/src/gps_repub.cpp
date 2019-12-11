#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>



ros::Publisher pub;
void gps_callback(sensor_msgs::NavSatFix msg_){
    sensor_msgs::NavSatFix msg= msg_;

    for(int row = 0; row < 3; ++ row){
	for(int col = 0; col < 3; ++ col){
	    msg.position_covariance[row*3+col] = (row==col? 0.000016188:0);
}
}
    msg.header.frame_id = "rover";
    msg.position_covariance_type = 1;
    pub.publish(msg);
}

int main (int argc, char**argv){
    ros::init(argc,argv, "gps_repub");
    ros::NodeHandle nh;
    pub = nh.advertise<sensor_msgs::NavSatFix>("/fix/with_covariance", 1);
    ros::Subscriber sub = nh.subscribe("/fix",1,gps_callback);
    ros::Rate rate(10);
    ros::spin();
}
