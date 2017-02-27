/*
 * WorldModel.h
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */

#ifndef WORLDMODEL_H_
#define WORLDMODEL_H_

#include "Library.h"
#include "shared_memory.h"
#include "subscribe_mavros_state.h"
#include "MavrosGlobalPosition.h"
#include "Behaviours.h"
#include "Geometry.h"

namespace au {

    class WorldModel {
        UNIQUE_INSTANCE(WorldModel)

    public:
        void init();
        void update();

    public:
        Shared_Memory* share_memory;
        Subscribe_mavros_state mavros_state;
        Mavros_Global_Position mavros_global_position;
        ros::NodeHandle n;
        ros::Subscriber mavros_state_sub;
        ros::Subscriber mavros_global_position_sub;
        au::Behaviours behaviours;
        bool start_mission;
        au::Behaviours::WP::const_iterator itr;
        au::Distance distance;
        int b;
    };

} // namespace au

#endif /* WORLDMODEL_H_ */
