#ifndef PMUTEX_H
#define PMUTEX_H

#include <QMutex>
#include "waitinglogger.h"
class OMutex
{
private:
   QMutex mutex;
   WaitingLogger *logger;

public:
    OMutex(WaitingLogger* waitingLogger);

    void lock();

    bool tryLock();

    void unlock();
};

#endif // PMUTEX_H
