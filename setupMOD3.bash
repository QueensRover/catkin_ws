sudo apt install x11-apps
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get install -y ros-melodic-desktop-full
sudo rosdep init
rosdep update
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get -y install python-catkin-tools

source /opt/ros/melodic/setup.bash
source ~/.bashrc
cd ~/catkin_ws/
catkin_make
source devel/setup.bash
sudo echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
cd ~/catkin_ws/src/unified-launch
sudo rm -r ./.git
source /usr/share/gazebo/setup.sh
cd ~/catkin_ws/
catkin init
catkin clean -y
catkin build owen_launch hector_gazebo_plugins wheel_control tf_transforms 
cd ~/catkin_ws/src/ros-gazebo/plugins/build
sudo rm ./CMake*
sudo cmake ..
sudo make
cp ~/catkin_ws/src/ros-gazebo/plugins/build/*.so ~/catkin_ws/devel/lib
sudo cp -r ~/catkin_ws/src/ros-gazebo/rover_real_model /usr/share/gazebo-9/models/
echo "export GAZEBO_PLUGIN_PATH=~/catkin_ws/devel/lib" >> ~/.bashrc
echo "export DISPLAY=:0" >> ~/.bashrc


