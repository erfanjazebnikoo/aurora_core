/*
 * UserInterface.h
 *
 *  Created on: Dec 22, 2016
 *      Author: sajjadmuscle
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "Library.h"
#include <qobject.h>
#include <qudpsocket.h>
#include <ros/ros.h>
#include "UICmdParser.h"
#include <QList>
#include "WayPoint.h"
#include <QString>
#include <QtXml/qdom.h>

namespace au {

    class UserInterface : QObject {

        Q_OBJECT

        UNIQUE_INSTANCE(UserInterface)

    private:
        class Parser : public au::UICmdParser {
            //    virtual void do_set(const QString &variable, const QString &value);
            //    virtual void do_get(const QString &variable);

            virtual void do_mavros_state();
            virtual void do_take_off(const QString &value);
            virtual void do_guided_mode();
            virtual void do_land_mode();
            virtual void do_rtl_mode();
            virtual void do_arm();
            virtual void do_disarm();
            virtual void do_fill_wayPoint(const QString &commands);
            virtual void do_start_mission();

            bool fromXMLtoWP(const QString &commands, QList<au::WayPoint> &wp);
        };

    public:
        void init();

    private:
        QUdpSocket *uiSocket;

    private slots:
        void readPendingDatagrams();

    };
} // namespace au

#endif /* USERINTERFACE_H_ */
