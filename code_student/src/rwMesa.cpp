#include "abstractreaderwriter.h"
#include <iostream>

/* ------------------------
 *  MESA priorité égal
 * ----------------------*/

RWMesaEqualPrio::RWMesaEqualPrio() : fifo(new OWaitCondition()), mutex(new OMutex()), nbReaders(0), writingInProgress(false){
}

void RWMesaEqualPrio::lockReading(const QString& threadName){
    SynchroController::getInstance()->pause();

    mutex->lock(threadName);
    if(writingInProgress)
        fifo->wait(mutex,threadName);
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
        fifo->wakeOne();
    }
    mutex->unlock();
}

void RWMesaEqualPrio::lockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    if(nbReaders > 0 || writingInProgress)
        fifo->wait(mutex,threadName);
    writingInProgress = true;
    mutex->unlock();
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
}

void RWMesaEqualPrio::unlockWriting(const QString& threadName){
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    writingInProgress = false;
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    fifo->wakeOne();
    mutex->unlock();
}

/* ------------------------
 *  MESA pririté reader
 * ----------------------*/
RWMesaWritersPrio::RWMesaWritersPrio() :
    waitWriting(new OWaitCondition()),
    waitReading(new OWaitCondition()),
    mutex(new OMutex()),
    nbReaders(0), nbWaitingReaders(0), nbWaitingWriters(0), writingInProgress(false){

}

RWMesaWritersPrio::~RWMesaWritersPrio() {
    delete waitWriting;
    delete waitReading;
    delete mutex;
}

void RWMesaWritersPrio::lockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    if ((nbWaitingReaders > 0) || (writingInProgress)) {
        nbWaitingReaders++;
        waitReading->wait(mutex,threadName);
    }
    else {
        nbReaders++;
    }
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaWritersPrio::lockWriting(const QString& threadName) {
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    if ((nbReaders >0) || (writingInProgress)) {
        nbWaitingWriters++;
        waitWriting->wait(mutex,threadName);
    }
    else {
        writingInProgress = true;
    }
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaWritersPrio::unlockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    nbReaders--;
    if (nbReaders == 0) {
        waitWriting->wakeOne();
    }
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutex->unlock();
}

void RWMesaWritersPrio::unlockWriting(const QString& threadName) {
    SynchroController::getInstance()->pause();
    mutex->lock(threadName);
    writingInProgress = false;
    if (nbWaitingWriters > 0) { // réveiller les autres rédacteurs, un par un, sans perdre le mutex
        nbWaitingWriters --;
        writingInProgress = true;
        waitWriting->wakeOne();
    }
    else {
        for (int i = 0; i <nbWaitingReaders; ++i) { // réveiller les lecteurs
            waitReading->wakeOne();
        }
        nbReaders = nbWaitingReaders;
        nbWaitingReaders = 0;
    }
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutex->unlock();
}
