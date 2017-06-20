#include "mythread.h"
#include <iostream>

using namespace std;

MyThread::MyThread(int threadId, AbstractReaderWriter *protocole,SynchroController *sync)
{
    this->tid = threadId;
    this->readerWriter = protocole;
    this->syncCtr = sync;
}

ReaderThread::ReaderThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(threadId,protocole,sync) {
    QThread::setObjectName("Reader" + QString::number(threadId));

}

void ReaderThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << tid << ": lecture" << endl;
        //
        syncCtr->pause();
        readerWriter->unlockReading(QThread::objectName());
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(threadId,protocole, sync) {
    QThread::setObjectName("Writer" + QString::number(threadId));
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
