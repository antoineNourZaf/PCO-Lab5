#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"


class MyThread : public QThread {
protected:

    AbstractReaderWriter *readerWriter;
public:

    int tid;
    MyThread(int threadId, AbstractReaderWriter* protocole);
    MyThread(int threadId, AbstractReaderWriter* protocole, const QString& nom);
};


class ReaderThread : public MyThread {
public:
    ReaderThread(int threadId, AbstractReaderWriter* protcole);
    void run();
};

class WriterThread : public MyThread {
public:
    WriterThread(int threadId, AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
