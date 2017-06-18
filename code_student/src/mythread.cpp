#include "mythread.h"

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
    std::cout << "Task " << tid << ": écriture" << std::endl;
    readerWriter->unlockReading();
    }
}

WriterThread::WriterThread(int threadId, AbstractReaderWriter* protcole): Mythread(threadId,protcole){
}

void WriterThread::run(){
    while(1) {
    readerWriter->lockWriting();
    std::cout << "Task " << tid << ": écriture" << std::endl;
    readerWriter->unlockWriting();
    }
}
