#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H

#include "qmutex.h"
#include <QSemaphore>
#include "qwaitcondition.h"
#include "waitinglogger.h"



class OSemaphore
{
private:
    int nbPermission;
    QSemaphore semaphore;
    WaitingLogger *logger;

public:
    OSemaphore(int n, WaitingLogger* waitingLogger);

    void acquire();

    void release();

    bool tryAcquire();
};

#endif // PSEMAPHORE_H
