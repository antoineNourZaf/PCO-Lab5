/**
  * définitions des lecteurs et des rédacteurs
  */

#include "abstractreaderwriter.h"
#include <iostream>

// ABSTRACT
AbstractReaderWriter::AbstractReaderWriter(WaitingLogger* logger) {
    this->RWLogger = logger;
}

AbstractReaderWriter::~AbstractReaderWriter() {

}


/******************** IMPLEMENTATIONS SEMAPHORES **************************
/*********************************************************
 * Priorité égale
 *********************************************************/

ReaderWriterSemaphoreEqualPrio::ReaderWriterSemaphoreEqualPrio(WaitingLogger* logger): AbstractReaderWriter(logger),
    fifo(new OSemaphore(1)),mutex(new OSemaphore(1)),writer(new OSemaphore(1)), nbReader(0){

}

ReaderWriterSemaphoreEqualPrio::~ReaderWriterSemaphoreEqualPrio() {
    delete writer;
    delete fifo;
    delete mutex;
}

void ReaderWriterSemaphoreEqualPrio::lockReading(const QString& threadName) {
    std::cout << "Rsc:" <<threadName.toStdString() << std::endl;
    // le premier lecteur va vérouiller
    fifo->acquire(threadName);
    mutex->acquire(threadName);

    nbReader++;
    if (nbReader == 1) {
        writer->acquire(threadName); // bloquer les rédacteurs
    }
    mutex->release();
    fifo->release(); // le suivant dans la fifo pourra tenter sa chance

    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterSemaphoreEqualPrio::unlockReading(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);

    mutex->acquire(threadName);
    nbReader--;
    if (nbReader == 0) {
        writer->release(); // le dernier lecteur permet debloque l'écriture
    }
    mutex->release();
}

void ReaderWriterSemaphoreEqualPrio::lockWriting(const QString& threadName) {
    fifo->acquire(threadName); // le redacteur va bloquer tout ceux qui attendent dans la file
    writer->acquire(threadName);
    //Accès ressources
    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterSemaphoreEqualPrio::unlockWriting(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);

    writer->release();
    fifo->release();
}

/*******************************************************
 * EM Writers Prio
 *******************************************************/

ReaderWriterSemaphoreWritersPrio::ReaderWriterSemaphoreWritersPrio(WaitingLogger* logger): AbstractReaderWriter(logger),
    mutexReaders(new OSemaphore(1)), mutexWriters(new OSemaphore(1)), writer(new OSemaphore(1)), reader(new OSemaphore(1)), mutex(new OSemaphore(1)), nbReaders(0), nbWriters(0)
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
    mutex->release(); // relachement de la lecteur
    reader->release();
    mutexReaders->release();
    //Accès ressources
    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterSemaphoreWritersPrio::lockWriting(const QString& threadName) {
    mutexWriters->acquire(threadName);
    nbWriters++;
    if (nbWriters == 1) {
        reader->acquire(threadName);
    }
    mutexWriters->release();
    writer->acquire(threadName); // si un rédacteur arrive alors que le premier lecteur est en train d'accéder
    //Accès ressources
    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterSemaphoreWritersPrio::unlockReading(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);

    mutex->acquire(threadName);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        writer->release(); // permet aux rédacteurs de passer
    }
    mutex->release();
}

void ReaderWriterSemaphoreWritersPrio::unlockWriting(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);

    writer->release();
    mutexWriters->acquire(threadName);
    nbWriters--;
    if (nbWriters == 0) { // le dernier rédacteur
        reader->release(); // va libérer les lecteurs
    }
    mutexWriters->release();
}




ReaderWriterHoareWritersPrio::ReaderWriterHoareWritersPrio(WaitingLogger* WaitingLogger) : AbstractReaderWriter(WaitingLogger),
nbReaders(0), writingInProgress(false), nbWritersWaiting(0)
{

}

ReaderWriterHoareWritersPrio::~ReaderWriterHoareWritersPrio() {

}

void ReaderWriterHoareWritersPrio::lockReading(const QString& threadName) {
    monitorIn(threadName);
    if ((writingInProgress) || (nbWritersWaiting > 0)) { // les lecteurs n'ont pas la priorité sur les rédacteurs, donc on vérifie qu'aucun rédacteur n'attend
        wait(waitReading, threadName);
        signal(waitReading, threadName);
    }
    nbReaders++;
    monitorOut();
    // Acces ressrouces
    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterHoareWritersPrio::lockWriting(const QString& threadName) {
    monitorIn(threadName);
    if ((nbReaders > 0) || (writingInProgress)) {
        nbWritersWaiting++; // le rédacteur attent la libération d'un rédacteur ou d'un lecteur
        wait(waitWriting, threadName);
        nbWritersWaiting--;
    }
    writingInProgress = true;
    monitorOut();
    //Accès ressources
    ((ReadWriteLogger*)RWLogger)->addResourceAccess(threadName);
}

void ReaderWriterHoareWritersPrio::unlockReading(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);

    monitorIn(threadName);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        signal(waitWriting, threadName); // libère la rédaction
    }
    monitorOut();
}

void ReaderWriterHoareWritersPrio::unlockWriting(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*)RWLogger)->removeResourceAccess(threadName);
    monitorIn(threadName);
    writingInProgress = false;
    if (nbWritersWaiting >0) { // si d'autres rédacteurs attendent,
        signal(waitWriting, threadName); // ils ont la priorité
    }
    else {
        signal(waitReading, threadName); // sinon les lecteurs peuvent passer
    }
    monitorOut();
}

