/* 
 * @File:     MavrosGlobalPosition.cpp
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Jan 2, 2017
 */

#include "MavrosGlobalPosition.h"
#include <qdebug.h>
#include <iostream>
#include <iomanip>

using namespace au;

MavrosGlobalPosition::MavrosGlobalPosition() :
  position(0.0, 0.0, 0.0)
{
  // TODO Auto-generated constructor stub
}

void MavrosGlobalPosition::mavrosGlobalCb(const sensor_msgs::NavSatFixConstPtr &msg)
{
  position.setLatitude(msg->latitude);
  position.setLongitude(msg->longitude);
  position.setAltitude(msg->altitude);
  //  std::cout << std::fixed;
  //  std::cout << std::setprecision(7);
  //    std::cout << std::endl << lat << std::endl << lon << std::endl;

}
