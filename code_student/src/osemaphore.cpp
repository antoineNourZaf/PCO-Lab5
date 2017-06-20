#include "osemaphore.h"
#include "mythread.h"
#include <iostream>

int OSemaphore::compteur=0;

OSemaphore::OSemaphore(int n):name("Semaphore" + QString::number(compteur)),semaphore(new QSemaphore(n)), nbPermission(n)
{
    nbSlotFree = nbPermission;
    compteur++;
    WaitingLogger::getInstance()->creatQueueObject(this->name);
}

OSemaphore::~OSemaphore(){
    delete semaphore;
     WaitingLogger::getInstance()->rmQueueObject(this->name);
}


void OSemaphore::acquire(const QString& threadName){
    if(!tryAcquire()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        semaphore->acquire();
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
}

void OSemaphore::release(){
    semaphore->release();
    nbSlotFree++;
}

bool OSemaphore::tryAcquire(){
    return semaphore->tryAcquire();
}
