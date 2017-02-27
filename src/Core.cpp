/*
 * Core.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */

#include "Core.h"
#include "WorldModel.h"
#include "UserInterface.h"

using namespace au;

UNIQUE_INSTANCE_VARIABLE(Core)

Core::Core()
{
  // TODO Auto-generated constructor stub

}

void Core::init()
{

  au::WorldModel::getInstance();

  au::UserInterface::getInstance();
  au::UserInterface::getInstance()->init();
  thread.start();
}

void Core::Thread::run()
{
  au::WorldModel * wm = au::WorldModel::getInstance();
  while (true)
  {
    msleep(20);
    //    ROS_INFO("hi *********");
    wm->update();

  }
}

Core::~Core()
{
  // TODO Auto-generated destructor stub
}

