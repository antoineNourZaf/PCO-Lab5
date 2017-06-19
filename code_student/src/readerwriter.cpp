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
    delete writer;
    delete fifo;
    delete mutex;
}

void ReaderWriterSemaphoreEqualPrio::lockReading() {
    // le premier lecteur va vérouiller
    fifo->acquire();
    mutex->acquire();

    nbReader++;
    if (nbReader == 1) {
        writer->acquire(); // bloquer les rédacteurs
    }
    mutex->release();
    fifo->release(); // le suivant dans la fifo pourra tenter sa chance
}

void ReaderWriterSemaphoreEqualPrio::unlockReading() {
    mutex->acquire();
    nbReader--;
    if (nbReader == 0) {
        writer->release(); // le dernier lecteur permet debloque l'écriture
    }
    mutex.release();
}

void ReaderWriterSemaphoreEqualPrio::lockWriting() {
    fifo->acquire(); // le redacteur va bloquer tout ceux qui attendent dans la file
    writer->acquire();
}

void ReaderWriterSemaphoreEqualPrio::unlockWriting() {
    writer->release();
    fifo->release();
}
