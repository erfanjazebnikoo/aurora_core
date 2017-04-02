/* 
 * @File:     WorldModel.cpp
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include "WorldModel.h"
#include <iostream>
#include <iomanip>
#include <stdbool.h>

using namespace au;
using namespace std;

double firstAlt;
bool isFirstAltSet;

UNIQUE_INSTANCE_VARIABLE(WorldModel)

WorldModel::WorldModel() :
  shareMemory(new SharedMemory()), mavrosState(shareMemory), startMission(false)
{
  mavrosStateSub = n.subscribe("/mavros/state", 1, &SubscribeMavrosState::mavrosStateCb, &mavrosState);
  mavrosGlobalPositionSub = n.subscribe("/mavros/global_position/global", 1, &MavrosGlobalPosition::mavrosGlobalCb,
    &mavrosGlobalPosition);
  mavrosHeartSub = n.subscribe("/heart", 1, &WorldModel::mavrosHeartCb, this);
  behaviours = Behaviours::getInstance();
  isFirstAltSet = false;
}

void WorldModel::init()
{

}

WorldModel::~WorldModel()
{
  // TODO Auto-generated destructor stub
}

void WorldModel::update()
{
  updateMyInformation();

  ros::spinOnce();
}

void WorldModel::updateMyInformation()
{
  if (!isFirstAltSet && mavrosGlobalPosition.position.getAltitude() > 1.0)
  {
    firstAlt = this->mavrosGlobalPosition.position.getAltitude();
    isFirstAltSet = true;
  }

  if (isFirstAltSet)
  {
    me.selfPosition.setLatitude(this->mavrosGlobalPosition.position.getLatitude());
    me.selfPosition.setLongitude(this->mavrosGlobalPosition.position.getLongitude());
    me.selfPosition.setAltitude(this->mavrosGlobalPosition.position.getAltitude() - firstAlt);
  }

  me.isArmed = shareMemory->getArmed();
  me.isConnected = shareMemory->getConnected();
  me.mode = shareMemory->getMode();
  me.modeChange = shareMemory->getModeChange();
}

bool WorldModel::isMissionStarted()
{
  return startMission;
}

void WorldModel::setStartMission(bool missionState)
{
  startMission = missionState;
}

void WorldModel::mavrosHeartCb(const aurora_vision::heart &msg)
{
  heart.isSeen = true;
  heart.x = msg.X;
  heart.y = msg.Y;
  heart.distance = msg.Distance;
}