#include "gazebo/physics/physics.hh"
#include "LeddarPlugin.hh"
#include <functional>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include <sensor_msgs/LaserScan.h>
#pragma warning (disable : 4244)
using namespace gazebo;

GZ_REGISTER_SENSOR_PLUGIN(LeddarPlugin)

LeddarPlugin::LeddarPlugin() {}

void LeddarPlugin::Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf)
{
    this->parentSensor =
        std::dynamic_pointer_cast<sensors::RaySensor>(_parent);

    this->world = physics::get_world(this->parentSensor->WorldName());

    this->newLaserScansConnection =
        this->parentSensor->LaserShape()->ConnectNewLaserScans(
            std::bind(&LeddarPlugin::OnNewLaserScans, this));

    ROS_INFO("GOTMODEL");

    if (!ros::isInitialized())
    {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "leddar",
                  ros::init_options::NoSigintHandler);
    }
    this->rosNode.reset(new ros::NodeHandle("leddar"));
    ROS_INFO("initNode");

    this->rosPub = this->rosNode->advertise<sensor_msgs::LaserScan>("leddarData", 1);

    ROS_INFO("subbe");
    // Spin up the queue helper thread.
}

void LeddarPlugin::OnNewLaserScans()
{
    //ROS_INFO("yeeeeeeet");
    //refresh code goes here
    //this->parentSensor->Ranges(this->_ranges);
    //ROS_INFO("%f", &this->_ranges[0]);

    //ROS_INFO("%f", this->parentSensor->Range(0));
    sensor_msgs::LaserScan msg;
    msg.header.frame_id = "leddar";
    msg.header.stamp = ros::Time::now();
    msg.angle_min = -0.3926991;
    msg.angle_max = 0.3926991;
    msg.angle_increment = (0.785398163 / 16);
    msg.range_min = 0.0;
    msg.range_max = 50.0;
    this->parentSensor->Ranges(this->_ranges);
    //msg.ranges = (this->_ranges)
    for(size_t i = 0; i < this->_ranges.size(); i++)
    {
        msg.ranges.push_back((float)this->_ranges[i]);
    }
    
    
    rosPub.publish(msg);
    ros::spinOnce();
}