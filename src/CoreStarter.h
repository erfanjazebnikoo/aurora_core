/*
 * CoreStarter.h
 *
 *  Created on: Dec 12, 2016
 *      Author: sajjadmuscle
 */

#ifndef CORESTARTER_H_
#define CORESTARTER_H_

#include "Core.h"
#include <QObject>

class CoreStarter : public QObject {
    Q_OBJECT

public:
    CoreStarter();
    ~CoreStarter();
};

#endif /* CORESTARTER_H_ */
