#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H

#include <QSemaphore>
#include "waitinglogger.h"

class OSemaphore {
private:
    static int compteur;
    int nbPermission;
    const QString name;
    QSemaphore *semaphore;
    WaitingLogger *logger;

public:
    OSemaphore(int n = 0);
    ~OSemaphore();
    void acquire(const QString & threadName);
    void release();
    bool tryAcquire();

};

#endif // PSEMAPHORE_H
