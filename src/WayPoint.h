/*
 * WayPoint.h
 *
 *  Created on: Dec 31, 2016
 *      Author: sajjadmuscle
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

namespace au {

    class WayPoint {
    public:
        WayPoint(double lat, double lon, int alt);
        ~WayPoint();

    public:
        double lat;
        double lon;
        int alt;
    };

} /* namespace au */

#endif /* WAYPOINT_H_ */
