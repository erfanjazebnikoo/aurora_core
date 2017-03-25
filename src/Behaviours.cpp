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
  read_takeoff_gps_cl = n.serviceClient<rviz_satellite::ReadTakeoffGps>("/read_takeoff_gps");
}

Behaviours::~Behaviours()
{

}

void Behaviours::takeOff(const QString &value)
{
  srv_takeoff.request.altitude = value.toInt();
  srv_takeoff.request.latitude = 0;
  srv_takeoff.request.longitude = 0;
  srv_takeoff.request.min_pitch = 0;
  srv_takeoff.request.yaw = 0;
  if (takeoff_cl.call(srv_takeoff))
  {
    ROS_ERROR("srv_takeoff send ok");
  }
  else
  {
    ROS_ERROR("Failed Takeoff");
  }
}

void Behaviours::guidedMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "GUIDED";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::landMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "LAND";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::rtlMode()
{
  srv_setMode.request.base_mode = 0;
  srv_setMode.request.custom_mode = "RTL";
  if (cl_mode.call(srv_setMode))
  {
    ROS_ERROR("setmode send ok");
  }
  else
  {
    ROS_ERROR("Failed SetMode");
  }
}

void Behaviours::arm()
{
  srv_arm.request.value = true;
  if (arming_cl.call(srv_arm))
  {
    ROS_ERROR("ARM send ok ");
  }
  else
  {
    ROS_ERROR("Failed arming or disarming");
  }
}

void Behaviours::disarm()
{
  srv_arm.request.value = false;
  if (arming_cl.call(srv_arm))
  {
    ROS_ERROR("ARM send ok ");
  }
  else
  {
    ROS_ERROR("Failed arming or disarming");
  }
}

void Behaviours::gotoWp(double lat, double lon, int alt)
{
  waypoint.frame = 3;
  waypoint.command = 16;
  waypoint.is_current = 2;
  waypoint.autocontinue = 0;
  waypoint.x_lat = lat;
  waypoint.param1 = 0;
  waypoint.param2 = 0;
  waypoint.param3 = 0;
  waypoint.param4 = 0;
  waypoint.y_long = lon;
  waypoint.z_alt = alt;
  waypoint_push.request.waypoints.push_back(waypoint);
  if (waypoint_cl.call(waypoint_push))
  {
    ROS_INFO("  go to waypoint  ");
  }
  else
    ROS_INFO("  cant go to waypoint  ");
}

QList<au::WayPoint> &Behaviours::getWayPoints()
{
  return wp;
}

au::WayPoint Behaviours::getWayPoint(int numOfWayPoint)
{
  return wp.at(numOfWayPoint);
}

void Behaviours::readTakeoffGps()
{
  if (read_takeoff_gps_cl.call(srv_read_takeoff_gps))
  {
    takeoff_gps_lat = srv_read_takeoff_gps.response.lat;
    takeoff_gps_lon = srv_read_takeoff_gps.response.lon;
    ROS_ERROR("Read takeoff gps %f", srv_read_takeoff_gps.response.lat);
  }
  else
  {
    ROS_ERROR("Cant read takeoff gps");
  }
}

double Behaviours::getTakeoffGpsLat()
{
  return this->takeoff_gps_lat;
}

double Behaviours::getTakeoffGpsLon()
{
  return this->takeoff_gps_lon;
}