#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class MyThread : public QThread {
protected:

    SynchroController *syncCtr;
    AbstractReaderWriter *readerWriter;
    static int compteur;

public:

    MyThread(AbstractReaderWriter *protocole,SynchroController *sync);

};


class ReaderThread : public MyThread {
public:

    ReaderThread(AbstractReaderWriter* protcole, SynchroController *sync);
    void run();
};

class WriterThread : public MyThread {
public:

    WriterThread(AbstractReaderWriter* protcole, SynchroController *sync);
    void run();
};

#endif // MYTHREAD_H
