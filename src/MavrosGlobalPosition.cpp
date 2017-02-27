/*
 * MavrosGlobalPosition.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: sajjadtest
 */

#include "MavrosGlobalPosition.h"
#include <qdebug.h>
#include <iostream>
#include <iomanip>

Mavros_Global_Position::Mavros_Global_Position() :
  lat(0), lon(0)
{
  // TODO Auto-generated constructor stub
}

void Mavros_Global_Position::mavrosGlobalCb(const sensor_msgs::NavSatFixConstPtr &msg)
{
  lat = msg->latitude;
  lon = msg->longitude;
//  std::cout << std::fixed;
//  std::cout << std::setprecision(7);
//    std::cout << std::endl << lat << std::endl << lon << std::endl;

}
