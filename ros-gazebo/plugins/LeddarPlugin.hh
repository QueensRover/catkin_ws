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
/// \brief A Ray Sensor Plugin
class LeddarPlugin : public SensorPlugin
{
    /// \brief Constructor
  public:
    LeddarPlugin();

    /// \brief Update callback
  public:
    virtual void OnNewLaserScans();

    /// \brief Load the plugin
    /// \param take in SDF root element
  public:
    void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);

  private:
    void QueueThread();
    /// \brief Pointer to parent
  protected:
    physics::WorldPtr world;

    /// \brief The parent sensor
  private:
    sensors::RaySensorPtr parentSensor;

    /// \brief The connection tied to RayPlugin::OnNewLaserScans()
  private:
    event::ConnectionPtr newLaserScansConnection;

  private:
    std::unique_ptr<ros::NodeHandle> rosNode;

    /// \brief A ROS subscriber
  private:
    ros::Publisher rosPub;




  private:
    std::vector<double> _ranges;
};
} // namespace gazebo
#endif