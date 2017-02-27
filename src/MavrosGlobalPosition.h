/*
 * MavrosGlobalPosition.h
 *
 *  Created on: Jan 2, 2017
 *      Author: sajjadtest
 */

#ifndef MAVROSGLOBALPOSITION_H_
#define MAVROSGLOBALPOSITION_H_
#include <ros/ros.h>
#include <mavros_msgs/GlobalPositionTarget.h>
#include <iostream>
#include <sensor_msgs/NavSatFix.h>

class Mavros_Global_Position {
public:
    Mavros_Global_Position();
    void mavrosGlobalCb(const sensor_msgs::NavSatFixConstPtr &msg);

public:
    double lat;
    double lon;
};

#endif /* MAVROSGLOBALPOSITION_H_ */
