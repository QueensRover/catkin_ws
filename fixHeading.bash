sudo -s
cp ~/unified-launch/gazebo-launch/worlds/world_with_rover.launch ~/catkin_ws/src/gazebo-launch/worlds/
cp ~/unified-launch/gazebo_plugins/hector_gazebo_plugins/src/gazebo_ros_magnetic.cpp ~/catkin_ws/src/gazebo_plugins/hector_gazebo_plugins/src/
cd catkin_ws
catkin build hector_gazebo_plugins