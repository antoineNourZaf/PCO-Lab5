#include "omutex.h"
#include "waitinglogger.h"
#include <iostream>

OMutex::OMutex()
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    slotFree= true;
}

OMutex::~OMutex(){
    this->mutex.~QMutex();
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OMutex::lock(const QString& threadName){

    if(!slotFree)
         WaitingLogger::getInstance()->addWaiting(threadName,name);
    mutex.lock();
    slotFree = false;
     WaitingLogger::getInstance()->removeWaiting(threadName,name); //IL L'A TRAITER DONC PLUS DANS LA FILE
}

bool OMutex::tryLock(){
    //TODO
    return true;
}

void OMutex::unlock(){
    slotFree = true;
    mutex.unlock();
}
