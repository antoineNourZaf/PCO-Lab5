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


// SEMAPHORES
// SEM Equal Prio
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

// SEM Writers Prio

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

}

void ReaderWriterSemaphoreWritersPrio::unlockReading(const QString& threadName) {

}

void ReaderWriterSemaphoreWritersPrio::unlockWriting(const QString& threadName) {

}


