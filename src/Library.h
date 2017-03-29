/* 
 * @File:     Library.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 12, 2016
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <cstdlib>
#include <QString>
#include <QtGlobal>
#include <QtAlgorithms>

namespace au {

#define UNIQUE_INSTANCE(CLASS) \
	    public: \
	        static inline CLASS *getInstance() \
	        { \
	            if (!__uniqeInstance__) \
	            {\
	                __uniqeInstance__ = new CLASS; \
	            }\
	            return __uniqeInstance__; \
	        } \
	        static inline void dropInstance()\
	        {\
	            if (__uniqeInstance__)\
	            {\
	                delete __uniqeInstance__;\
	                __uniqeInstance__ = 0;\
	            }\
	        }\
	        static inline bool hasInstance()\
	        {\
	            return (__uniqeInstance__);\
	        }\
	    private:\
	        CLASS(); \
	        virtual ~CLASS(); \
	        CLASS(const CLASS&);\
	        CLASS &operator=(const CLASS &);\
	        static CLASS *__uniqeInstance__;

#define UNIQUE_INSTANCE_VARIABLE(CLASS) CLASS *CLASS::__uniqeInstance__ = 0;

    namespace about {
        extern const QString TITLE;
        extern const QString VERSION;
        extern const QString TEAM;
        extern const QString MEMBER;
        extern const QString LICENCE;
        extern const QString DESCRIPTION;
        extern const QString PLATFORM;
        extern const QString LOGO;
    }

} // namespace au

#endif /* LIBRARY_H_ */
