#! /bin/bash
sudo apt install x11-apps
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get install -y ros-melodic-desktop-full
sudo apt-get install -y python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo rosdep init
rosdep update
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get -y install python-catkin-tools

source /opt/ros/melodic/setup.bash
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
cd ~/catkin_ws
rosdep install --from-paths src --ignore-src -r -y
cd ~/catkin_ws/src/unified-launch
source ~/.bashrc
cd ~/catkin_ws/
rm -r .catkin_tools
rm -r build
rm -r devel
rm -r logs
rm .catkin_workspace
catkin init
catkin clean -y
catkin build 
echo "export GAZEBO_PLUGIN_PATH=~/catkin_ws/devel/lib" >> ~/.bashrc


