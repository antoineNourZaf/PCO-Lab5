#include "omutex.h"
#include "waitinglogger.h"
#include <iostream>

int OMutex::compteur=0;

OMutex::OMutex() : mutex(new QMutex()),name("Mutex" + QString::number(compteur))
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    compteur++;
}

OMutex::~OMutex(){
    delete mutex;
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OMutex::lock(const QString& threadName){

    if(!tryLock()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        mutex->lock();
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
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
