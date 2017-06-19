#include "mythread.h"
#include <iostream>

using namespace std;

MyThread::MyThread(int threadId, AbstractReaderWriter *protocole,SynchroController *sync,const QString& nom)
{
    this->tid = threadId;
    this->readerWriter = protocole;
    this->syncCtr = sync;
    QThread::setObjectName(nom);
}

ReaderThread::ReaderThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync,const QString& nom) : MyThread(threadId,protocole,sync,nom) {

}

void ReaderThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << tid << ": lecture" << endl;
        syncCtr->pause();
        readerWriter->unlockReading(QThread::objectName());
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync, const QString& nom) : MyThread(threadId,protocole, sync,nom) {
}

void WriterThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockWriting(QThread::objectName());
        cout << "Task " << tid << ": écriture" << endl;
        syncCtr->pause();
        readerWriter->unlockWriting(QThread::objectName());
    }
}
