#include "shared_memory.h"

Shared_Memory::Shared_Memory() :
  armed(false), connected(false)
{
  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    std::cout << "mutex init failed" << std::endl;
  }
}

std::string Shared_Memory::getModeChange()
{
  std::string result;
  pthread_mutex_lock(&mutex);
  result = this->modeChange;
  pthread_mutex_unlock(&mutex);
  return result;
}

void Shared_Memory::setModeChange(std::string s)
{
  pthread_mutex_lock(&mutex);
  this->modeChange = s;
  pthread_mutex_unlock(&mutex);
}

void Shared_Memory::setMode(std::string s)
{
  pthread_mutex_lock(&mutex);
  this->mode = s;
  pthread_mutex_unlock(&mutex);
}

std::string Shared_Memory::getMode()
{
  std::string result;
  pthread_mutex_lock(&mutex);
  result = this->mode;
  pthread_mutex_unlock(&mutex);
  return result;
}

void Shared_Memory::setConnected(bool b)
{
  pthread_mutex_lock(&mutex);
  this->connected = b;
  pthread_mutex_unlock(&mutex);
}

bool Shared_Memory::getConnected()
{
  bool result;
  pthread_mutex_lock(&mutex);
  result = this->connected;
  pthread_mutex_unlock(&mutex);
  return result;
}

void Shared_Memory::setArmed(bool b)
{
  pthread_mutex_lock(&mutex);
  this->armed = b;
  pthread_mutex_unlock(&mutex);
}

bool Shared_Memory::getArmed()
{
  bool result;
  pthread_mutex_lock(&mutex);
  result = this->armed;
  pthread_mutex_unlock(&mutex);
  return result;
}

