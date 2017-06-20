#include "omutex.h"
#include "waitinglogger.h"
#include <iostream>

OMutex::OMutex() : mutex(new QMutex())
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
}

OMutex::~OMutex(){
    delete mutex;
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OMutex::lock(const QString& threadName){

    if(!tryLock()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        mutex->lock();
        WaitingLogger::getInstance()->removeWaiting(threadName,name); //IL L'A TRAITER DONC PLUS DANS LA FILE
    }
}

bool OMutex::tryLock(){
    return mutex->tryLock();
}

void OMutex::unlock(){
    mutex->unlock();
}

QMutex* OMutex::getMutex(){
    return mutex;
}
