#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <vector>
#include <pthread.h>
#include <iostream>

class Shared_Memory {
public:
    Shared_Memory();

    bool getArmed();
    void setArmed(bool b);
    std::string getMode();
    void setMode(std::string s);
    void setConnected(bool b);
    bool getConnected();
    std::string getModeChange();
    void setModeChange(std::string s);
public:
    pthread_mutex_t mutex;

    std::string mode;
    std::string modeChange;
    bool armed;
    bool connected;
};

#endif // SHARED_MEMORY_H
