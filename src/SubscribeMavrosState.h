/* 
 * @File:     SubscribeMavrosState.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#ifndef SUBSCRIBE_MAVROS_STATE_H
#define SUBSCRIBE_MAVROS_STATE_H

#include <ros/ros.h>
#include "mavros_msgs/State.h"

#include "SharedMemory.h"

class SubscribeMavrosState {
public:
    SubscribeMavrosState(SharedMemory* sharedMemory);
    void mavrosStateCb(const mavros_msgs::StateConstPtr &msg);

private:
    SharedMemory* sharedMemory;

    std::string mode;
    bool armed;
    bool guided;
    bool connected;
};
#endif // SUBSCRIBE_MAVROS_STATE_H
