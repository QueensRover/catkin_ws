sudo apt install x11-apps
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full
sudo rosdep init
rosdep update
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get install python-catkin-tools
source /opt/ros/kinetic/setup.bash
source ~/.bashrc
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
source devel/setup.bash
sudo echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
cd ~/catkin_ws/src
git config --global credential.helper store
git clone https://gitlab.com/qset_rover/ros-gazebo.git
git clone https://gitlab.com/qset_rover/gazebo-launch
git clone https://gitlab.com/qset_rover/ros-tf-transforms 
cd ros-tf-transforms 
git checkout ubuntuCompliant
cd ~/catkin_ws/src
git clone https://gitlab.com/qset_rover/gazebo_plugins
cd gazebo_plugins
git checkout forWindows
cd ~/catkin_ws/src
git clone https://gitlab.com/qset_rover/wheel-control
git clone https://gitlab.com/qset_rover/phidgets_drivers.git
git clone https://gitlab.com/qset_rover/ros_sabertooth
cd ~/catkin_ws
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get install ros-kinetic-gazebo9-*
source /usr/share/gazebo/setup.sh
cd ~/catkin_ws/src/ros-gazebo/plugins/build
cmake ..
make
cp ~/catkin_ws/src/ros-gazebo/plugins/build/*.so ~/catkin_ws/devel/lib
cd ~/catkin_ws/
catkin init
catkin build owen_launch hector_gazebo_plugins wheel_control tf_transforms 
sudo cp -r ~/catkin_ws/src/ros-gazebo/rover_real_model /usr/share/gazebo-9/models/
sudo echo "export GAZEBO_PLUGIN_PATH=~/catkin_ws/devel/lib" >> ~/.bashrc
sudo echo "export DISPLAY=:0" >> ~/.bashrc


