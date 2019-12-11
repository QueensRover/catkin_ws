//
// Created by owen on 2019-11-18.
//

#include "ultrasonic_plugin.h"
#include "gazebo/physics/physics.hh"
#include <functional>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "sensor_msgs/Range.h"
#pragma  warning (disable : 4244)
using namespace gazebo;

GZ_REGISTER_SENSOR_PLUGIN(UltrasonicPlugin)

UltrasonicPlugin::UltrasonicPlugin() {}
void UltrasonicPlugin::Load(gazebo::sensors::SensorPtr _parent, sdf::ElementPtr _sdf) {
    this->parentSensor =
            std::dynamic_pointer_cast<sensors::RaySensor>(_parent);

    this->world = physics::get_world(this->parentSensor->WorldName());

    this->newLaserScansConnection =
            this->parentSensor->LaserShape()->ConnectNewLaserScans(
                    std::bind(&UltrasonicPlugin::OnNewLaserScans, this));

    ROS_INFO("GOTULTRA");

    if (!ros::isInitialized())
    {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "ultrasonic",
                  ros::init_options::NoSigintHandler);
    }
    this->rosNode.reset(new ros::NodeHandle("ultrasonic"));
    ROS_INFO("initNode");

    this->rosPub = this->rosNode->advertise<sensor_msgs::Range>("ultrasonicData", 1);

    ROS_INFO("subbe");
    // Spin up the queue helper thread.
}
void UltrasonicPlugin::OnNewLaserScans() {
    sensor_msgs::Range msg;
    msg.header.frame_id = "rover";
    msg.header.stamp = ros::Time::now();
    msg.radiation_type = 0;
    msg.field_of_view = 0;
    msg.max_range = 10;
    msg.min_range = 0.01;
    this->parentSensor->Ranges(this->_ranges);
    msg.range = (float)this->_ranges[0];
    rosPub.publish(msg);
    ros::spinOnce();
}
