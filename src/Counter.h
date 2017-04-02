/* 
 * @File:     Counter.h
 * @Author:   Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on March 28, 2017, 1:19 PM
 */

#ifndef COUNTER_H
#define	COUNTER_H
namespace au {

    class Counter {
    public:
        Counter();
        Counter(int maxCount);
        Counter(int maxCount, int count);
        Counter(int maxCount, bool state);
        Counter(int maxCount, int count, bool state);
        void init(int maxCount, int count = 0, bool state = false);
        void reset();
        void set();
        void increase(int amount = 1);
        void decrease(int amount = 1);
        void setCount(int count);
        int getCount();
        void setState(bool state);
        bool getState();
    private:
        int maxCount;
        int count;
        bool state;

    };
}

#endif	/* COUNTER_H */

