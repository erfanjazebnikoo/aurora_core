/* 
 * @File:     WayPoint.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 31, 2016
 */

#include "WayPoint.h"

using namespace au;

WayPoint::WayPoint(GpsCoordination position)
{
  this->position.setLatitude(position.getLatitude());
  this->position.setLongitude(position.getLongitude());
  this->position.setAltitude(position.getAltitude());
}

WayPoint::~WayPoint()
{
  // TODO Auto-generated destructor stub
}
