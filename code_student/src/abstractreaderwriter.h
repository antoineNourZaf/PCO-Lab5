#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "synchrocontroller.h"
#include "waitinglogger.h"
#include "osemaphore.h"
#include "ohoaremonitor.h"

class AbstractReaderWriter {
public:
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
    int nbReader;
    OSemaphore* mutex; // accès à la nbReaders
    OSemaphore* fifo; // file d'attente pour tout le monde
    OSemaphore* writer; // le premier lecteur bloque les rédacteurs ET un rédacteur bloque tt le monde

public:

    ReaderWriterSemaphoreEqualPrio();
    virtual ~ReaderWriterSemaphoreEqualPrio();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};

// **************************************************
// *             Redacteurs prioritaire
// **************************************************

/**
 * @brief The ReaderWriterSemaphoreWritersPrio class
 */
class RWSemaphorePrioWriter : public AbstractReaderWriter {
protected:
    OSemaphore* mutexReaders;
    OSemaphore* mutexWriters;
    OSemaphore* writer;
    OSemaphore* reader;
    OSemaphore* mutex;
    int nbReaders, nbWriters;

public:
    RWSemaphorePrioWriter();
    virtual ~RWSemaphorePrioWriter();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};


/**
 * @brief The ReaderWriterHoarWritersPrio class
 */
class ReaderWriterHoareWritersPrio : public AbstractReaderWriter, public OHoareMonitor {
protected:
    Condition waitWriting;
    Condition waitReading;
    int nbReaders;
    bool writingInProgress;
    int nbWritersWaiting;

public:
    ReaderWriterHoareWritersPrio();
    ~ReaderWriterHoareWritersPrio();

    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};




#endif // ABSTRACTREADERWRITER_H
