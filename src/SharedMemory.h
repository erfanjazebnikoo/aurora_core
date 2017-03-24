/* 
 * @File:     SharedMemory.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <vector>
#include <pthread.h>
#include <iostream>

class SharedMemory {
public:
    SharedMemory();

    bool getArmed();
    void setArmed(bool b);
    std::string getMode();
    void setMode(std::string s);
    void setConnected(bool b);
    bool getConnected();
    std::string getModeChange();
    void setModeChange(std::string s);
private:
    pthread_mutex_t mutex;

    std::string mode;
    std::string modeChange;
    bool armed;
    bool connected;
};

#endif // SHARED_MEMORY_H
