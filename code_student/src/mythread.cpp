#include "mythread.h"
#include <iostream>

using namespace std;

int MyThread::compteur = 0;

MyThread::MyThread( AbstractReaderWriter *protocole)
{
    this->readerWriter = protocole;
    compteur++;
}

ReaderThread::ReaderThread(AbstractReaderWriter* protocole) : MyThread(protocole) {
    QThread::setObjectName("Reader" + QString::number(compteur));
}

void ReaderThread::run() {

    while (true) {
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        readerWriter->unlockReading(QThread::objectName());
    }
}

WriterThread::WriterThread(AbstractReaderWriter* protocole) : MyThread(protocole) {
    QThread::setObjectName("Writer" + QString::number(compteur));
}

void WriterThread::run() {

    while (true) {
        readerWriter->lockWriting(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        readerWriter->unlockWriting(QThread::objectName());
    }
}
