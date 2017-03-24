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
        MavrosGlobalPosition mavrosGlobalPosition;
        au::Behaviours *behaviours;
        bool startMission;
        void updateMyInformation();

    public:
        void init();
        void update();
        bool isMissionStarted();
        void setStartMission(bool missionState);

        struct Me {
            double lat;
            double lon;
            double alt;
            bool isArmed;
            bool isConnected;
            string mode;
            string modeChange;

            Me() : lat(0), lon(0), alt(0), isArmed(false), isConnected(false), mode(""), modeChange("") {
            }
        } me;
    };

} // namespace au

#endif /* WORLDMODEL_H_ */
