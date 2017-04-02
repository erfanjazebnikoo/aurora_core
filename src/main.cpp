/* 
 * @File:     main.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include <QCoreApplication>
#include "CoreStarter.h"

#include "mavros_msgs/WaypointPush.h"

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "aurora_core");

  QCoreApplication application(argc, argv);
  QCoreApplication::setApplicationName(au::about::TITLE);
  QCoreApplication::setApplicationVersion(au::about::VERSION);
  QCoreApplication::setOrganizationName(au::about::TEAM);
  ROS_INFO("Main => Core Started...!");
  CoreStarter coreStarter;
  //  ros::spinOnce();
  application.exec();

}
