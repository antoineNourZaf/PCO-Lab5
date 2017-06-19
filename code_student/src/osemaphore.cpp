#include "osemaphore.h"

OSemaphore::OSemaphore(WaitingLogger* waitingLogger,int n):name("Semaphore")
{
    nbPermission = n;
    logger = waitingLogger;
    semaphore = new QSemaphore(nbPermission);
}


void OSemaphore::acquire(MyThread* thread){
    logger->addWaiting(thread->objectName(),name);
    semaphore.acquire();
    logger->removeWaiting(thread->objectName(),name);
}

void OSemaphore::release(){
    semaphore.release();
}

bool OSemaphore::tryAcquire(){

}
