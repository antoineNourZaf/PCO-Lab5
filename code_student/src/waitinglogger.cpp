#include "waitinglogger.h"

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
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName){
            if(!queue->threadNames.contains(threadName))
                queue->threadNames.append(threadName);
        }
    }
    queues.append(new WaitingQueue(objectName, QStringList()<<threadName));

    //updateView();
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName){
            if(queue->threadNames.contains(threadName)){
                queue->threadNames.removeOne(threadName);
                if(queue->threadNames.size()==0){
                  //supprimer queue
                }
            }
        }
    }

}

void ReadWriteLogger::updateView()
{

}
