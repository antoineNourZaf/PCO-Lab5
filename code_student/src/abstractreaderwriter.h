#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

class AbstractReaderWriter {
public:
    AbstractReaderWriter(int tpi, AbstractReaderWriter*);
    virtual ~AbstractReaderWriter();
    virtual void lockReading() = 0;
    virtual void lockWriting() = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};

class ReaderWriterMutex : public AbstractReaderWriter {

};

class ReaderWriterSemaphore : public AbstractReaderWriter {

};


#endif // ABSTRACTREADERWRITER_H
