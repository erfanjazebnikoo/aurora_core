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
namespace geo
{

double deg2rad(double deg)
{
  return (deg * M_PI / 180);
}

double rad2deg(double rad)
{
  return (rad * 180 / M_PI);
}
}
}
