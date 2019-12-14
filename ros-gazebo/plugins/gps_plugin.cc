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

    int argc = 0;
    char ** argv = NULL;
    ros::init(argc, argv, "gazebo_position");
    this->posPub = this->nodeHandle.advertise<geometry_msgs::Point>(topic, 1);
    this->rosQueueThread = std::thread(std::bind(&GpsPlugin::QueueThread, this));

}

void GpsPlugin::QueueThread() {
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        math::Pose pose = link->GetWorldPose();
        geometry_msgs::Point msg;
        msg.x = pose.pos.x;
        msg.y = pose.pos.y;
        msg.z = pose.pos.z;

        posPub.publish(msg);
        loop_rate.sleep();
    }
}
