/* 
 * @File:     AutoMission.cpp
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 22, 2017, 4:33 PM
 */

#include "AutoMission.h"
#include "Counter.h"

using namespace au;
using namespace std;

AutoMission::AutoMission()
{
  world = WorldModel::getInstance();
  behaviours = Behaviours::getInstance();

  takeOffAlt = 10.0;

  needUpdate = false;
  takeOffFlag = false;
  wpFlag = false;
  currentState = STATE_NUMB;
  GpsCoordination tempCoordination;
  tempCoordination.init();
  currentWayPoint = new WayPoint(tempCoordination);
  isWayPointStarted = false;
  updateCounter.init(150); // Update timer default value is = 150
  wayPointCounter.init(100);
  reachedWayPoints.clear();
  isNextWayPointSet = false;

  //////////////////////////////////////////// Victim and Lifebuoy
  heartPosition.init();
  isGotoHeartPosition = false;
  isRobotAboveOfVictim = false;
  isRescueCompleted = false;
  decreaseAltForRescue = false;
  releaseLifebuoyCounter.init(100);
  noVictimCounter.init(10);

  findVictimFlag = false;
  findVictim2Flag = false;
  findVictimEmergencyFlag = false;
  lifebuoyFlag = false;
  autoFlag = false;

  //////////////////////////////////////////// Landing
  takeOffPosition.init();
}

AutoMission::~AutoMission()
{
}

void AutoMission::execute()
{
  if (isReleasingLifebuoy)
  {
    releaseLifebuoyDesicionMaker();
  }
  else
  {
    if (readyForUpdate())
    {
      currentStateDecisionMaker();

      if (needUpdate)
      {
        stateHandler();
      }
    }
  }
}

void AutoMission::currentStateDecisionMaker()
{

  if (currentState == STATE_NUMB && world->me.mode != "GUIDED")
  {
    currentState = STATE_GUIDED_MODE;
    needUpdate = true;
  }
  else if (currentState == STATE_GUIDED_MODE && !world->me.isArmed)
  {
    currentState = STATE_ARM;
    needUpdate = true;
  }
  else if (currentState == STATE_ARM && !takeOffFlag)
  {
    currentState = STATE_TAKE_OFF;
    takeOffPosition.init(world->me.selfPosition);
    takeOffFlag = true;
    needUpdate = true;
  }
  else if (takeOffAlt - world->me.selfPosition.getAltitude() < 1.0 && !isGotoHeartPosition)
  {
    currentState = STATE_GO_TO_VICTIM;
    needUpdate = true;
  }
  else if (world->me.selfPosition.distance(heartPosition) < 2.0 &&
           world->heart.isSeen && !findVictimFlag)
  {
    currentState = STATE_FIND_VICTIM;
    isRobotAboveOfVictim = true;
    findVictimFlag = true;
    needUpdate = true;
  }
  else if (isRobotAboveOfVictim && world->me.selfPosition.getAltitude() < 6.2 &&
           !findVictim2Flag)
  {
    currentState = STATE_FIND_VICTIM2;
    findVictim2Flag = true;
    needUpdate = true;
  }
  else if (world->me.selfPosition.distance(heartPosition) < 2.0 &&
           !world->heart.isSeen && !findVictimEmergencyFlag)
  {
    noVictimCounter.increase();

    if (noVictimCounter.getState())
    {
      currentState = STATE_FIND_VICTIM_EMERGENCY;
      findVictimEmergencyFlag = true;
      needUpdate = true;
    }
  }
  else if (world->me.selfPosition.distance(heartPosition) < 2.0 &&
           world->me.selfPosition.getAltitude() < 3.2 && !lifebuoyFlag)
  {
    currentState = STATE_DROP_LIFEBUOY;
    lifebuoyFlag = true;
    needUpdate = true;
  }
  else if (isRescueCompleted && !isWayPointStarted)
  {
    currentState = STATE_WAYPOINT_START;
    needUpdate = true;
  }
  else if (isWayPointStarted &&
           world->me.selfPosition.getAltitude() > takeOffAlt - 0.5 &&
           !autoFlag)
  {
    currentState = STATE_AUTO;
    autoFlag = true;
    needUpdate = true;
  }
}

void AutoMission::stateHandler()
{
  switch (currentState)
  {
    case STATE_GUIDED_MODE:
      ROS_WARN("AutoMission => Guided Mode Started...!");
      behaviours->guidedMode();
      break;
    case STATE_ARM:
      ROS_WARN("AutoMission => Armed...!");
      behaviours->arm();
      break;
    case STATE_TAKE_OFF:
      ROS_WARN("AutoMission => Take Off...!");
      behaviours->takeOff(QString::number(takeOffAlt));
      break;
    case STATE_GO_TO_VICTIM:
      ROS_WARN("AutoMission => Go to Heart Position Started...!");
      heartPosition.init(world->heart.firstLatitude, world->heart.firstLongtidue,
        takeOffAlt);
      behaviours->goToWayPoint(heartPosition);
      isGotoHeartPosition = true;
      break;
    case STATE_FIND_VICTIM:
      ROS_WARN("AutoMission => Find Victim Started...!");
      heartPosition.init(world->heart.firstLatitude, world->heart.firstLongtidue, 6.0); ///new point based on heart position in frame
      behaviours->goToWayPoint(heartPosition);
      break;
    case STATE_FIND_VICTIM2:
      ROS_WARN("AutoMission => Decrease Altitude and Find Victim...!");
      heartPosition.init(world->heart.firstLatitude, world->heart.firstLongtidue, 3.0); ///new point based on heart position in frame
      behaviours->goToWayPoint(heartPosition);
      break;
    case STATE_FIND_VICTIM_EMERGENCY:
      ROS_WARN("AutoMission => Emergency Mode of Find Victim Started...!");
      heartPosition.init(world->heart.firstLatitude, world->heart.firstLongtidue, 3.0);
      behaviours->goToWayPoint(heartPosition);
      break;
    case STATE_DROP_LIFEBUOY:
      ROS_WARN("AutoMission => Lifebuoy Releasing Started...!");
      releaseLifebuoyDesicionMaker();
      break;
    case STATE_WAYPOINT_START:
      ROS_WARN("AutoMission => Way Point Started...!");
      behaviours->goToWayPoint(world->me.selfPosition.getLatitude(),
        world->me.selfPosition.getLongitude(),
        takeOffAlt);
      isWayPointStarted = true;
      break;
    case STATE_AUTO:
      ROS_WARN("AutoMission => Mapping Started...!");
      behaviours->autoMode();
      break;
    default:
      //@TODO: do nothing in this time
      break;
  }
  needUpdate = false;
}

bool AutoMission::readyForUpdate()
{
  if (updateCounter.getState())
  {
    //    ROS_WARN("AutoMission => Ready for Update...!");
    updateCounter.reset();
    return true;
  }
  else
  {
    updateCounter.increase();
    return false;
  }
}

void AutoMission::releaseLifebuoyDesicionMaker()
{
  if (!releaseLifebuoyCounter.getState())
  {
    ROS_INFO("AutoMission => Releasing lifebuoy...!");
    isReleasingLifebuoy = true;
    behaviours->radioControlDataOverride(2000);
    releaseLifebuoyCounter.increase();
  }
  else
  {
    ROS_INFO("AutoMission => Lifebuoy released successfully...!");
    isRescueCompleted = true;
    isRobotAboveOfVictim = false;
    isReleasingLifebuoy = false;
    ROS_WARN("AutoMission => Find Victim Finished...!");
  }
}

