/* 
 * @File:     Behaviours.cpp
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 29, 2016
 */

#include "Behaviours.h"

using namespace au;

UNIQUE_INSTANCE_VARIABLE(Behaviours)
Behaviours::Behaviours()
{
  takeoff_cl = n.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff");
  cl_mode = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
  arming_cl = n.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
  waypoint_cl = n.serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push");
}

Behaviours::~Behaviours()
{

}

bool Behaviours::takeOff(const QString &value)
{
  srv_takeoff.request.altitude = value.toInt();
  srv_takeoff.request.latitude = 0;
  srv_takeoff.request.longitude = 0;
  srv_takeoff.request.min_pitch = 0;
  srv_takeoff.request.yaw = 0;
  if (takeoff_cl.call(srv_takeoff))
  {
    ROS_INFO("Behaviours => Take Off Send Successful...!");
    return srv_takeoff.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Take Off Send Failed...!");
    return srv_takeoff.response.success;
  }
}

bool Behaviours::guidedMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "GUIDED";
  if (cl_mode.call(srv_setMode))
  {
    ROS_INFO("Behaviours => Set Guided Mode Successful...!");
    return srv_setMode.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Set Guided Mode Failed...!");
    return srv_setMode.response.success;
  }
}

bool Behaviours::landMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "LAND";
  if (cl_mode.call(srv_setMode))
  {
    ROS_INFO("Behaviours => Set Land Mode Successful...!");
    return srv_setMode.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Set Land Mode Failed...!");
    return srv_setMode.response.success;
  }
}

bool Behaviours::rtlMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "RTL";
  if (cl_mode.call(srv_setMode))
  {
    ROS_INFO("Behaviours => Set RTL Mode Successful...!");
    return srv_setMode.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Set RTL Mode Failed...!");
    return srv_setMode.response.success;
  }
}

bool Behaviours::arm()
{
  srv_arm.request.value = true;
  if (arming_cl.call(srv_arm))
  {
    ROS_INFO("Behaviours => Arm Send Successful...!");
    return srv_arm.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Arm Send Failed...!");
    return srv_arm.response.success;
  }
}

bool Behaviours::disarm()
{
  srv_arm.request.value = false;
  if (arming_cl.call(srv_arm))
  {
    ROS_INFO("Behaviours => Disarm Send Successful...!");
    return srv_arm.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Disarm Send Failed...!");
    return srv_arm.response.success;
  }
}

bool Behaviours::gotoWp(GpsCoordination target)
{
  waypoint.frame = 3;
  waypoint.command = 16;
  waypoint.is_current = 2;
  waypoint.autocontinue = 0;
  waypoint.param1 = 0;
  waypoint.param2 = 0;
  waypoint.param3 = 0;
  waypoint.param4 = 0;
  waypoint.x_lat = target.getLatitude();
  waypoint.y_long = target.getLongitude();
  waypoint.z_alt = target.getAltitude();
  waypoint_push.request.waypoints.push_back(waypoint);
  if (waypoint_cl.call(waypoint_push))
  {
    ROS_INFO("Behaviours => Go to Way Point Successful...!");
    return waypoint_push.response.success;
  }
  else
  {
    ROS_ERROR("Behaviours => Go to Way Point Failed...!");
    return waypoint_push.response.success;
  }
}

QList<au::WayPoint> &Behaviours::getWayPoints()
{
  return wp;
}

au::WayPoint Behaviours::getWayPoint(int numOfWayPoint)
{
  return wp.at(numOfWayPoint);
}
