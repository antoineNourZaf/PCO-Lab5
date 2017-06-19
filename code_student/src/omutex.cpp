#include "omutex.h"

OMutex::OMutex(WaitingLogger* waitingLogger):name("Mutex")
{
    logger = waitingLogger;
}

void OMutex::lock(MyThread* thread){
    logger->addWaiting(thread->objectName(),name);
    mutex.lock();
    logger->removeWaiting(thread->objectName(),name);
}

bool OMutex::tryLock(){
    //TODI
}

void OMutex::unlock(){
    mutex.unlock();
}
