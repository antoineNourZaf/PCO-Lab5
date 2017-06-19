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
ReaderWriterSemaphore::ReaderWriterSemaphore(SynchroController* synchroController): AbstractReaderWriter(synchroController),
    mutex(new OSemaphore(1)), fifo(new OSemaphore(1)), writer(new OSemaphore(1)), nbReader(0){

}

ReaderWriterSemaphore::~ReaderWriterSemaphore() {

}

void ReaderWriterSemaphore::lockReading() {
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

void ReaderWriterSemaphore::unlockReading() {
    mutex->acquire();
    nbReader--;
    if (nbReader == 0) {
        writer->release(); // le dernier lecteur permet debloque l'écriture
    }
    mutex.release();
}

void ReaderWriterSemaphore::lockWriting() {
    fifo->acquire(); // le redacteur va bloquer tout ceux qui attendent dans la file
    writer->acquire();
}

void ReaderWriterSemaphore::unlockWriting() {
    writer->release();
    fifo->release();
}
