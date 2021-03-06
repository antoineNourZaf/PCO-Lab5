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
    virtual void lockReading(const QString& name)   = 0;
    virtual void lockWriting(const QString& name)   = 0;
    virtual void unlockReading(const QString& name) = 0;
    virtual void unlockWriting(const QString& name) = 0;
};

// **************************************************
// *                  Priorité egale
// ***************************************************
class ReaderWriterSemaphoreEqualPrio : public AbstractReaderWriter {
protected:

    OSemaphore* mutex; // accès à la nbReaders
    int nbReader;

    OSemaphore* fifo; // file d'attente pour tout le monde

    OSemaphore* writer; // le premier lecteur bloque les rédacteurs ET un rédacteur bloque tt le monde

public:

    ReaderWriterSemaphoreEqualPrio(SynchroController* synchroController);
    virtual ~ReaderWriterSemaphoreEqualPrio();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};

// **************************************************
// *             Redacteurs prioritaire
// **************************************************
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
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};



#endif // ABSTRACTREADERWRITER_H
