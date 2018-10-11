# Aurora - Core

Core program of autonomous multi rotor robots based on [APM autopilot][apm].We use [ROS platform][ros] and [Mavlink protocol][mavlink-wiki] for connection between program and robot.
A multirotor or multicopter is a rotorcraft with more than two rotors. An advantage of multirotor aircraft is the simpler rotor mechanics required for flight control. 
We designed, optimized and manufactured hexacopter drone with a [vision based][aurora_vision] AI and [online 3D mapping][aurora_copter] using the C++ programming language on [ROS platform][ros].

-------------------

### Installation Requirements

| Requirement | Tested Successfully On |
| ------ | ------ |
| OS| [Ubuntu 14.04](http://cdimage.ubuntu.com/netboot/14.04/?_ga=2.72803859.1606487436.1539181592-1947134802.1539181592)|
| ROS | [ROS indigo][ros-indigo]|
| Flight Control| [Ardupilot Mega (APM) 2.8][apm]|
| Ground Control Station Communication|[MAVROS][mavros], [wiki][mavros-wiki]|
| Auto Pilot Communication| [Mavlink][mavlink], [wiki][mavlink-wiki]|

----------

## Software
The software section divides into: 

| Application | Link |
| ------ | ------ |
| Core | [https://github.com/erfanjazebnikoo/aurora_core][aurora_core]|
| GUI|[https://github.com/erfanjazebnikoo/aurora_gui][aurora_gui] |
| Vision|[https://github.com/SajjadRahnama/aurora_vision] |
| Mapping|[https://github.com/SajjadRahnama/aurora_copter][aurora_copter] |

[GUI][aurora_gui] is responsible for receiving inputs from the drone and controlling it, [Core][aurora_core] responsibility is to receive inputs from [GUI][aurora_gui], analyze data and provide proper outputs for the drone, and [The Mapping application][aurora_copter] is responsible for making 3D maps from coordinates and aerial images.
In this project C++ programming language, [OpenCV][opencv] and [QT][qt] libraries are applied. [QT5][qt] libraries and ROS packages along with other libraries respectively used in all applications.

![N|Solid](http://erfanjazebnikoo.com/downloads/aurora-core-gui.jpg)

### 1- Artificial intelligence architecture
In the high-level control system, A suitable structure was designed by Guilano panel for multi-agent decision making. The structure uses concepts, world model, skills, behavior, and communications to make more intelligent decisions. Some intelligent behavioral algorithm including state-based decision were implemented by the panel to make the right decision during a mission, shape position estimation and flying above a shape by using image processing data.
This section includes three main units: planning unit, executing unit and knowledge unit. The major task of the knowledge unit is to collect sensory and vision output data, analyze and convert them to meaningful data which are the inputs of decision making sections. 
The planning unit main task is to make high-level intelligent decisions (commands) like mission decision maker, releasing Lifebuoy on the victim and so forth. It, furthermore, orchestrates them with other teammate decisions in the multi-agent situation.This part is also allocated to the general playing strategies of the team according to mission states and then sends the appropriate commands to executing unit. 
In the executing unit, the commands are analyzed to set the main skills. The skills are basic behaviors like take-off, Land, Change mode, and arm/disarm the robot.

[![N|Solid](http://erfanjazebnikoo.com/downloads/aurora-core-flowchart-lq.jpg)](http://erfanjazebnikoo.com/downloads/aurora-core-flowchart.jpg)

### 2- ROS
[Robots Operating System (ROS)][ros] is a set of software frameworks for software development of robots. A set of tools, libraries, and conventions in order to simplify complex behavior of the robot as a powerful robotic platform. [ROS Indigo version][ros-indigo] is used in this project. [ROS][ros] package is generally included in mapping, navigation, object and face recognition, and also movement detection. [ROS][ros] is deployed by Guilano team, for controlling and intelligent behavior of the robot.

### 3- Communications
UDP protocol is applied by our team in order to form a link between Core and [GUI][aurora_gui]. Guilano team applies the example of using UDP protocol, the coordinates obtained by [GUI][aurora_gui] convert to an XML file and send on UDP port while Core is waiting for a data in this port.
[MAVLink][mavlink-wiki] is a communication protocol between Flight Control (FC) and Ground Control Station (GCS) which provides the capability to control robot for the user by sending message packets to FC. [MAVLink][mavlink-wiki] is a very compact library in order to manage messages for micro air vehicles. It can pack C-struck by high functionality serial channels and send them to GCS. This protocol can be used as a communication link in APM, Pixhawk and PX4 platforms. [MAVLink][mavlink-wiki] has been being used in this project as a communication protocol between drone and GCS since we have used Pixhawk in this project.
[Mavros][mavros-wiki] is a communication library between FC and [ROS][ros] system that can receive FC data to be used in Core. In addition, [Mavros][mavros-wiki] is able to connect to the robot and control it with the help of telemetry (for instance, changing flight modes, controlling servo motors, controlling robot movements).

### 4- Mapping
One of the missions of the competition is mapping along with trajectory. To conduct this mission, open source codes are used and changed to satisfy the competition necessities. To run this system, only one camera is needed to be installed under the robot (the camera faces down). The rviz package which is to show ROS  output systems was applied to demonstrate output data. Rviz includes robot movement directions, the map obtained from camera and objects from image processing.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_3d_mapping.jpg)

### 5- Simulator
A simulator is a tool for testing software and simulation of competition environment. Gazebo is a simulation framework which works alongside [ROS][ros] here and illustrates the outputs.
A simulator can work with the sensors such as laser scanner, sonar, parachute and so forth, which are not available just how a real robot does.To find the strengths and weaknesses of the program, it can be tested in a simulated environment for several times.

----------

## Image Processing
Detecting objects is accurately one of the missions of the competition. [OpenCV][opencv] libraries are made use of in order to detect objects. In the previous projects, we managed to detect shapes like circle, square, triangle, pentagon, star and so forth. More complex shapes and colors are needed to train for [OpenCV][opencv]. In the last competition, the team trained the required shapes, for instance, heart and landing sign, to land by providing images from different angles and training them by [OpenCV][opencv] libraries. This time-consuming process results in an XML file which is used to detect the target shape.
In addition, we used canny, filtering and rough circle algorithms from [OpenCV][opencv] libraries to detect simple colored shapes. Another point to mention is that the image processing program works with [ROS][ros]. In this method, the image is provided by the topics specified for sending image data. It is beneficial because the main program is separated from the image processing program. The main program is responsible for controlling the robot. If any issues occur in the image processing program, the main application works without any problems.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_image_processing.jpg)

----------

# Guilano 

Guilano team has committed to working on research and development of multicopter robots since 2010 at Professor Hesabi robotic research laboratory of Islamic Azad University of Lahijan Branch. Some of the team achievements are creating quadrotors, hexacopters, bi-fuel drones in different sizes, applications, as well as winning various awards in competitions and exhibitions. Guilano team took part in the indoor league of Iran Open and ranked 4 in the year 2013. It ranked 5 in the outdoor league of Iran open 2017 as well. Guilano team was, indeed, the best technical team of the 2017 Iran open competition.The team goals have changed to making intelligent robots by image processing, improving AI  and fundamental research in electronics since 2013. Thus, we have focused on research and development of hardware and software to improve the functionality of robots. The DIY RC radio controller and telemetry, creating an emergency controller, antenna tracker, developing mapping algorithms and the intelligent making of robot behaviors are some instance of the recent projects
In this year, Guilano team is willing to create sophisticated robots. Hence, it needs to be experiencing major changes in hardware and software design in order to participate in the outdoor league. Different flight modes have been simulated, tested and implemented according to the competition rules.Therefore, optimized details for body design was obtained to build a hexacopter robot. Electronic circuits designed were due to sensors and essential capabilities. Robot movement controllers were added to subordinate software layers.The noted Software is divided into two major sections. These sections are object detection based on image processing and Artificial Intelligence (AI) so as to develop proper behavior in different situations. In this paper, we explain algorithms and design details completely and clearly.

**Team Leader:**
 - [Erfan Jazeb Nikoo](mailto:erfan.jazebnikoo@gmail.com)

**Hardware Team Member:**
 - [Amir Abkhoshk](mailto:amirabkhoshk@gmail.com)
 - [Babak Moradi](mailto:Babak.elecrobo@gmail.com)

**Software Team Member:**
 - [Sajjad Rahnama](mailto:sajjadmuscle@gmail.com)
 - [Navid Hadipour Limouei](mailto:navid.hadipour.le@gmail.com)
 
 ### Youtube: 
 
 [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/wumIN9yP0dw/0.jpg)](https://www.youtube.com/watch?v=wumIN9yP0dw)

----------

## Robot Control Architecture

The control system overview is presented in Figure. The [Pixhawk flight controller][pixhawk] is used for low-level control like controlling the angular rotations, setting motor outputs and also providing raw data used by the higher level estimation and control. The IMU  and sonar data is fused by using a nonlinear filter (unscented Kalman filter) and the estimates are supplied to the controllers that control the vertical and horizontal position of the hexacopter by sending altitude and throttle set points back to the pixhawk autopilot.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_system_overview.png)

[PID][pid] control is explained in and is one of the most fundamental types of control and also the most frequently implemented in industry. The great strengths of the [PID controller][pid] are its simple structure and low requirements on the system model. Pixhawk used the [PID controller][pid] to take control of the stability of the robot. Furthermore, a specific ratio is evaluated by the stated equipment for every direction of movement of the aerial robot. The method of this controller functionality is described below

![N|Solid](http://erfanjazebnikoo.com/downloads/Quala-PID-Pathfinder-PID.png)

Guilano robot is controlled in the manual and autonomous mode that is described in this document.

----------

## Hardware and mechanical features

A multirotor design and configuration are dependent on many parameters such as take-off, weight, endurance, wind gust resistance, payload, which are selected based on the consumption of the robot. The consumption may vary for various purposes such as aerial photography, FPV , security, and so forth.The aforementioned multirotor is optimized for 30minutes of flight with the 1kg payload attached in a 30km/h wind speed. In addition, Tiger antigravity brushless motors and 9 Inch propellers are used in the Guilano multirotor.

[![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_hexacopter_lq.jpg)](http://erfanjazebnikoo.com/downloads/guilano_hexacopter.jpg)

### 1- Electronics
After years of research, we obtained the fundamental and necessary factors for proper method to implement and use the equipment. This robot has different dimensions which numerous creativity and innovations can be seen in most of them.

#### 1.	Flight Controller
Pixhawk is an open-source hardware project aiming to provide high-end autopilot hardware. Pixhawk is an advanced autopilot which is developed by DIY Drones. It has a powerful processor by 168 MHz Cortex M4F CPU (256 KB RAM, 2 MB Flash), advanced sensors (3D accelerometer, gyroscope sensor, magnetometer, barometer) and NuttX real-time operating system. 
The emergency controller board in the broached robot is capable of giving a related function to robot needs in according to different situations by various sensors used in the robot and complete intelligent experience in both autonomous and manual modes. This helps an autonomous system to provide control for a robot which decreases the robot unwanted behaviors even in bad weather conditions or when the connection is lost. This board can be connected directly to the computer.

![N|Solid](http://erfanjazebnikoo.com/downloads/pixhawk.jpg)

#### 2.	Components and modules
The components used in the above-mentioned robot are [external GPS][gps], [Air Gear 350 brushless motors and speed controllers][motors], emergency controller board and power supply circuit. Some components made by the panel are RC radio, emergency controller board, and power supply circuit.

#### 3.	Telemetry and RC Radio
While The DIY Guilano RC radio and telemetry system are based on [RFM23Bp][RFM23Bp] and ATmega328 microcontroller hardware which can use large UHF Band, The team have made use of the ISM  frequency of (433.05 -434.79 MHz).It can send telemetry data and standard PPM signals through eight channels. In other words, we don’t necessarily use the separate telemetry and RC radio. 
The advantage of using our design is to avoid using two radio links on different frequencies, and also works fine along with numerous interferences with sensitive electronic equipment, namely GPS, magnetometer, servo motors, camera, gimbal, and so forth.
This system is based on the opensource of the [openLRSng project][openLRSng] and modified for more bandwidth, Baud Rate, Binding code, 5 channel selectable frequency hopping, RSSI  Providing, Failsafe and reduction of the output RF power for local legislation. The following pictures show the PCB  Design and radio used on the Robot.

![Solid](http://erfanjazebnikoo.com/downloads/guilano_ppm_transmitter.jpg) 
![Solid](http://erfanjazebnikoo.com/downloads/guilano_ppm_receiver.jpg)
![Solid](http://erfanjazebnikoo.com/downloads/guilano_ppm_schematic.jpg)


The latest version of this radio can send 8 channel PPM signals and data on 57600 air baud rate.The RFM 23Bp provides the digital RSSI value for the firmware to convert to PWM  output signal. These signals are received by the microcontroller which integrates the signals with each other and converts them to an analog voltage in order to be used by ADC  converter. This is the most important feedback for using the robot in radio range. The Two pieces of firmware for transmitter and receiver are written and loaded to the ground station and the robot board.

#### 4.	HD video Stream
The [Raspberry Pi 3][rbpi3] and a 5-megapixel camera providing HD video are used in Guilano projects. The raspberry is beneficial because of the H264 encoder hardware which results in a very low latency about 70 ms which is very appropriate for the real-time image processing and navigation AI software.
The video streams sent to the ground station by UDP network are a port through the Gstreamer. The open source software is installed on both the raspberry pi and the ground station Linux machine. We used a 0.6 W 2.4MHz Amplifier with a high gain antenna on both the ground station and the robot, for the medium range (about 1000 meters). Moreover, all the local legislation concerning the RF restrictions was taken into consideration in the project.

![Solid](http://erfanjazebnikoo.com/downloads/raspberry_pi.jpg)

#### 5.	Battery
The Battery depends on the main purpose and ideas to design the copter. For a particular instance, the best option for mini and micro size batteries is two or three cells of Li-Po  battery that would help to diminish the size and weight, but increase the current consumption as a result of low voltage.
The battery used in this robot is Li-Po, Tattu Gens Ace 10000mAh 25C 4 Cell, which is specifically designed for multi-rotor robots. These batteries provide high current to fly at high speed in any direction and high endurance for about 30 minutes. The mentioned batteries are made by vibrant resistant and fire retardant materials, then they can be used in various conditions. Low weight and vast capacity are two brilliant features of these batteries.

![Solid](http://erfanjazebnikoo.com/downloads/battery.jpg)


### 2-	Mechanics
The frame of the mentioned hexacopter is star-shaped and made by wooden material for the central plates. Its arms are made of aluminum alloy.

#### 1.	Chassis and body

This robot is a hexacopter which is made of six arms and propellers. The largest size of the robot is 77 cm. The arms are made of aluminum alloy which is common in aerial industries because this alloy has low weight and density as well as satisfactory solidity.
The appearance of upper and lower chassis is circular. The diameter is 180 mm with the thickness of 5mm. The chassis is made of wood. The upper chassis used to place main board, speed controllers, besides attaching arms. The lower chassis is used to place batteries, landing gear and arms. Furthermore, this robot uses an H-shaped landing gear that is used for more stability and safety in landing.

[![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_solidwork_1_lq.jpg)](http://erfanjazebnikoo.com/downloads/guilano_solidwork_1.jpg)
[![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_solidwork_2_lq.jpg)](http://erfanjazebnikoo.com/downloads/guilano_solidwork_2.jpg)


#### 2.	Driving mechanism

This robot is powered by 6.920KV Air Gear 350 tiger brushless motors with an 800g thrust that uses 9*4.5 inch propellers along with 4 cell Li-Po battery. As a result, the total thrust of the copter is about 4500g that is used to neutralize the weight of the hexacopter and the unwanted drifting. Hexarotor releases more driving force and stability in the sky. The total weight of the robot is approximately 1.5kg to benefit from more strength and speed.
When the robot is expected to turn right or left, it goes to the direction by increasing more torque in opposite motors.

![N|Solid](http://erfanjazebnikoo.com/downloads/guilano_motors_blades.jpg)

-----------------

## Support

- [Erfan Jazeb Nikoo](mailto:erfan.jazebnikoo@gmail.com)
- [Sajjad Rahnama](mailto:sajjadmuscle@gmail.com)

[pixhawk]:<https://docs.px4.io/en/flight_controller/pixhawk4.html>
[mavros]:<https://dev.px4.io/ros-mavros-installation.html>
[mavros-wiki]:<http://wiki.ros.org/mavros>
[mavlink]:<http://qgroundcontrol.org/mavlink/>
[mavlink-wiki]:<http://wiki.ros.org/mavlink>
[ros]:<http://www.ros.org/core-components/>
[ros-indigo]:<http://wiki.ros.org/indigo/Installation/Ubuntu>
[pid]:<https://en.wikipedia.org/wiki/PID_controller>
[gps]:<https://www.u-blox.com/en/product/neo-m8-series>
[motors]:<http://store-en.tmotor.com/>
[RFM23Bp]:<http://www.hoperf.com/upload/rf/RFM23BP.pdf>
[openLRSng]:<https://openlrsng.org/>
[rbpi3]:<https://www.raspberrypi.org/products/raspberry-pi-3-model-b/>
[opencv]:<https://opencv.org/>
[qt]:<https://www.qt.io/>
[aurora_gui]:<https://github.com/erfanjazebnikoo/aurora_gui>
[aurora_core]:<https://github.com/erfanjazebnikoo/aurora_core>
[aurora_copter]:<https://github.com/SajjadRahnama/aurora_copter>
[aurora_Vision]:<https://github.com/SajjadRahnama/aurora_vision>
[apm]:<http://www.ardupilot.co.uk/>

