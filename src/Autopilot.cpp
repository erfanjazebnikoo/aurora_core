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

double takeOffAlt = 20.0;

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
}

Autopilot::~Autopilot()
{
}

void Autopilot::execute()
{
  if (readyForUpdate())
  {
    ROS_ERROR("Autopilot => Size of Way points: %d", behaviours->getWayPoints().size());
    ROS_WARN("Autopilot => Distance: %f", world->me.selfPosition.distance(currentWayPoint->position));
    ROS_INFO("Autopilot => Lat: %f , Lon: %f , alt: %f", currentWayPoint->position.getLatitude(), currentWayPoint->position.getLongitude(),
      currentWayPoint->position.getAltitude());
    ROS_ERROR("Autopilot => Way point counter: %d", wayPointCounter.getCount());

    wayPointsHandler();
    currentStateDecisionMaker();

    if (needUpdate)
    {
      stateHandler();
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
    takeOffFlag = true;
    needUpdate = true;
  }
  else if (takeOffAlt - world->me.selfPosition.getAltitude() < 1.0 && !isWayPointStarted)
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
  else if (wayPointCounter.getCount() == behaviours->getWayPoints().size() &&
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
      needUpdate = false;
      break;
    case STATE_ARM:
      ROS_WARN("Autopilot => Armed...!");
      behaviours->arm();
      needUpdate = false;
      break;
    case STATE_TAKE_OFF:
      ROS_WARN("Autopilot => Take Off...!");
      behaviours->takeOff(QString::number(takeOffAlt));
      needUpdate = false;
      break;
    case STATE_WAYPOINT_START:
      ROS_WARN("Autopilot => Way Point Started...!");
      behaviours->gotoWp(currentWayPoint->position);
      isWayPointStarted = true;
      needUpdate = false;
      break;
    case STATE_WAYPOINT_CURRENT:
      //
      break;
    case STATE_WAYPOINT_NEXT:
      ROS_WARN("Autopilot => Next Way Point Started...!");
      behaviours->gotoWp(currentWayPoint->position);
      needUpdate = false;
      break;
    case STATE_FIND_VICTIM:
      //@TODO: handle find victim
      break;
    case STATE_DROP_LIFEBUOY:
      //@TODO: handle drop life buoy
      break;
    case STATE_WAYPOINT_RESUME:
      //@TODO: handle current way point
      break;
    case STATE_WAYPOINT_FINISH:
      //@TODO: handle current way point
      break;
    case STATE_RETURN_TO_HOME:
      behaviours->rtlMode();
      needUpdate = false;
      break;
    default:
      //@TODO: do nothing in this time
      break;
  }
}

void Autopilot::wayPointsHandler()
{
  if (world->me.selfPosition.distance(currentWayPoint->position) < 2.0)
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
  if (updateCounter.getState())
  {
    ROS_WARN("Autopilot => Ready for Update...!");
    updateCounter.reset();
    return true;
  }
  else
  {
    updateCounter.increase();
    return false;
  }
}