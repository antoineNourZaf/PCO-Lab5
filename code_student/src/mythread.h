#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class MyThread : public QThread {
protected:
    AbstractReaderWriter *readerWriter;
    static int compteur;

public:

    MyThread(AbstractReaderWriter *protocole);

};


class ReaderThread : public MyThread {
public:

    ReaderThread(AbstractReaderWriter* protcole);
    void run();
};

class WriterThread : public MyThread {
public:

    WriterThread(AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
