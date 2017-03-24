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

using namespace au;
using namespace std;

bool takeOffFlag;
bool wpFlag;

Autopilot::Autopilot()
{
  world = au::WorldModel::getInstance();
  behaviours = au::Behaviours::getInstance();
  takeOffFlag = false;
  wpFlag = false;
}

Autopilot::Autopilot(const Autopilot& orig)
{
}

Autopilot::~Autopilot()
{
}

void Autopilot::execute()
{
  if (!takeOffFlag)
  {
    takeOffFlag = true;
    behaviours->takeOff("20");
  }

  //  cout << "My Alt: " << world->me.alt << endl;

  if (20.0 - world->me.alt < 1.0)
  {
    //    int i = 0;
    if (!wpFlag)
    {
      cout << "Way Point Started...!!! :D" << endl;
      behaviours->gotoWp(behaviours->getWayPoint(0).lat, behaviours->getWayPoint(0).lon, behaviours->getWayPoint(0).alt);
      wpFlag = true;
    }
    //  world->behaviours.landMode();
    //    for (auto wp : world->behaviours.wp)
    //    {
    //
    //      cout << i << ":  " << wp.lat << endl;
    //      i++;
    //    }
  }
}
