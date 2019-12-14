cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})

find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
#find_package(sensors REQUIRED)

include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS}) 
include_directories(${sensor_msgs_INCLUDE_DIRS})
include_directories(${message_generation_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Build our plugin
add_library(rover_plugin SHARED rover_plugin.cc)
target_link_libraries(rover_plugin ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
add_library(leddar_plugin SHARED leddar_plugin.cc)
target_link_libraries(leddar_plugin ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
add_library(ultrasonic_plugin SHARED ultrasonic_plugin.cpp)
target_link_libraries(ultrasonic_plugin ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
add_library(gps_plugin SHARED gps_plugin.cc)
target_link_libraries(gps_plugin     ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
