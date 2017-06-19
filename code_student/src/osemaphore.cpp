#include "osemaphore.h"
#include "mythread.h"

OSemaphore::OSemaphore(int n):name("Semaphore"),semaphore(new QSemaphore())
{
    nbPermission = n;
    logger = WaitingLogger::getInstance();
    //semaphore = new QSemaphore(nbPermission);
}


void OSemaphore::acquire(const QString& threadName){
    //logger->addWaiting(threadName,name);
    semaphore->acquire();
    //logger->removeWaiting(threadName,name);
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){

}
