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

bool OWaitCondition::wait(OMutex *lockedMutex) {
    if (lockedMutex == nullptr)
        return false;
    //WaitingLogger::getInstance()->addWaiting(threadName,name);
    return qCond->wait(lockedMutex->getMutex());
    //WaitingLogger::getInstance()->removeWaiting(threadName,name);
}

void OWaitCondition::wakeOne() {
    qCond->wakeOne();
}

void OWaitCondition::wakeAll() {
    qCond->wakeAll();
}

