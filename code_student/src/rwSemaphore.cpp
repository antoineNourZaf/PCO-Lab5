/**
  * définitions des lecteurs et des rédacteurs
  */

#include "abstractreaderwriter.h"
#include <iostream>

/******************** IMPLEMENTATIONS SEMAPHORES **************************
 * Priorité égale
 *********************************************************/

ReaderWriterSemaphoreEqualPrio::ReaderWriterSemaphoreEqualPrio(): nbReader(0), mutex(new OSemaphore(1)),fifo(new OSemaphore(1)),writer(new OSemaphore(1)){

}

ReaderWriterSemaphoreEqualPrio::~ReaderWriterSemaphoreEqualPrio() {
    delete writer;
    delete fifo;
    delete mutex;
}

void ReaderWriterSemaphoreEqualPrio::lockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    // le premier lecteur va vérouiller
    fifo->acquire(threadName);
    mutex->acquire(threadName);

    nbReader++;
    if (nbReader == 1) {
        writer->acquire(threadName); // bloquer les rédacteurs
    }
    mutex->release();
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    fifo->release(); // le suivant dans la fifo pourra tenter sa chance
}

void ReaderWriterSemaphoreEqualPrio::unlockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    mutex->acquire(threadName);
    nbReader--;
    if (nbReader == 0) {
        writer->release(); // le dernier lecteur permet debloque l'écriture
    }
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutex->release();
}

void ReaderWriterSemaphoreEqualPrio::lockWriting(const QString& threadName) {
    fifo->acquire(threadName); // le redacteur va bloquer tout ceux qui attendent dans la file
    writer->acquire(threadName);
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
}

void ReaderWriterSemaphoreEqualPrio::unlockWriting(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);

    writer->release();
    fifo->release();
}

/*******************************************************
 * EM Writers Prio
 *******************************************************/

ReaderWriterSemaphoreWritersPrio::ReaderWriterSemaphoreWritersPrio(): mutexReaders(new OSemaphore(1)), mutexWriters(new OSemaphore(1)), writer(new OSemaphore(1)), reader(new OSemaphore(1)), mutex(new OSemaphore(1)), nbReaders(0), nbWriters(0)
{

}

ReaderWriterSemaphoreWritersPrio::~ReaderWriterSemaphoreWritersPrio() {
        delete mutexReaders;
        delete mutexWriters;
        delete writer;
        delete reader;
        delete mutex;
}

void ReaderWriterSemaphoreWritersPrio::lockReading(const QString& threadName) {
    mutexReaders->acquire(threadName); // seulement 1 lecteur peut entrer
    reader->acquire(threadName); // un redacteur va bloquer les rédacteurs et les lecteurs
    mutex->acquire(threadName);
    nbReaders++;
    if (nbReaders == 1) { // le premier lecteur
        writer->acquire(threadName); // va bloquer les rédacteurs
    }
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);

    mutex->release(); // relachement de la lecteur
    reader->release();
    mutexReaders->release();
}

void ReaderWriterSemaphoreWritersPrio::lockWriting(const QString& threadName) {
    mutexWriters->acquire(threadName);
    nbWriters++;
    if (nbWriters == 1) {
        reader->acquire(threadName);
    }
    mutexWriters->release();
    writer->acquire(threadName); // si un rédacteur arrive alors que le premier lecteur est en train d'accéder
}

void ReaderWriterSemaphoreWritersPrio::unlockReading(const QString& threadName) {
    mutex->acquire(threadName);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        writer->release(); // permet aux rédacteurs de passer
    }
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);

    mutex->release();
}

void ReaderWriterSemaphoreWritersPrio::unlockWriting(const QString& threadName) {
    writer->release();
    mutexWriters->acquire(threadName);
    nbWriters--;
    if (nbWriters == 0) { // le dernier rédacteur
        reader->release(); // va libérer les lecteurs
    }
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    mutexWriters->release();
}


