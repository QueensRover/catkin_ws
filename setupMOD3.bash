sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update
sudo apt-get install ros-melodic-desktop-full
sudo rosdep init
rosdep update
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get install python-catkin-tools
source /opt/ros/melodic/setup.bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin init
source devel/setup.bash
cd ~/catkin_ws/src
git config --global credential.helper store
git clone https://gitlab.com/qset_rover/ros-gazebo.git
git clone https://gitlab.com/qset_rover/gazebo-launch
git clone https://gitlab.com/qset_rover/ros-tf-transforms 
cd ros-tf-transforms git checkout ubuntuCompliant
cd ~/catkin_ws/src
git clone https://gitlab.com/qset_rover/gazebo_plugins
git clone https://gitlab.com/qset_rover/wheel-control
git clone git@gitlab.com:qset_rover/phidgets_drivers.git
cd ~/catkin_ws
catkin build owen_launch hector_gazebo_plugins wheel_control tf_transforms 
cp ~/catkin_ws/src/ros-gazebo/plugins/build/*.so ~/catkin_ws/devel/lib
sudo echo "export GAZEBO_PLUGIN_PATH=~/catkin_ws/devel/lib" >> ~/.bashrc
source ~/catkin_ws/devel/setup.bash