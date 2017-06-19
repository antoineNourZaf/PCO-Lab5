#ifndef PMUTEX_H
#define PMUTEX_H

#include <QMutex>
#include "waitinglogger.h"
#include "mythread.h"

class OMutex
{
private:
   const QString name;
   QMutex mutex;
   WaitingLogger *logger;

public:
    OMutex(WaitingLogger* waitingLogger);

    void lock(MyThread* thread);

    bool tryLock();

    void unlock();
};

#endif // PMUTEX_H
