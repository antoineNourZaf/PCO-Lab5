#include "omutex.h"
#include "waitinglogger.h"

OMutex::OMutex(WaitingLogger* waitingLogger)
{
    logger = waitingLogger;
}

void OMutex::lock(const QString& threadName){
    logger->addWaiting(threadName,name); //threadName,this->name
    mutex.lock();
    logger->removeWaiting(threadName,name); //IL L'A TRAITER DONC PLUS DANS LA FILE
}

bool OMutex::tryLock(){
    //TODO
    return true;
}

void OMutex::unlock(){
    mutex.unlock();
}
