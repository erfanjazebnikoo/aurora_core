/* 
 * @File:     Behaviours.h
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 29, 2016
 */

#ifndef BEHAVIOURS_H_
#define BEHAVIOURS_H_
#include "Library.h"
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/WaypointPush.h>
#include <rviz_satellite/ReadTakeoffGps.h>
#include <aurora_vision/heart.h>
#include <ros/ros.h>
#include "WayPoint.h"
#include <QList>
#include "GpsCoordination.h"

namespace au {

    class Behaviours {
        UNIQUE_INSTANCE(Behaviours)

    public:
        void takeOff(const QString &value);
        void guidedMode();
        void landMode();
        void rtlMode();
        void arm();
        void disarm();
        void gotoWp(double lat, double lon, int alt);
        void readTakeoffGps();
        double getTakeoffGpsLat();
        double getTakeoffGpsLon();
        void mavrosHeartCb(const aurora_vision::heart &msg);
        QList<au::WayPoint> &getWayPoints();
        au::WayPoint getWayPoint(int numOfWayPoint);

    private:
        double takeoff_gps_lat;
        double takeoff_gps_lon;

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

        ros::ServiceClient read_takeoff_gps_cl;
        rviz_satellite::ReadTakeoffGps srv_read_takeoff_gps;

        ros::Subscriber mavrosHeartSub;
    };

} /* namespace au */

#endif /* BEHAVIOURS_H_ */
