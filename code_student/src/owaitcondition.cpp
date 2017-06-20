#include "owaitcondition.h"

int OWaitCondition::compteur=0;

OWaitCondition::OWaitCondition() : qCond(new QWaitCondition()), name("WaitCondition" + QString::number(compteur))
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    compteur++;
}

OWaitCondition::~OWaitCondition(){
    delete qCond;
     WaitingLogger::getInstance()->rmQueueObject(this->name);
}

bool OWaitCondition::wait(OMutex *lockedMutex,const QString& threadName) {
    if (lockedMutex == nullptr)
        return false;
    WaitingLogger::getInstance()->addWaiting(threadName,name);
    bool status = qCond->wait(lockedMutex->getMutex());
    WaitingLogger::getInstance()->removeWaiting(threadName,name);
    return status;
}

void OWaitCondition::wakeOne() {
    qCond->wakeOne();
}

void OWaitCondition::wakeAll() {
    qCond->wakeAll();
}

