/* 
 * @File:     GpsCoordination.h
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 28, 2017, 1:58 PM
 */

#ifndef GPSCOORDINATION_H
#define	GPSCOORDINATION_H

namespace au {

    class GpsCoordination {
    public:
        GpsCoordination();
        GpsCoordination(double latitude, double longitude, double altitude);
        virtual ~GpsCoordination();

        void init();
        void init(double latitude, double longitude, double altitude);
        void init(GpsCoordination position);

        double getLatitude();
        double getLongitude();
        double getAltitude();

        void setLatitude(double latitude);
        void setLongitude(double longitude);
        void setAltitude(double altitude);

        double distance(GpsCoordination targets);
    private:
        double latitude;
        double longitude;
        double altitude;
    };
}
#endif	/* GPSCOORDINATION_H */

