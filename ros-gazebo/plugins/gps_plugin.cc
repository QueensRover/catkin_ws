#include "gps_plugin.hh"
#include "geometry_msgs/Point.h"
#include <gazebo/physics/physics.hh>
using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(GpsPlugin)

GpsPlugin::GpsPlugin() {}

void GpsPlugin::Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf) {



    link = _model->GetLink();
    link_name_ = _model->GetName();

    topic = "/fix/metres";
    headingTopic = "/heading";
    int argc = 0;
    char ** argv = NULL;
    ros::init(argc, argv, "gazebo_position");
    this->posPub = this->nodeHandle.advertise<geometry_msgs::Point>(topic, 1);
    this->headingPub = this->nodeHandle.advertise<std_msgs::Float32>(headingTopic, 1);
    this->rosQueueThread = std::thread(std::bind(&GpsPlugin::QueueThread, this));

}

void GpsPlugin::QueueThread() {
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        ignition::math::Pose3d pose = link->WorldPose();
        geometry_msgs::Point msg;
        msg.x = pose.Pos().X();
        msg.y = pose.Pos().Y();
        msg.z = pose.Pos().Z();
        std_msgs::Float32 headingMsg;
        headingMsg.data = pose.Rot().Z() * 3.141592653 ;
        headingPub.publish(headingMsg);
        posPub.publish(msg);
        loop_rate.sleep();
    }
}
