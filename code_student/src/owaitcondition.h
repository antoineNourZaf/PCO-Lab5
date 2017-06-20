#ifndef PWAITCONDITION_H
#define PWAITCONDITION_H

#include <QWaitCondition>
#include "omutex.h"

class OWaitCondition
{
private:
    QWaitCondition* qCond;
    static int compteur;
    const QString name;
public:

    OWaitCondition();
    ~OWaitCondition();

    bool wait(OMutex *lockedMutex,const QString& threadName);

    void wakeAll();

    void wakeOne();

};

#endif // PWAITCONDITION_H
