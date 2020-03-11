rm ~/catkin_ws/devel/libhector*
cp ~/unified-launch/ros-gazebo/plugins/gps_plugin.* ~/catkin_ws/src/ros-gazebo/plugins/
cd ~/catkin_ws/src/ros-gazebo/plugins/build
cmake ..
make
cp ~/catkin_ws/src/ros-gazebo/plugins/build/*.so ~/catkin_ws/devel/lib/
echo "Finished running script"
