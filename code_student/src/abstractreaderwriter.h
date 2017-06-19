#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "osemaphore.h"
#include "omutex.h"
#include "synchrocontroller.h"

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



class ReaderWriterMutex : public AbstractReaderWriter {
public:
    virtual ~ReaderWriterMutex();
    ReaderWriterMutex(SynchroController* synchroController);
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};


// ===============================================


class ReaderWriterSemaphore : public AbstractReaderWriter {
protected:
    OSemaphore mutex; // accès à la nbReaders
    int nbReader;

    OSemaphore fifo; // file d'attente pour tout le monde

    OSemaphore writer; // le premier lecteur bloque les rédacteurs ET un rédacteur bloque tt le monde

public:
    ReaderWriterSemaphore(SynchroController* synchroController);
    virtual ~ReaderWriterSemaphore();
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};


#endif // ABSTRACTREADERWRITER_H
