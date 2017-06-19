#ifndef OWAITCONDITION_H
#define OWAITCONDITION_H

#include <QWaitCondition>
#include "waitinglogger.h"
#include "omutex.h"


// pour Mesa
class OWaitCondition
{
private:
    QWaitCondition qCond;
    QString name = "OWaitCondition";
    WaitingLogger* logger;
public:

    OWaitCondition(WaitingLogger* waitingLogger);

    bool wait(OMutex *lockedMutex, const QString& threadName);

    void wakeAll();

    void wakeOne(const QString& threadName);

};

#endif // OWAITCONDITION_H
