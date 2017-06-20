#include "omutex.h"
#include "waitinglogger.h"
#include <iostream>

OMutex::OMutex(WaitingLogger* waitingLogger)
{
    logger = waitingLogger;
    logger->creatQueueObject(this->name);
}

OMutex::~OMutex(){
    this->mutex.~QMutex();
    logger->rmQueueObject(this->name);
}

void OMutex::lock(const QString& threadName){
    logger->addWaiting(threadName,name);
    mutex.lock();
    logger->removeWaiting(threadName,name); //IL L'A TRAITER DONC PLUS DANS LA FILE
}

bool OMutex::tryLock(){
    //TODO
    return true;
}

void OMutex::unlock(){
    mutex.unlock();
}
