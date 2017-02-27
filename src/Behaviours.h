/*
 * Behaviours.h
 *
 *  Created on: Dec 29, 2016
 *      Author: sajjadmuscle
 */

#ifndef BEHAVIOURS_H_
#define BEHAVIOURS_H_
#include "Library.h"
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/WaypointPush.h>
#include <ros/ros.h>
#include "WayPoint.h"
#include <QList>

namespace au {

    class Behaviours {
    public:
        Behaviours();
        ~Behaviours();
        void takeOff(const QString &value);
        void guidedMode();
        void landMode();
        void rtlMode();
        void arm();
        void gotoWp(double lat, double lon, int alt);

    public:
        ros::NodeHandle n;

        ros::ServiceClient takeoff_cl;
        mavros_msgs::CommandTOL srv_takeoff;

        ros::ServiceClient cl_mode;
        mavros_msgs::SetMode srv_setMode;

        ros::ServiceClient arming_cl;
        mavros_msgs::CommandBool srv_arm;

        ros::ServiceClient waypoint_cl;
        mavros_msgs::WaypointPush waypoint_push;
        mavros_msgs::Waypoint waypoint;
        typedef QList<au::WayPoint> WP;
        QList<au::WayPoint> wp;

    };

} /* namespace au */

#endif /* BEHAVIOURS_H_ */
