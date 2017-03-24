/* 
 * @File:     SharedMemory.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#include "SharedMemory.h"

SharedMemory::SharedMemory() :
  armed(false), connected(false)
{
  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    std::cout << "mutex init failed" << std::endl;
  }
}

std::string SharedMemory::getModeChange()
{
  std::string result;
  pthread_mutex_lock(&mutex);
  result = this->modeChange;
  pthread_mutex_unlock(&mutex);
  return result;
}

void SharedMemory::setModeChange(std::string s)
{
  pthread_mutex_lock(&mutex);
  this->modeChange = s;
  pthread_mutex_unlock(&mutex);
}

void SharedMemory::setMode(std::string s)
{
  pthread_mutex_lock(&mutex);
  this->mode = s;
  pthread_mutex_unlock(&mutex);
}

std::string SharedMemory::getMode()
{
  std::string result;
  pthread_mutex_lock(&mutex);
  result = this->mode;
  pthread_mutex_unlock(&mutex);
  return result;
}

void SharedMemory::setConnected(bool b)
{
  pthread_mutex_lock(&mutex);
  this->connected = b;
  pthread_mutex_unlock(&mutex);
}

bool SharedMemory::getConnected()
{
  bool result;
  pthread_mutex_lock(&mutex);
  result = this->connected;
  pthread_mutex_unlock(&mutex);
  return result;
}

void SharedMemory::setArmed(bool b)
{
  pthread_mutex_lock(&mutex);
  this->armed = b;
  pthread_mutex_unlock(&mutex);
}

bool SharedMemory::getArmed()
{
  bool result;
  pthread_mutex_lock(&mutex);
  result = this->armed;
  pthread_mutex_unlock(&mutex);
  return result;
}

