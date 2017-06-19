#include "osemaphore.h"
#include "mythread.h"

OSemaphore::OSemaphore(int n):name("Semaphore"),semaphore(new QSemaphore())
{
    nbPermission = n;
    logger = WaitingLogger::getInstance();
    //semaphore = new QSemaphore(nbPermission);
}


void OSemaphore::acquire(MyThread* thread){
    logger->addWaiting(thread->objectName(),name);
    semaphore->acquire();
    logger->removeWaiting(thread->objectName(),name);
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){

}
