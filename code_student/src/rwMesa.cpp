#include "abstractreaderwriter.h"
#include <iostream>

/* ------------------------
 *  MESA priorité égal
 * ----------------------*/

RWMesaEqualPrio::RWMesaEqualPrio() : condFIFO(new OWaitCondition()), mutex(new OMutex()), nbReaders(0), writingInProgress(false){
}

void RWMesaEqualPrio::lockReading(const QString& threadName){
    SynchroController::getInstance()->pause();

    mutex->lock(threadName);
    if(writingInProgress)
        condFIFO->wait(mutex);
    nbReaders++;
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaEqualPrio::unlockReading(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    nbReaders--;
    if(nbReaders == 0){
        condFIFO->wakeOne();
    }
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaEqualPrio::lockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    if(nbReaders > 0 || writingInProgress)
        condFIFO->wait(mutex);
    writingInProgress = true;
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaEqualPrio::unlockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    writingInProgress = false;
    condFIFO->wakeOne();
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutex->unlock();
}

/* ------------------------
 *  MESA pririté reader
 * ----------------------*/
