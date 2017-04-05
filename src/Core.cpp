/* 
 * @File:     Core.cpp
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include "Core.h"
#include "WorldModel.h"
#include "UserInterface.h"
#include "Autopilot.h"
#include "AutoMission.h"

using namespace au;
using namespace std;

UNIQUE_INSTANCE_VARIABLE(Core)

Core::Core()
{
  // TODO Auto-generated constructor stub

}

void Core::init()
{
  cout << endl << "+******************************************************************************+" << endl;
  cout << au::about::LOGO.toStdString() << endl;
  cout << "  " << au::about::TITLE.toStdString() << " - Version: " << au::about::VERSION.toStdString() << endl <<
    "  " << au::about::TEAM.toStdString() << endl << "  " << au::about::DESCRIPTION.toStdString() << endl << endl << "  " <<
    au::about::MEMBER.toStdString() << endl << endl;
  cout << "+******************************************************************************+" << endl << endl;


  au::WorldModel::getInstance();
  au::Behaviours::getInstance();

  au::UserInterface::getInstance();
  au::UserInterface::getInstance()->init();
  thread.start();
}

void Core::Thread::run()
{
  au::WorldModel * wm = au::WorldModel::getInstance();
  AutoMission *autoMission = new AutoMission();
  while (true)
  {
    msleep(20);
    //    ROS_INFO("hi *********");
    wm->update();
    if (wm->isMissionStarted())
      autoMission->execute();
  }
}

Core::~Core()
{
  au::WorldModel::dropInstance();
  au::Behaviours::dropInstance();
  au::UserInterface::dropInstance();
}

