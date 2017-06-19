/**
  * définitions des lecteurs et des rédacteurs
  */

#include "abstractreaderwriter.h"

// ABSTRACT
AbstractReaderWriter::AbstractReaderWriter(SynchroController* synchroController) {
    this->synCtr = synchroController;
}

AbstractReaderWriter::~AbstractReaderWriter() {

}


/*********************************************************
 * Priorité égale
 *********************************************************/

// sem equal prio
ReaderWriterSemaphoreEqualPrio::ReaderWriterSemaphoreEqualPrio(SynchroController* synchroController): AbstractReaderWriter(synchroController),
    mutex(new OSemaphore(1)), fifo(new OSemaphore(1)), writer(new OSemaphore(1)), nbReader(0){

}

ReaderWriterSemaphoreEqualPrio::~ReaderWriterSemaphoreEqualPrio() {
    delete writer;
    delete fifo;
    delete mutex;
}

void ReaderWriterSemaphoreEqualPrio::lockReading(const QString& threadName) {
    // le premier lecteur va vérouiller
    fifo->acquire(threadName);
    mutex->acquire(threadName);

    nbReader++;
    if (nbReader == 1) {
        writer->acquire(threadName); // bloquer les rédacteurs
    }
    mutex->release();
    fifo->release(); // le suivant dans la fifo pourra tenter sa chance
}

void ReaderWriterSemaphoreEqualPrio::unlockReading(const QString& threadName) {
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
}

void ReaderWriterSemaphoreEqualPrio::unlockWriting(const QString& threadName) {
    writer->release();
    fifo->release();
}





/*******************************************************
 * Writers Prio
 *******************************************************/
// semaphore writers prio
ReaderWriterSemaphoreWritersPrio::ReaderWriterSemaphoreWritersPrio(SynchroController* synchroController): AbstractReaderWriter(synchroController),
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
    mutex->release();
}

void ReaderWriterSemaphoreWritersPrio::unlockWriting(const QString& threadName) {
    writer->release();
    mutexWriters->acquire(threadName);
    nbWriters--;
    if (nbWriters == 0) { // le dernier rédacteur
        reader->release(); // va libérer les lecteurs
    }
    mutexWriters->release();
}



// hoare writers prio
ReaderWriterHoareWritersPrio::ReaderWriterHoareWritersPrio(SynchroController* synchroController) : AbstractReaderWriter(synchroController),
nbReaders(0), writingInProgress(false), nbWritersWaiting(0)
{

}

ReaderWriterHoareWritersPrio::~ReaderWriterHoareWritersPrio() {

}

void ReaderWriterHoareWritersPrio::lockReading(const QString& name) {
    monitorIn(name);
    if ((writingInProgress) || (nbWritersWaiting > 0)) { // les lecteurs n'ont pas la priorité sur les rédacteurs, donc on vérifie qu'aucun rédacteur n'attend
        wait(waitReading, name);
        signal(waitReading, name);
    }
    nbReaders++;
    monitorOut();
}

void ReaderWriterHoareWritersPrio::lockWriting(const QString& name) {
    monitorIn(name);
    if ((nbReaders > 0) || (writingInProgress)) {
        nbWritersWaiting++; // le rédacteur attent la libération d'un rédacteur ou d'un lecteur
        wait(waitWriting, name);
        nbWritersWaiting--;
    }
    writingInProgress = true;
    monitorOut();
}

void ReaderWriterHoareWritersPrio::unlockReading(const QString& name) {
    monitorIn(name);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        signal(waitWriting, name); // libère la rédaction
    }
    monitorOut();
}

void ReaderWriterHoareWritersPrio::unlockWriting(const QString& name) {
    monitorIn(name);
    writingInProgress = false;
    if (nbWritersWaiting >0) { // si d'autres rédacteurs attendent,
        signal(waitWriting, name); // ils ont la priorité
    }
    else {
        signal(waitReading, name); // sinon les lecteurs peuvent passer
    }
    monitorOut();
}





// MESA writersPrio
ReaderWriterMesaWritersPrio::ReaderWriterMesaWritersPrio(SynchroController* synchroController) : AbstractReaderWriter(synchroController),
mutex(new OMutex(WaitingLogger::getInstance())), waitReading(new OWaitCondition(WaitingLogger::getInstance())), waitWriting(new OWaitCondition(WaitingLogger::getInstance())),
  nbReaders(0), nbWaitingReaders(0), nbWaitingWriters(0), writingInProgress(false)
{

}

ReaderWriterMesaWritersPrio::~ReaderWriterMesaWritersPrio() {
    delete waitWriting;
    delete waitReading;
    delete mutex;
}

void ReaderWriterMesaWritersPrio::lockReading(const QString& name) {
    mutex->lock(name);
    if ((nbWaitingReaders > 0) || (writingInProgress)) {
        nbWaitingReaders++;
        waitReading->wait(&mutex);
    }
    else {
        nbReaders++;
    }
    mutex->unlock();
}

void ReaderWriterMesaWritersPrio::lockWriting(const QString& name) {
    mutex->lock(name);
    if ((nbReaders >0) || (writingInProgress)) {
        nbWaitingWriters++;
        waitWriting->wait(&mutex);
    }
    else {
        writingInProgress = true;
    }
    mutex->unlock();
}

void ReaderWriterMesaWritersPrio::unlockReading(const QString& name) {
    mutex->lock(name);
    nbReaders--;
    if (nbReaders == 0) {
        waitWriting->wakeOne();
    }
    mutex->unlock();
}

void ReaderWriterMesaWritersPrio::unlockWriting(const QString& name) {
    mutex->lock(name);
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
    mutex->unlock();
}
