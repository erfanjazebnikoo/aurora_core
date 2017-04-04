/* 
 * @File:     Autopilot.cpp
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 22, 2017, 4:33 PM
 */

#include "Autopilot.h"
#include "Counter.h"

using namespace au;
using namespace std;

bool takeOffFlag;
bool wpFlag;

double takeOffAlt = 10.0;
bool findVictimExecute = true;

Autopilot::Autopilot()
{
  world = WorldModel::getInstance();
  behaviours = Behaviours::getInstance();
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
  isGotoHeartPosition = false;
  isRobotAboveOfVictim = false;
  isRescueCompleted = false;
  decreaseAltForRescue = false;
  releaseLifebuoyCounter.init(200);

  //////////////////////////////////////////// Landing
  takeOffPosition.init();
}

Autopilot::~Autopilot()
{
}

void Autopilot::execute()
{

  if (isRobotAboveOfVictim && findVictimExecute)
  {
    releaseLifebuoyDesicionMaker();
  }
  else
  {
    if (readyForUpdate())
    {
      wayPointsHandler();
      currentStateDecisionMaker();

      if (needUpdate)
      {
        stateHandler();
      }
    }
  }
}

void Autopilot::currentStateDecisionMaker()
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
    currentState = STATE_WAYPOINT_START;
    needUpdate = true;
  }
  else if (world->heart.isSeen && !isRescueCompleted)
  {
    currentState = STATE_FIND_VICTIM;
    isRobotAboveOfVictim = true;
    needUpdate = true;
  }
  else if (isRescueCompleted && !isWayPointStarted)
  {
    currentState = STATE_WAYPOINT_START;
    needUpdate = true;
  }
  else if (isNextWayPointSet)
  {
    currentState = STATE_WAYPOINT_NEXT;
    isNextWayPointSet = false;
    needUpdate = true;
  }
  else if (world->heart.isSeen && !isRescueCompleted)
  {
    currentState = STATE_FIND_VICTIM;
    isRobotAboveOfVictim = true;
    needUpdate = true;
  }
  else if (wayPointCounter.getCount() == behaviours->getWayPoints().size() - 1 &&
           world->me.selfPosition.distance(currentWayPoint->position) < 2.0)
  {
    currentState = STATE_RETURN_TO_HOME;
    needUpdate = true;
  }

}

void Autopilot::stateHandler()
{
  switch (currentState)
  {
    case STATE_GUIDED_MODE:
      ROS_WARN("Autopilot => Guided Mode Started...!");
      behaviours->guidedMode();
      break;
    case STATE_ARM:
      ROS_WARN("Autopilot => Armed...!");
      behaviours->arm();
      break;
    case STATE_TAKE_OFF:
      ROS_WARN("Autopilot => Take Off...!");
      behaviours->takeOff(QString::number(takeOffAlt));
      break;
    case STATE_GO_TO_VICTIM:
      ROS_WARN("Autopilot => Way Point Started...!");
      behaviours->goToWayPoint(currentWayPoint->position/* Heart Position */);
      isGotoHeartPosition = true;
      break;
    case STATE_FIND_VICTIM:
      ROS_WARN("Autopilot => Find Victim Started...!");
      behaviours->loiterMode();
      setRobotAboveOfVictim();
      break;
    case STATE_WAYPOINT_START:
      ROS_WARN("Autopilot => Way Point Started...!");
      behaviours->goToWayPoint(currentWayPoint->position);
      isWayPointStarted = true;
      break;
    case STATE_WAYPOINT_NEXT:
      ROS_WARN("Autopilot => Next Way Point Started...!");
      behaviours->goToWayPoint(currentWayPoint->position);
      break;

    case STATE_RETURN_TO_HOME:
      behaviours->rtlMode();
      break;
    default:
      //@TODO: do nothing in this time
      break;
  }
  needUpdate = false;
}

void Autopilot::wayPointsHandler()
{
  if (world->me.selfPosition.distance(currentWayPoint->position) < 2.0 &&
      wayPointCounter.getCount() < behaviours->getWayPoints().size() - 1)
  {
    //    reachedWayPoints.append(currentWayPoint);
    wayPointCounter.increase();
    isNextWayPointSet = true;
  }
  else
  {
    isNextWayPointSet = false;
  }
  currentWayPoint->position.init(behaviours->getWayPoint(wayPointCounter.getCount()).position);
}

bool Autopilot::readyForUpdate()
{
  if (world->heart.isSeen && !isRescueCompleted)
  {
    return true;
  }
  if (updateCounter.getState())
  {
    //    ROS_WARN("Autopilot => Ready for Update...!");
    updateCounter.reset();
    return true;
  }
  else
  {
    updateCounter.increase();
    return false;
  }
}

void Autopilot::setRobotAboveOfVictim()
{
  isRobotAboveOfVictim = true;

  if (world->heart.x > 163)
  {
    ROS_ERROR("Autopilot => Go Right for find victim...!");
    behaviours->radioControlDataOverride(1600, 1500, 1500, 1500);
  }
  else if (world->heart.x < 157)
  {
    ROS_INFO("Autopilot => Go Left for find victim...!");
    behaviours->radioControlDataOverride(1400, 1500, 1500, 1500);
  }
  else if (world->heart.y < 123)
  {
    ROS_ERROR("Autopilot => Go Forward for find victim...!");
    behaviours->radioControlDataOverride(1500, 1400, 1500, 1500);
  }
  else if (world->heart.y > 117)
  {
    ROS_INFO("Autopilot => Go Back for find victim...!");
    behaviours->radioControlDataOverride(1500, 1600, 1500, 1500);
  }
}

void Autopilot::releaseLifebuoyDesicionMaker()
{
  if (world->heart.distance > 5.0)
  {
    setRobotAboveOfVictim();
  }
  else
  {
    if (world->me.selfPosition.getAltitude() >= 3.0)
    {
      ROS_INFO("Autopilot => Decreasing Altitude for releasing lifebuoy...!");
      behaviours->radioControlDataOverride(1500, 1500, 1400, 1500);
    }
    else
    {
      if (!releaseLifebuoyCounter.getState())
      {
        ROS_INFO("Autopilot => Releasing lifebuoy...!");
        behaviours->radioControlDataOverride(1500, 1500, 1500, 1500, 2000);
        releaseLifebuoyCounter.increase();
      }
      else
      {
        ROS_INFO("Autopilot => Lifebuoy released successfully...!");
        behaviours->radioControlDataOverride(1500, 1500, 1500, 1500, 1500);
        isRescueCompleted = true;
        findVictimExecute = false;
        isRobotAboveOfVictim = false;
        ROS_WARN("Autopilot => Find Victim Finished...!");
      }
    }
  }
}

