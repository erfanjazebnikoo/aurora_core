/* 
 * @File:     Autopilot.h
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 22, 2017, 4:33 PM
 */

#ifndef AUTOPILOT_H
#define	AUTOPILOT_H

#include "WorldModel.h"
#include "Counter.h"

namespace au {

    class Autopilot {
    public:
        Autopilot();
        virtual ~Autopilot();
        void execute();

        enum STATE {
            STATE_NUMB = -1,
            STATE_GUIDED_MODE = 0,
            STATE_ARM = 1,
            STATE_TAKE_OFF = 2,
            STATE_WAYPOINT_START = 3,
            STATE_WAYPOINT_CURRENT = 4,
            STATE_WAYPOINT_NEXT = 5,
            STATE_FIND_VICTIM = 6,
            STATE_DROP_LIFEBUOY = 7,
            STATE_WAYPOINT_RESUME = 8,
            STATE_WAYPOINT_FINISH = 9,
            STATE_RETURN_TO_HOME = 10
        };
    private:
        WorldModel *world;
        Behaviours *behaviours;
        bool needUpdate;
        bool isWayPointStarted;
        int currentState;
        WayPoint *currentWayPoint;
        QList<WayPoint> reachedWayPoints;
        bool isNextWayPointSet;
        Counter wayPointCounter;
        Counter updateCounter;
        bool isRobotAboveOfVictim;
        bool isRescueCompleted;
        double rescueAltitude;
        bool decreaseAltForRescue;
        
        void stateHandler();
        void wayPointsHandler();
        void currentStateDecisionMaker();
        bool readyForUpdate();
        void setRobotAboveOfVictim();
    };
}
#endif	/* AUTOPILOT_H */

