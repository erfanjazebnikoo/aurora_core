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

using namespace au;

class Autopilot {
public:
    Autopilot();
    Autopilot(const Autopilot& orig);
    virtual ~Autopilot();
    void execute();
    bool readyForUpdate();
private:
    au::WorldModel *world;
    au::Behaviours *behaviours;
    bool needUpdate;
};

#endif	/* AUTOPILOT_H */

