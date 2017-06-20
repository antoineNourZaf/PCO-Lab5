#include "mythread.h"
#include <iostream>

using namespace std;

int MyThread::compteur = 0;

MyThread::MyThread( AbstractReaderWriter *protocole,SynchroController *sync)
{
    this->readerWriter = protocole;
    this->syncCtr = sync;
    compteur++;
}

ReaderThread::ReaderThread(AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(protocole,sync) {
    QThread::setObjectName("Reader" + QString::number(compteur));
}

void ReaderThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;

        syncCtr->pause();
        readerWriter->unlockReading(QThread::objectName());
    }
}

WriterThread::WriterThread(AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(protocole, sync) {
    QThread::setObjectName("Writer" + QString::number(compteur));
}

void WriterThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockWriting(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        syncCtr->pause();
        readerWriter->unlockWriting(QThread::objectName());
    }
}
