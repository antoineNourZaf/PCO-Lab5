#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H

#include "qmutex.h"
#include "qsemaphore.h"
#include "qwaitcondition.h"


class OSemaphore
{
public:
    OSemaphore(int n = 0);

    void acquire();

    void release();

    bool tryAcquire();

private:
    QWaitCondition* condition;
    QMutex* mutex;
    int nbPermission;
};

#endif // PSEMAPHORE_H
