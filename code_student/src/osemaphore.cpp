#include "osemaphore.h"
#include "mythread.h"
#include <iostream>

int OSemaphore::compteur=0;

OSemaphore::OSemaphore(int n):name("Semaphore" + QString::number(compteur)),semaphore(new QSemaphore(n))
{
    nbPermission = n;
    logger = WaitingLogger::getInstance();
    compteur++;
    logger->creatQueueObject(this->name);
}

OSemaphore::~OSemaphore(){
    delete semaphore;
    logger->rmQueueObject(this->name);
}


void OSemaphore::acquire(const QString& threadName){
    logger->addWaiting(threadName,name);
    semaphore->acquire();
    logger->removeWaiting(threadName,name);
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){
    return tryAcquire();
}
