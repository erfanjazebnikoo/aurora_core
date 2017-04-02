/* 
 * @File:     Geometry.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Jan 2, 2017
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <cmath>
//#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

namespace au {

    namespace geo {
        
        double deg2rad(double deg);
        double rad2deg(double rad);
    }
} /* namespace au */

#endif /* GEOMETRY_H_ */
