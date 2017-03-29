/* 
 * @File:     GpsCoordination.cpp
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 28, 2017, 1:58 PM
 */

#include "GpsCoordination.h"
#include "Geometry.h"

using namespace au;
using namespace au::geo;

GpsCoordination::GpsCoordination()
{
  this->latitude = 0.0;
  this->longitude = 0.0;
  this->altitude = 0.0;
}

GpsCoordination::GpsCoordination(double latitude, double longitude, double altitude)
{
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
}

GpsCoordination::~GpsCoordination()
{
}

void GpsCoordination::init()
{
  this->latitude = 0.0;
  this->longitude = 0.0;
  this->altitude = 0.0;
}

void GpsCoordination::init(double latitude, double longitude, double altitude)
{
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
}

void GpsCoordination::init(GpsCoordination position)
{
  this->latitude = position.latitude;
  this->longitude = position.longitude;
  this->altitude = position.altitude;
}

double GpsCoordination::getLatitude()
{
  return this->latitude;
}

double GpsCoordination::getLongitude()
{
  return this->longitude;
}

double GpsCoordination::getAltitude()
{
  return this->altitude;
}

void GpsCoordination::setLatitude(double latitude)
{
  this->latitude = latitude;
}

void GpsCoordination::setLongitude(double longitude)
{
  this->longitude = longitude;
}

void GpsCoordination::setAltitude(double altitude)
{
  this->altitude = altitude;
}

double GpsCoordination::distance(GpsCoordination targets)
{
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(this->getLatitude());
  lon1r = deg2rad(this->getLongitude());
  lat2r = deg2rad(targets.getLatitude());
  lon2r = deg2rad(targets.getLongitude());
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)) * 1000.0;
}
