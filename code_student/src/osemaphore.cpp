#include "osemaphore.h"
#include "mythread.h"
#include <iostream>

int OSemaphore::compteur=0;

OSemaphore::OSemaphore(int n):name("Semaphore" + QString::number(compteur)),semaphore(new QSemaphore())
{
    nbPermission = n;
    logger = WaitingLogger::getInstance();
    compteur++;
}


void OSemaphore::acquire(const QString& threadName){

    std::cout << name.toStdString() << " by : "<< threadName.toStdString() << std::endl;
    logger->addWaiting(threadName,name);
    semaphore->acquire();
    logger->removeWaiting(threadName,name);
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){

}
