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
#include <mavros_msgs/OverrideRCIn.h>
#include <rviz_satellite/ReadTakeoffGps.h>
#include <ros/ros.h>
#include "WayPoint.h"
#include <QList>
#include "GpsCoordination.h"

namespace au {

    class Behaviours {
        UNIQUE_INSTANCE(Behaviours)

    public:
        bool takeOff(const QString &value);
        bool guidedMode();
        bool landMode();
        bool rtlMode();
        bool loiterMode();
        void radioControlDataOverride(double roll, double pitch, double throttle, double yaw);
        void radioControlDataOverride(double roll, double pitch, double throttle, double yaw, double gripperServo);
        bool arm();
        bool disarm();
        bool goToWayPoint(GpsCoordination target);
        bool goToWayPoint(double latitude, double longitude, double altitude);
        void readTakeoffGps();
        double getTakeoffGpsLat();
        double getTakeoffGpsLon();
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
        ros::Publisher rcOverridePub;
        typedef QList<au::WayPoint> WP;
        QList<au::WayPoint> wp;

        ros::ServiceClient read_takeoff_gps_cl;
        rviz_satellite::ReadTakeoffGps srv_read_takeoff_gps;
    };

} /* namespace au */

#endif /* BEHAVIOURS_H_ */
