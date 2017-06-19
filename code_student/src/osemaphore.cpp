#include "osemaphore.h"

// TODO
OSemaphore::OSemaphore(int n = 0, WaitingLogger* waitingLogger)
{
    nbPermission = n;
    logger = waitingLogger;
    semaphore = new QSemaphore(nbPermission);
}


void OSemaphore::acquire(){
    logger->addWaiting();
    semaphore.acquire();
    logger->removeWaiting();
}

void OSemaphore::release(){
    semaphore.release();
}

bool OSemaphore::tryAcquire(){

}
