#include "mythread.h"
#include <iostream>
using namespace std;

Mythread::Mythread(int threadId, AbstractReaderWriter* protocole)
{
    this->tid = threadId;
    this->readerWriter = protocole;
}

Mythread::Mythread(int threadId, AbstractReaderWriter* protocole, const QString& nom) {

    this->tid = threadId;
    this->readerWriter = protocole;
    QThread::setObjectName(nom);

}

ReaderThread::ReaderThread(int threadId, AbstractReaderWriter* protocole) : Mythread(threadId,protocole) {

}

void ReaderThread::run() {

    while (true) {

        readerWriter->lockReading();
        cout << "Task " << tid << ": lecture" << endl;
        readerWriter->unlockReading();
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protocole) : Mythread(threadId,protocole) {
}

void WriterThread::run() {

    while (true) {

        readerWriter->lockWriting();
        cout << "Task " << tid << ": écriture" << endl;
        readerWriter->unlockWriting();
    }
}
