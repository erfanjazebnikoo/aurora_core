/*
 * Core.h
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */
#include <QCoreApplication>
#include "CoreStarter.h"

#include "mavros_msgs/WaypointPush.h"

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "aurora_core");
//  ros::NodeHandle n;
//  ros::ServiceClient get = n.serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push");
//  mavros_msgs::WaypointPush wp_push;
//  mavros_msgs::Waypoint wp;
//  wp.frame = 3;
//  wp.command = 16;
//  wp.is_current = 2;
//  wp.autocontinue = 0;
//  wp.param1 = 0.0;
//  wp.x_lat = -35.3621170;
//  wp.y_long = 149.1651428;
//  wp.z_alt = 20;
//  wp_push.request.waypoints.clear();
//  wp_push.request.waypoints.push_back(wp);
//  if (get.call(wp_push))
//  {
//    ROS_INFO("dddddddddddddddddddddddddddddddddddd");
//  }
//  else
//    ROS_INFO("ffffffffffffffffffffffffffffffffff");


  QCoreApplication application(argc, argv);
  QCoreApplication::setApplicationName(au::about::TITLE);
  QCoreApplication::setApplicationVersion(au::about::VERSION);
  QCoreApplication::setOrganizationName(au::about::TEAM);
  ROS_INFO("----Core started----");
  CoreStarter coreStarter;
  //  ros::spinOnce();
  application.exec();

}
