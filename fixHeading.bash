cp ~/unified-launch/gazebo-launch/worlds/world_with_rover.world ~/catkin_ws/src/gazebo-launch/worlds/
cp ~/unified-launch/gazebo_plugins/hector_gazebo_plugins/src/gazebo_ros_magnetic.cpp ~/catkin_ws/src/gazebo_plugins/hector_gazebo_plugins/src/
cd ~/catkin_ws
catkin_make
echo "Finished running script"