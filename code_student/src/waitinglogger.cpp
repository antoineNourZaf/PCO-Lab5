#include "waitinglogger.h"
#include <iostream>

using namespace std;

WaitingLogger::WaitingLogger()
{

}

WaitingLogger *WaitingLogger::getInstance()
{
    static WaitingLogger *instance = new ReadWriteLogger();
    return instance;
}

QList<WaitingQueue *> WaitingLogger::getQueues() const
{
    return queues;
}


QStringList ReadWriteLogger::getResourceAccesses() const
{
    return resourceAccesses;
}

ReadWriteLogger::ReadWriteLogger()
{

}

void ReadWriteLogger::addResourceAccess(const QString &threadName)
{

}

void ReadWriteLogger::removeResourceAccess(const QString &threadName)
{

}

WaitingQueue::WaitingQueue(QString objectName, QStringList threadNames){
    this->name = objectName;
    this->threadNames = threadNames;
}

void WaitingLogger::addWaiting(const QString &threadName, const QString &objectName){
    std::cout << "ADDWAITING" << std::endl;
    bool find = false;
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName && !queue->threadNames.contains(threadName)){
            queue->threadNames.append(threadName);
            find = true;
        }
    }
    if(!find){
        queues.append(new WaitingQueue(objectName, QStringList()<<threadName));
    }

    updateView();
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    std::cout << "RMWAITING" << std::endl;
    WaitingQueue* queueToRm = NULL;
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName){
            if(queue->threadNames.contains(threadName)){
                queue->threadNames.removeOne(threadName);
                if(queue->threadNames.size()==0){
                  queueToRm=queue;
                }
            }
        }
    }

    if(queueToRm != NULL){
        queues.removeOne(queueToRm);
    }
}

void ReadWriteLogger::updateView()
{
     for(WaitingQueue* queue : getQueues()){
         cout << queue->name.toStdString() << " : ";
         for(QString thread :queue->threadNames){
             std::cout<<thread.toStdString()<<" ";
         }
         std::cout<<endl;
     }
}
