#
# Author: Jakob Engel <jajuengel@gmail.com>
# Contributor: Stefan Wilkes <stefan.wilkes@gmail.com>
#
cmake_minimum_required(VERSION 2.8.3)
project(aurora_core)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  mavros
  mavros_msgs
  sensor_msgs
)


#include_directories(${catkin_INCLUDE_DIRS})
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES vision_opencv
#  CATKIN_DEPENDS cv_bridge image roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)
# ---------------------------- GUI --------------------------------------------------
# set header ans source files
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(GUI_SOURCE_FILES         
	src/main.cpp    
	src/SharedMemory.cpp  
	src/SubscribeMavrosState.cpp
        src/MavRosSetStreamRate.cpp 
	src/Library.cpp
	src/Core.cpp
	src/CoreStarter.cpp
	src/UserInterface.cpp
	src/WorldModel.cpp
	src/UICmdParser.cpp
	src/UICmdResponse.cpp
	src/Behaviours.cpp
	src/WayPoint.cpp
	src/Geometry.cpp
	src/MavrosGlobalPosition.cpp
	src/Autopilot.cpp
)

set(GUI_HEADER_FILES         
	src/SharedMemory.h  
	src/SubscribeMavrosState.h
	src/MavRosSetStreamRate.h
	src/Library.h
	src/Core.h
	src/CoreStarter.h
	src/UserInterface.h
	src/WorldModel.h
	src/UICmdParser.h
	src/UICmdResponse.h
	src/Behaviours.h
	src/WayPoint.h
	src/Geometry.h
	src/MavrosGlobalPosition.h
	src/Autopilot.h
)


# *.qrc
set(GUI_RESOURCE_FILES        
)

# do QT stuff
ADD_DEFINITIONS( -Wall )
find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml REQUIRED )
include(${QT_USE_FILE})
QT4_ADD_RESOURCES(GUI_RESOURCE_FILES_CPP ${GUI_RESOURCE_FILES})
QT4_WRAP_CPP(GUI_HEADER_FILES_HPP ${GUI_HEADER_FILES})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${catkin_INCLUDE_DIRS})

# build!
add_executable(aurora_core ${GUI_SOURCE_FILES} ${GUI_RESOURCE_FILES_CPP} ${GUI_HEADER_FILES_HPP})
target_link_libraries(aurora_core ${catkin_LIBRARIES} ${QT_LIBRARIES} ${ROS_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies(aurora_core ${PROJECT_NAME}_gencpp)

