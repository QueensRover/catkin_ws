#ifndef _ROVER_PLUGIN_HH_
#define _ROVER_PLUGIN_HH_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "wheelSpeed.h"

namespace gazebo
{
/// \brief A plugin to control rover
class RoverPlugin : public ModelPlugin
{
public:
  /// \brief Constructor
  RoverPlugin() {}

private:
  physics::ModelPtr model;

  /// \brief Pointer to the joint.
private:
  physics::JointPtr joint0;
  physics::JointPtr joint1;
  physics::JointPtr joint2;
  physics::JointPtr joint3;

  /// \brief A PID controller for the joint.
private:
  common::PID pid0;
  common::PID pid1;
  common::PID pid2;
  common::PID pid3;

  /// \brief A node use for ROS transport
private:
  std::unique_ptr<ros::NodeHandle> rosNode;

  /// \brief A ROS subscriber
private:
  ros::Subscriber rosSub;
  ros::Publisher testPub;
  /// \brief A ROS callbackqueue that helps process messages
private:
  ros::CallbackQueue rosQueue;

  /// \brief A thread the keeps running the rosQueue
private:
  std::thread rosQueueThread;

private:
  float setPoints[2] = {0, 0};

private:
  float motorSpeed[4] = {0, 0, 0, 0};

  /// \brief The load function is called by Gazebo when the plugin is
  /// inserted into simulation
  /// \param[in] _model A pointer to the model that this plugin is
  /// attached to.
  /// \param[in] _sdf A pointer to the plugin's SDF element.
public:
  virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
  {

    // Store the model pointer for convenience.
    this->model = _model;
    ROS_INFO("GOTMODEL");
    // Get the first joint. We are making an assumption about the model
    // having one joint that is the rotational joint.
    this->joint0 = _model->GetJoints()[0];
    this->joint1 = _model->GetJoints()[1];
    this->joint2 = _model->GetJoints()[2];
    this->joint3 = _model->GetJoints()[3];

    this->pid0 = common::PID(1, 0, 0);
    this->pid1 = common::PID(1, 0, 0);
    this->pid2 = common::PID(1, 0, 0);
    this->pid3 = common::PID(1, 0, 0);
    ROS_INFO("pids");
    this->model->GetJointController()->SetVelocityPID(
        this->joint0->GetScopedName(), this->pid0);

    this->model->GetJointController()->SetVelocityPID(
        this->joint1->GetScopedName(), this->pid1);

    this->model->GetJointController()->SetVelocityPID(
        this->joint2->GetScopedName(), this->pid2);

    this->model->GetJointController()->SetVelocityPID(
        this->joint3->GetScopedName(), this->pid3);
    ROS_INFO("setpids");
    // Initialize ros, if it has not already bee initialized.

    if (!ros::isInitialized())
    {
      int argc = 0;
      char **argv = NULL;
      ros::init(argc, argv, "gazebo_wheelControl",
                ros::init_options::NoSigintHandler);
    }
    this->rosNode.reset(new ros::NodeHandle("gazebo_wheelControl"));
    ROS_INFO("initNode");
    // Create our ROS node. This acts in a similar manner to
    // the Gazebo node

    // Create a named topic, and subscribe to it.
    /*ros::SubscribeOptions so =
        ros::SubscribeOptions::create<wheel_control::wheelSpeed>(
            "wheelSpeedTopic",
            1,
            boost::bind(&RoverPlugin::OnRosMsg, this, _1),
            ros::VoidPtr(), &this->rosQueue);
    this->rosSub = this->rosNode->subscribe(so);
*/

    this->rosSub = this->rosNode->subscribe<wheel_control::wheelSpeed>("wheelSpeedTopic", 1, &RoverPlugin::OnRosMsg, this);
    this->testPub = this->rosNode->advertise<wheel_control::wheelSpeed>("test", 1);

    ROS_INFO("subbe");
    // Spin up the queue helper thread.
    this->rosQueueThread =
        std::thread(std::bind(&RoverPlugin::QueueThread, this));

    this->model->GetJointController()->SetVelocityTarget(this->joint2->GetScopedName(), motorSpeed[2]);
    this->model->GetJointController()->SetVelocityTarget(this->joint1->GetScopedName(), motorSpeed[1]);
    this->model->GetJointController()->SetVelocityTarget(this->joint0->GetScopedName(), motorSpeed[0]);
    this->model->GetJointController()->SetVelocityTarget(this->joint3->GetScopedName(), motorSpeed[3]);
    ROS_INFO("speedet");
  }

public:
  void OnUpdate()
  {
    ROS_INFO("UPPPPP");
  }

  /// \brief Handle an incoming message from ROS
  /// \param[in] _msg A float value that is used to set the velocity
  /// of the Velodyne.
public:
  void OnRosMsg(const wheel_control::wheelSpeed msg)
  {
    ROS_INFO(" old %f left     %f right", setPoints[0], setPoints[1]);
    setPoints[0] = msg.left;  //*(float)maxSpeed;
    setPoints[1] = msg.right; //*(float)maxSpeed;
    motorSpeed[0] = setPoints[0] * 25;
    motorSpeed[1] = setPoints[0] * 25;
    motorSpeed[2] = setPoints[1] * 25;
    motorSpeed[3] = setPoints[1] * 25;
    ROS_INFO("%f left     %f right", setPoints[0], setPoints[1]);
    this->model->GetJointController()->SetVelocityTarget(this->joint2->GetScopedName(), motorSpeed[2]);
    this->model->GetJointController()->SetVelocityTarget(this->joint1->GetScopedName(), motorSpeed[1]);
    this->model->GetJointController()->SetVelocityTarget(this->joint0->GetScopedName(), motorSpeed[0]);
    this->model->GetJointController()->SetVelocityTarget(this->joint3->GetScopedName(), motorSpeed[3]);
  }

  /// \brief ROS helper function that processes messages
private:
  void QueueThread()
  {
    ROS_INFO("ques");
    static const double timeout = 0.01;
    while (this->rosNode->ok())
    {
      wheel_control::wheelSpeed msg;
      msg.left = 1;
      msg.right = 1;
      msg.wheelMode = 0;
      testPub.publish(msg);
      ros::Rate loop_rate(10);
      ros::spinOnce();
      //this->rosQueue.callAvailable(ros::WallDuration(timeout));
    }
  }
};
GZ_REGISTER_MODEL_PLUGIN(RoverPlugin)
} // namespace gazebo
#endif