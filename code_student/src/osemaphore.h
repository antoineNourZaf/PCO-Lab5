#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H

#include <QSemaphore>
#include "waitinglogger.h"
//#include "mythread.h"

class MyThread;

class OSemaphore
{
private:
    const QString name;
    int nbPermission;
    QSemaphore *semaphore;
    WaitingLogger *logger;

public:
    OSemaphore(int n = 0);

    void acquire(MyThread* thread); // pour connaitre quel thread fait l'acquire

    void release();

    bool tryAcquire();
};

#endif // PSEMAPHORE_H
