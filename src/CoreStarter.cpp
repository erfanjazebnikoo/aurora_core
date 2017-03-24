/* 
 * @File:     CoreStarter.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
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

