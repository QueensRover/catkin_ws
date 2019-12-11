//
// Created by owen on 2019-11-18.
//

#ifndef ROS_GAZEBO_ULTRASONIC_PLUGIN_H
#define ROS_GAZEBO_ULTRASONIC_PLUGIN_H
#include "gazebo/common/Plugin.hh"
#include "gazebo/sensors/SensorTypes.hh"
#include "gazebo/sensors/RaySensor.hh"
#include "gazebo/util/system.hh"

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"

namespace gazebo {
    class UltrasonicPlugin : public SensorPlugin {
    public:
        UltrasonicPlugin();
        virtual void OnNewLaserScans();
        void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);
    protected:
        physics::WorldPtr world;
    private:
        sensors::RaySensorPtr parentSensor;
        event::ConnectionPtr newLaserScansConnection;
        std::unique_ptr<ros::NodeHandle> rosNode;
        ros::Publisher rosPub;
        std::vector<double> _ranges;
    };
}


#endif //ROS_GAZEBO_ULTRASONIC_PLUGIN_H
