/* 
 * @File:     MavrosGlobalPosition.h
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Jan 2, 2017
 */

#ifndef MAVROSGLOBALPOSITION_H_
#define MAVROSGLOBALPOSITION_H_
#include <ros/ros.h>
#include <mavros_msgs/GlobalPositionTarget.h>
#include <iostream>
#include <sensor_msgs/NavSatFix.h>
#include "GpsCoordination.h"

namespace au {

    class MavrosGlobalPosition {
    public:
        MavrosGlobalPosition();
        void mavrosGlobalCb(const sensor_msgs::NavSatFixConstPtr &msg);

    public:
        GpsCoordination position;
    };
}
#endif /* MAVROSGLOBALPOSITION_H_ */
