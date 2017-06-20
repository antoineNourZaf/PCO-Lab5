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
        condFIFO->wait(mutex,threadName);
    nbReaders++;
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaEqualPrio::unlockReading(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    nbReaders--;
    if(nbReaders == 0){
        condFIFO->wakeOne();
    }
    mutex->unlock();
}

void RWMesaEqualPrio::lockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    if(nbReaders > 0 || writingInProgress)
        condFIFO->wait(mutex,threadName);
    writingInProgress = true;
    mutex->unlock();
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
}

void RWMesaEqualPrio::unlockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    writingInProgress = false;
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    condFIFO->wakeOne();
    mutex->unlock();
}

/* ------------------------
 *  MESA pririté reader
 * ----------------------*/
