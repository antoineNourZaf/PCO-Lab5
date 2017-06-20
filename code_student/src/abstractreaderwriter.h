#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "waitinglogger.h"
#include "osemaphore.h"
#include "ohoaremonitor.h"

class AbstractReaderWriter {
protected:
    WaitingLogger* RWLogger;
public:
    AbstractReaderWriter(WaitingLogger* logger);
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

    ReaderWriterSemaphoreEqualPrio(WaitingLogger* logger);
    virtual ~ReaderWriterSemaphoreEqualPrio();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};

class ReaderWriterHoare;


// **************************************************
// *             Redacteurs prioritaire
// **************************************************

/**
 * @brief The ReaderWriterSemaphoreWritersPrio class
 */
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

    ReaderWriterSemaphoreWritersPrio(WaitingLogger* logger);
    virtual ~ReaderWriterSemaphoreWritersPrio();
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
    ReaderWriterHoareWritersPrio(WaitingLogger* logger);
    ~ReaderWriterHoareWritersPrio();

    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};




#endif // ABSTRACTREADERWRITER_H
