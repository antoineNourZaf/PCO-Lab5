#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

class AbstractReaderWriter {
public:
    AbstractReaderWriter();
    virtual ~AbstractReaderWriter();
    virtual void lockReading() = 0;
    virtual void lockWriting() = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};

class ReaderWriterMutex : public AbstractReaderWriter {
public:
    ReaderWriterMutex();
    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
};

class ReaderWriterSemaphore : public AbstractReaderWriter {
public:
    ReaderWriterSemaphore();
    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
};


#endif // ABSTRACTREADERWRITER_H
