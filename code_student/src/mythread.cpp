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
    int nbtour = 3;
    while (true) {
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        usleep((int)((float)50000*rand()/(RAND_MAX+1.0)));
        readerWriter->unlockReading(QThread::objectName());
        nbtour--;
    }
}

WriterThread::WriterThread(AbstractReaderWriter* protocole) : MyThread(protocole) {
    QThread::setObjectName("Writer" + QString::number(compteur));
}

void WriterThread::run() {
    int nbtour = 3;
    while (true) {
        readerWriter->lockWriting(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        usleep((int)((float)50000*rand()/(RAND_MAX+1.0)));
        readerWriter->unlockWriting(QThread::objectName());
        nbtour--;
    }
}
