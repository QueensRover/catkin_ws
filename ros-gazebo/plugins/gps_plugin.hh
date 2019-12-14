#ifndef _LEDDARPLUGIN_HH_
#define _LEDDARPLUGIN_HH_

#include "gazebo/common/Plugin.hh"
#include "gazebo/sensors/SensorTypes.hh"
#include "gazebo/sensors/RaySensor.hh"
#include "gazebo/util/system.hh"

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"

namespace gazebo
{

    class GpsPlugin : public ModelPlugin
    {
    public:
        GpsPlugin();

    protected:
        virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
        virtual void QueueThread();

    private:
        physics::WorldPtr world;
        physics::LinkPtr link;
        std::string link_name_;
        std::string topic;
        ros::NodeHandle nodeHandle;
        ros::Publisher posPub;
        std::thread rosQueueThread;


    };
}

#endif