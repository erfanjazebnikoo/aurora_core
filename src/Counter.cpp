/* 
 * @File:     Counter.cpp
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 28, 2017, 1:19 PM
 */

#include "Counter.h"

using namespace au;

Counter::Counter()
{
  this->count = 0;
  this->maxCount = 10;
  this->state = false;
}

Counter::Counter(int maxCount)
{
  this->count = 0;
  this->maxCount = maxCount;
  this->state = false;
}

Counter::Counter(int maxCount, int count)
{
  this->count = count;
  this->maxCount = maxCount;
  this->state = false;
}

Counter::Counter(int maxCount, bool state)
{
  this->count = 0;
  this->maxCount = maxCount;
  this->state = state;
}

Counter::Counter(int maxCount, int count, bool state)
{
  this->count = count;
  this->maxCount = maxCount;
  this->state = state;
}

void Counter::init(int maxCount, int count, bool state)
{
  this->maxCount = maxCount;
  this->count = count;
  this->state = state;
}

void Counter::reset()
{
  setState(false);
}

void Counter::set()
{
  setState(true);
}

void Counter::increase(int amount)
{
  count += amount;
  if (count >= maxCount)
  {
    count = maxCount;
    state = true;
  }
}

void Counter::decrease(int amount)
{
  count -= amount;
  if (count <= 0)
  {
    count = 0;
    state = false;
  }
}

void Counter::setCount(int count)
{
  this->count = count;
  if (this->count >= maxCount)
  {
    setState(true);
  }
  else if (this->count <= 0)
  {
    setState(false);
  }
}

void Counter::setState(bool state)
{
  this->state = state;
  if (state)
  {
    count = maxCount;
  }
  else
  {
    count = 0;
  }

}

bool Counter::getState()
{
  return state;
}

int Counter::getCount()
{
  return count;
}

