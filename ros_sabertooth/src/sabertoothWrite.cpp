#include "ros/ros.h"
#include "serialWriter.h"
#include "sabertooth/sabertooth.h"

using namespace std;

serialWriter writer;
uint16_t adr;
uint16_t cmd;
uint16_t data;

void callBack(const sabertooth::sabertooth msg) {
	ROS_INFO("Address: [%d], command: [%d], data: [%d]\n", msg.address, msg.command, msg.data);
	adr = msg.address;
	cmd = msg.command;
 	data = msg.data;
	//writer.serialWrite(address, command, data);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "sabertooth");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("sabertooth", 4, callBack);
	ros::Rate loop = 80;
	while(ros::ok()){
		ros::spinOnce();
		writer.serialWrite(adr, cmd, data);
		loop.sleep();
	}

	//iros::spin();

}//main
