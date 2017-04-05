/* 
 * @File:     AutoMission.h
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 22, 2017, 4:33 PM
 */

#ifndef AUTOMISSION_H
#define	AUTOMISSION_H

#include "WorldModel.h"
#include "Counter.h"

namespace au {

    class AutoMission {
    public:
        AutoMission();
        virtual ~AutoMission();
        void execute();

        enum STATE {
            STATE_NUMB = -1,
            STATE_GUIDED_MODE = 0,
            STATE_ARM = 1,
            STATE_TAKE_OFF = 2,
            STATE_GO_TO_VICTIM = 3,
            STATE_FIND_VICTIM = 4,
            STATE_FIND_VICTIM2 = 5,
            STATE_FIND_VICTIM_EMERGENCY = 6,
            STATE_DROP_LIFEBUOY = 7,
            STATE_WAYPOINT_START = 8,
            STATE_AUTO = 9
        };
    private:
        WorldModel *world;
        Behaviours *behaviours;
        bool takeOffFlag;
        bool wpFlag;
        double takeOffAlt;
        bool findVictimExecute;
        bool needUpdate;
        bool isWayPointStarted;
        int currentState;
        WayPoint *currentWayPoint;
        QList<WayPoint> reachedWayPoints;
        bool isNextWayPointSet;
        Counter wayPointCounter;
        Counter updateCounter;

        //////////////////////////////////////////// Victim and Lifebuoy
        GpsCoordination heartPosition;
        Counter noVictimCounter;
        Counter releaseLifebuoyCounter;
        bool isReleasingLifebuoy;
        bool isGotoHeartPosition;
        bool isRobotAboveOfVictim;
        bool isRescueCompleted;
        bool decreaseAltForRescue;
        
        bool findVictimFlag;
        bool findVictim2Flag;
        bool findVictimEmergencyFlag;
        bool lifebuoyFlag;
        bool autoFlag;
        
        //////////////////////////////////////////// Landing
        GpsCoordination takeOffPosition;

        void stateHandler();
        void currentStateDecisionMaker();
        bool readyForUpdate();
        void setRobotAboveOfVictim();
        void releaseLifebuoyDesicionMaker();
    };
}
#endif	/* AUTOMISSION_H */

