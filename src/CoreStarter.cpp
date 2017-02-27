/*
 * CoreStarter.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */

#include "CoreStarter.h"

CoreStarter::CoreStarter()
{
  au::Core::getInstance()->init();
}

CoreStarter::~CoreStarter()
{
  // TODO Auto-generated destructor stub
}

