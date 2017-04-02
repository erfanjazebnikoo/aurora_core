/* 
 * @File:     WorldModel.h
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#ifndef WORLDMODEL_H_
#define WORLDMODEL_H_

#include "Library.h"
#include "SharedMemory.h"
#include "SubscribeMavrosState.h"
#include "MavrosGlobalPosition.h"
#include "Behaviours.h"
#include "Geometry.h"
#include "GpsCoordination.h"
#include <aurora_vision/heart.h>

using namespace std;

namespace au {

    class WorldModel {
        UNIQUE_INSTANCE(WorldModel)

    private:
        SharedMemory* shareMemory;
        SubscribeMavrosState mavrosState;
        ros::NodeHandle n;
        ros::Subscriber mavrosStateSub;
        ros::Subscriber mavrosGlobalPositionSub;
        ros::Subscriber mavrosHeartSub;
        MavrosGlobalPosition mavrosGlobalPosition;
        au::Behaviours *behaviours;
        bool startMission;
        void updateMyInformation();
        void mavrosHeartCb(const aurora_vision::heart &msg);

    public:
        void init();
        void update();
        bool isMissionStarted();
        void setStartMission(bool missionState);

        struct Me {
            GpsCoordination selfPosition;
            bool isArmed;
            bool isConnected;
            string mode;
            string modeChange;

            Me() : selfPosition(0.0, 0.0, 0.0), isArmed(false), isConnected(false), mode(""), modeChange("") {
            }
        } me;

        struct Heart {
            bool isSeen;
            double x;
            double y;
            double distance;

            Heart() : isSeen(false), x(0.0), y(0.0), distance(0.0) {
            }
        } heart;
    };

} // namespace au

#endif /* WORLDMODEL_H_ */
