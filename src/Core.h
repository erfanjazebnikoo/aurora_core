/* 
 * @File:     Core.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#ifndef CORE_H_
#define CORE_H_

#include "Library.h"
#include <QThread>
#include <ros/ros.h>


namespace au {

    class Core {
        UNIQUE_INSTANCE(Core)

    public:
        void init();

    private:

        class Thread : public QThread {
        public:
            void run();
        };
        Thread thread;
    };

} // namespace name

#endif /* CORE_H_ */
