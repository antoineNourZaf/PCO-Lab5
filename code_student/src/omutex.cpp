#include "omutex.h"

// TODO
OMutex::OMutex(WaitingLogger* waitingLogger)
{
    logger = waitingLogger;
}

void OMutex::lock(){
    logger->addWaiting();
    mutex.lock();
    logger->removeWaiting();
}

bool OMutex::tryLock(){

}

void OMutex::unlock(){
    mutex.unlock();
}
