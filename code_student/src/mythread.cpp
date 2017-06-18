#include "mythread.h"
#include <iostream>
using namespace std;

Mythread::Mythread(int threadId, AbstractReaderWriter* protcole)
{
    this->tid = threadId;
    this->readerWriter = protcole;
}

ReaderThread::ReaderThread(int threadId, AbstractReaderWriter* protcole):Mythread(threadId,protcole){

}

void ReaderThread::run(){
    while(1) {
    readerWriter->lockReading();
    cout << "Task " << tid << ": écriture" << endl;
    readerWriter->unlockReading();
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protcole): Mythread(threadId,protcole){
}

void WriterThread::run(){
    while(1) {
    readerWriter->lockWriting();
    cout << "Task " << tid << ": écriture" << endl;
    readerWriter->unlockWriting();
    }
}
