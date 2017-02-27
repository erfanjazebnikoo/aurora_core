/*
 * WorldModel.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */

#include "WorldModel.h"
#include <iostream>
#include <iomanip>

using namespace au;

UNIQUE_INSTANCE_VARIABLE(WorldModel)

WorldModel::WorldModel() :
  share_memory(new Shared_Memory()), mavros_state(share_memory), start_mission(false), b(0)
{
  mavros_state_sub = n.subscribe("/mavros/state", 1, &Subscribe_mavros_state::mavrosStateCb, &mavros_state);
  mavros_global_position_sub = n.subscribe("/mavros/global_position/global", 1, &Mavros_Global_Position::mavrosGlobalCb,
    &mavros_global_position);
}

void WorldModel::init()
{
  itr = behaviours.wp.begin();
}

WorldModel::~WorldModel()
{
  // TODO Auto-generated destructor stub
}

void WorldModel::update()
{
  //  ROS_INFO("------------------------");
  if (start_mission)
  {
    //    ROS_INFO("Mission Started");
    double a = distance.distanceEarth(mavros_global_position.lat, mavros_global_position.lon, itr->lat, itr->lon);
    std::cout << std::fixed;
    std::cout << std::setprecision(7);
    std::cout << std::endl << a * 1000 << std::endl;
    //    if (a < 0.6)
    //    {
    //      b++;
    //      itr++;
    //      behaviours.gotoWp(itr->lat, itr->lon, itr->alt);
    //    }
    //
  }
  ros::spinOnce();

}
