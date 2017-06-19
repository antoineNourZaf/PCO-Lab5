#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

// forward declaration
class AbstractReaderWriter;


class MyThread : public QThread {
protected:
    SynchroController *syncCtr;
    AbstractReaderWriter *readerWriter;
    int tid;
public:

    MyThread(int threadId, AbstractReaderWriter *protocole,SynchroController *sync,const QString& nom);

};


class ReaderThread : public MyThread {
public:
    ReaderThread(int threadId, AbstractReaderWriter* protcole, SynchroController *sync, const QString& nom);
    void run();
};

class WriterThread : public MyThread {
public:
    WriterThread(int threadId, AbstractReaderWriter* protcole, SynchroController *sync, const QString& nom);
    void run();
};

#endif // MYTHREAD_H
