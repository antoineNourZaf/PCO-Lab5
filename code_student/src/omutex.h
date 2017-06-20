#ifndef PMUTEX_H
#define PMUTEX_H

#include <QMutex>
#include "waitinglogger.h"
//#include "mythread.h" //ICI problème ? Pourquo ?

class OMutex {
private:
    const QString name = "Mutex";
    QMutex* mutex;

public:

    OMutex();
    ~OMutex();
    QMutex* getMutex();
    void lock(const QString& threadName);
    bool tryLock();
    void unlock();
};

#endif // PMUTEX_H
