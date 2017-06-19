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



// SEMAPHORE
ReaderWriterSemaphoreEqualPrio::ReaderWriterSemaphoreEqualPrio(SynchroController* synchroController): AbstractReaderWriter(synchroController),
    mutex(new OSemaphore(1)), fifo(new OSemaphore(1)), writer(new OSemaphore(1)), nbReader(0){

}

ReaderWriterSemaphoreEqualPrio::~ReaderWriterSemaphoreEqualPrio() {

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
