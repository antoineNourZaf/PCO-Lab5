#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "osemaphore.h"

class AbstractReaderWriter {
public:
    AbstractReaderWriter(int tpi, AbstractReaderWriter*);
    virtual ~AbstractReaderWriter();
    virtual void lockReading() = 0;
    virtual void lockWriting() = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};


/**
 * @brief The ReaderWriterMutex class
 * Priorité lecteurs
 */
class ReaderWriterMutex : public AbstractReaderWriter {
protected:
    OSemaphore mutex; // accès à la ressource

    OSemaphore readerBlocker; // file d'attente des lecteurs
    int nbReader;

    OSemaphore writerBlocker; // file d'attente des rédacteurs
    int nbWriters;

public:
    virtual ~AbstractReaderWriter();
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};



class ReaderWriterSemaphore : public AbstractReaderWriter {
protected:

    virtual ~AbstractReaderWriter();
    virtual void lockReading();
    virtual void lockWriting();
    virtual void unlockReading();
    virtual void unlockWriting();
};


#endif // ABSTRACTREADERWRITER_H
