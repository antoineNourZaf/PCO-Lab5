#include "omutex.h"

OMutex::OMutex(WaitingLogger* waitingLogger):name("Mutex")
{
    logger = waitingLogger;
}

void OMutex::lock(const QString& threadName){
    //logger->addWaiting("sd","sd"); //threadName,this->name
    mutex.lock();
    //logger->removeWaiting(threadName,name);
}

bool OMutex::tryLock(){
    //TODI
}

void OMutex::unlock(){
    mutex.unlock();
}
