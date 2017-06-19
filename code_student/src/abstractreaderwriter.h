#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "synchrocontroller.h"
#include "osemaphore.h"

class AbstractReaderWriter {
protected:
    SynchroController* synCtr;
public:
    AbstractReaderWriter(SynchroController* synchroController);
    virtual ~AbstractReaderWriter();
    virtual void lockReading()   = 0;
    virtual void lockWriting()   = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};

// ===============================================


class ReaderWriterSemaphoreEqualPrio : public AbstractReaderWriter {
protected:
    OSemaphore* mutex; // accès à la nbReaders
    int nbReader;

    OSemaphore* fifo; // file d'attente pour tout le monde

    OSemaphore* writer; // le premier lecteur bloque les rédacteurs ET un rédacteur bloque tt le monde

public:
    ReaderWriterSemaphoreEqualPrio(SynchroController* synchroController);
    virtual ~ReaderWriterSemaphoreEqualPrio();
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};

class ReaderWriterSemaphoreWritersPrio : public AbstractReaderWriter {
protected:
    OSemaphore* mutexReaders;
    OSemaphore* mutexWriters;
    OSemaphore* writer;
    OSemaphore* reader;
    OSemaphore* mutex;
    int nbReaders;
    int nbWriters;

public:
    ReaderWriterSemaphoreWritersPrio(SynchroController* synchroController);
    virtual ~ReaderWriterSemaphoreWritersPrio();
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};


#endif // ABSTRACTREADERWRITER_H
