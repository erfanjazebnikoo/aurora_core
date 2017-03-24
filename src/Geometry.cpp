/* 
 * @File:     Geometry.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Jan 2, 2017
 */

#include "Geometry.h"

namespace au
{

Distance::Distance()
{
  // TODO Auto-generated constructor stub
}

Distance::~Distance()
{
  // TODO Auto-generated destructor stub
}

double Distance::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d)
{
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}
} /* namespace au */

