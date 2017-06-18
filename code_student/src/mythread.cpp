#include "mythread.h"
#include <iostream>
using namespace std;

MyThread::MyThread(int threadId, AbstractReaderWriter *protocole,SynchroController *sync)
{
    this->tid = threadId;
    this->readerWriter = protocole;
    this->syncCtr = sync;
}

MyThread::MyThread(int threadId, AbstractReaderWriter* protocole, const QString& nom) {

    this->tid = threadId;
    this->readerWriter = protocole;
    QThread::setObjectName(nom);

}

ReaderThread::ReaderThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(threadId,protocole,sync) {

}

void ReaderThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockReading();
        cout << "Task " << tid << ": lecture" << endl;
        syncCtr->pause();
        readerWriter->unlockReading();
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protocole, SynchroController *sync) : MyThread(threadId,protocole, sync) {
}

void WriterThread::run() {

    while (true) {
        syncCtr->pause();
        readerWriter->lockWriting();
        cout << "Task " << tid << ": écriture" << endl;
        syncCtr->pause();
        readerWriter->unlockWriting();
    }
}
