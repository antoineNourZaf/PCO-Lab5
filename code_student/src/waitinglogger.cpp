#include "waitinglogger.h"
#include <iostream>
#include <stdlib.h>

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
    if(!resourceAccesses.contains(threadName)){
        resourceAccesses.append(threadName);
    }
}

void ReadWriteLogger::removeResourceAccess(const QString &threadName)
{
    if(resourceAccesses.contains(threadName)){
        resourceAccesses.removeOne(threadName);
    }
}

WaitingQueue::WaitingQueue(QString objectName, QStringList threadNames){
    this->name = objectName;
    this->threadNames = threadNames;
}

void WaitingLogger::addWaiting(const QString &threadName, const QString &objectName){
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName && !queue->threadNames.contains(threadName)){
            queue->threadNames.append(threadName);
        }
    }
    updateView();
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName && queue->threadNames.contains(threadName)){
            queue->threadNames.removeOne(threadName);
        }
    }
}

void WaitingLogger::creatQueueObject(const QString &objectName){
    bool find = false;
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName){
            find = true;
        }
    }
    if(!find)
        queues.append(new WaitingQueue(objectName, QStringList()));
}

void WaitingLogger::rmQueueObject(const QString &objectName){
    WaitingQueue* queueToRm = NULL;
    for(WaitingQueue* queue : queues){
        if(queue->name == objectName){
            queueToRm = queue;
        }
    }
    if(queueToRm)
        queues.removeOne(queueToRm);
}


void ReadWriteLogger::updateView()
{
    system("cls");
    cout << "<Enter> to continue <q>, <esc> to exit !" << endl;
    for(WaitingQueue* queue : getQueues()){
        cout << queue->name.toStdString() << " : ";
        for(QString thread :queue->threadNames){
            std::cout<<thread.toStdString()<<" ";
        }
        std::cout<<endl;
    }
    std::cout<< "In resource : ";
    for(QString threadRes : getResourceAccesses()){
        std::cout << threadRes.toStdString() << " ";
    }
    std::cout<<std::endl;

}
