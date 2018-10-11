# Aurora core

Core program of autonomous multi rotor robots based on APM autopilot.We use ROS platform and Mavlink protocol for connection between program and robot.
A multirotor or multicopter is a rotorcraft with more than two rotors. An advantage of multirotor aircraft is the simpler rotor mechanics required for flight control. 
We designed, optimized and manufactured hexacopter drone with a vision based AI and online 3D mapping using the C++ programming language on ROS platform.

-------------------

### Installation Requirements

| Requirement | Tested Successfully On | 
| ------ | ------ |
| OS| [Ubuntu 14.04](http://cdimage.ubuntu.com/netboot/14.04/?_ga=2.72803859.1606487436.1539181592-1947134802.1539181592)|
| ROS | [ROS indigo](http://wiki.ros.org/indigo/Installation/Ubuntu) |
| Flight Control| [Pixhawk 4][pixhawk]|
| Ground Control Station Communication|[MAVROS][mavros], [wiki][mavros-wiki]|
| Auto Pilot Communication| [Mavlink][mavlink], [wiki][mavlink-wiki]|

----------

## Software
The software section divides into Core, Mapping and GUI  applications. GUI is responsible for receiving inputs from the drone and controlling it, Core responsibility is to receive inputs from GUI, analyze data and provide proper outputs for the drone, and The Mapping application is responsible for making 3D maps from coordinates and aerial images.
In this project C++ programming language, OpenCV and QT libraries are applied. QT5 libraries and ROS packages along with other libraries respectively used in all applications.

![N|Solid](http://erfanjazebnikoo.com/downloads/aurora-core.jpg)

### 1- Artificial intelligence architecture
In the high-level control system, A suitable structure was designed by Guilano panel for multi-agent decision making. The structure uses concepts, world model, skills, behavior, and communications to make more intelligent decisions. Some intelligent behavioral algorithm including state-based decision were implemented by the panel to make the right decision during a mission, shape position estimation and flying above a shape by using image processing data.
This section includes three main units: planning unit, executing unit and knowledge unit. The major task of the knowledge unit is to collect sensory and vision output data, analyze and convert them to meaningful data which are the inputs of decision making sections. 
The planning unit main task is to make high-level intelligent decisions (commands) like mission decision maker, releasing Lifebuoy on the victim and so forth. It, furthermore, orchestrates them with other teammate decisions in the multi-agent situation.This part is also allocated to the general playing strategies of the team according to mission states and then sends the appropriate commands to executing unit. 
In the executing unit, the commands are analyzed to set the main skills. The skills are basic behaviors like take-off, Land, Change mode, and arm/disarm the robot.

[![N|Solid](http://erfanjazebnikoo.com/downloads/aurora-core-flowchart-lq.jpg)](http://erfanjazebnikoo.com/downloads/aurora-core-flowchart.jpg)

### 2- ROS
[Robots Operating System (ROS)][ros] is a set of software frameworks for software development of robots. A set of tools, libraries, and conventions in order to simplify complex behavior of the robot as a powerful robotic platform. ROS Indigo version is used in this project. ROS package is generally included in mapping, navigation, object and face recognition, and also movement detection. ROS is deployed by Guilano team, for controlling and intelligent behavior of the robot.

### 3- Communications
UDP protocol is applied by our team in order to form a link between Core and GUI. Guilano team applies the example of using UDP protocol, the coordinates obtained by GUI convert to an XML file and send on UDP port while Core is waiting for a data in this port.
[MAVLink][mavlink-wiki] is a communication protocol between Flight Control (FC) and Ground Control Station (GCS) which provides the capability to control robot for the user by sending message packets to FC. MAVLink is a very compact library in order to manage messages for micro air vehicles. It can pack C-struck by high functionality serial channels and send them to GCS. This protocol can be used as a communication link in APM, Pixhawk and PX4 platforms. MAVLink has been being used in this project as a communication protocol between drone and GCS since we have used Pixhawk in this project.
[Mavros][mavros-wiki] is a communication library between FC and ROS system that can receive FC data to be used in Core. In addition, Mavros is able to connect to the robot and control it with the help of telemetry (for instance, changing flight modes, controlling servo motors, controlling robot movements).

### 4- Mapping
One of the missions of the competition is mapping along with trajectory. To conduct this mission, open source codes are used and changed to satisfy the competition necessities. To run this system, only one camera is needed to be installed under the robot (the camera faces down). The rviz package which is to show ROS  output systems was applied to demonstrate output data. Rviz includes robot movement directions, the map obtained from camera and objects from image processing.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_3d_mapping.jpg)

### 5- Simulator
A simulator is a tool for testing software and simulation of competition environment. Gazebo is a simulation framework which works alongside ROS here and illustrates the outputs.
A simulator can work with the sensors such as laser scanner, sonar, parachute and so forth, which are not available just how a real robot does.To find the strengths and weaknesses of the program, it can be tested in a simulated environment for several times.

----------

## Image Processing
Detecting objects is accurately one of the missions of the competition. [OpenCV](https://opencv.org/) libraries are made use of in order to detect objects. In the previous projects, we managed to detect shapes like circle, square, triangle, pentagon, star and so forth. More complex shapes and colors are needed to train for OpenCV. In the last competition, the team trained the required shapes, for instance, heart and landing sign, to land by providing images from different angles and training them by OpenCV libraries. This time-consuming process results in an XML file which is used to detect the target shape.
In addition, we used canny, filtering and rough circle algorithms from OpenCV libraries to detect simple colored shapes. Another point to mention is that the image processing program works with ROS. In this method, the image is provided by the topics specified for sending image data. It is beneficial because the main program is separated from the image processing program. The main program is responsible for controlling the robot. If any issues occur in the image processing program, the main application works without any problems.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_image_processing.jpg)

----------

## Robot Control Architecture

The control system overview is presented in Figure. The [Pixhawk flight controller][pixhawk] is used for low-level control like controlling the angular rotations, setting motor outputs and also providing raw data used by the higher level estimation and control. The IMU  and sonar data is fused by using a nonlinear filter (unscented Kalman filter) and the estimates are supplied to the controllers that control the vertical and horizontal position of the hexacopter by sending altitude and throttle set points back to the pixhawk autopilot.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_system_overview.png)

[PID][pid] control is explained in and is one of the most fundamental types of control and also the most frequently implemented in industry. The great strengths of the PID controller are its simple structure and low requirements on the system model. Pixhawk used the PID controller to take control of the stability of the robot. Furthermore, a specific ratio is evaluated by the stated equipment for every direction of movement of the aerial robot. The method of this controller functionality is described below

![N|Solid](http://erfanjazebnikoo.com/downloads/Quala-PID-Pathfinder-PID.png)

Guilano robot is controlled in the manual and autonomous mode that is described in this document.

----------

### Youtube: 

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/wumIN9yP0dw/0.jpg)](https://www.youtube.com/watch?v=wumIN9yP0dw)

-----------------

## Support

Please ask your questions on:

- erfan.jazebnikoo@gmail.com
- sajjadmuscle@gmail.com

[pixhawk]:<https://docs.px4.io/en/flight_controller/pixhawk4.html>
[mavros]:<https://dev.px4.io/ros-mavros-installation.html>
[mavros-wiki]:<http://wiki.ros.org/mavros>
[mavlink]:<http://qgroundcontrol.org/mavlink/>
[mavlink-wiki]:<http://wiki.ros.org/mavlink>
[ros]:<http://www.ros.org/core-components/>
[pid]:<https://en.wikipedia.org/wiki/PID_controller>
