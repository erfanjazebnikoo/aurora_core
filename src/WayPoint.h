/* 
 * @File:     WayPoint.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 31, 2016
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "GpsCoordination.h"

namespace au {

    class WayPoint {
    public:
        WayPoint(GpsCoordination position);
        ~WayPoint();

    public:
        GpsCoordination position;
    };

} /* namespace au */

#endif /* WAYPOINT_H_ */
