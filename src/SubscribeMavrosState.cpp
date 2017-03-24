/* 
 * @File:     SubscribeMavrosState.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include "SubscribeMavrosState.h"

SubscribeMavrosState::SubscribeMavrosState(SharedMemory* sharedMemory) :
  armed(false), connected(false), guided(false)
{
  this->sharedMemory = sharedMemory;

}

void SubscribeMavrosState::mavrosStateCb(const mavros_msgs::StateConstPtr &msg)
{
  if (msg->mode == std::string("CMODE(0)"))
    return;
  ROS_INFO("I heard: [%s] [%d] [%d]", msg->mode.c_str(), msg->armed, msg->guided);
  this->mode = msg->mode;
  this->guided = msg->guided == 128;
  this->armed = msg->armed == 128;
  this->sharedMemory->setArmed(this->armed);
  this->sharedMemory->setMode(this->mode);
  this->connected = msg->connected;
  this->sharedMemory->setConnected(this->connected);
}
