#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"


class Mythread : public QThread {
protected:

    AbstractReaderWriter *readerWriter;
public:

    int tid;
    Mythread(int threadId, AbstractReaderWriter* protocole);
};


class ReaderThread : public Mythread {
public:
    ReaderThread(int threadId, AbstractReaderWriter* protcole);
    void run();
};

class WriterThread : public Mythread {
public:
    WriterThread(int threadId, AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
