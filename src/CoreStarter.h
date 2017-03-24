/* 
 * @File:     CoreStarter.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
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
