/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file waitinglogger.cpp
 *
 * Ce fichier définit les classes de logging, les méthodes de création/suppression/mise à jour des queues
 * et d'ajout/retrait des threads ayant accès à la RC.
 */
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
    /* Verifie que le thread n'est pas déjà dans la liste,
       si ce n'est pas le cas, alors on ajoute à la suite */
    if(!resourceAccesses.contains(threadName)){
        resourceAccesses.append(threadName);
    }
}

void ReadWriteLogger::removeResourceAccess(const QString &threadName)
{
    /* Verifie que le thread existe dans la liste,
       si c'est le cas, alors on le supprime de la liste */
    if(resourceAccesses.contains(threadName)){
        resourceAccesses.removeOne(threadName);
    }
}

WaitingQueue::WaitingQueue(QString objectName, QStringList threadNames){
    this->name = objectName;
    this->threadNames = threadNames;
}

void WaitingLogger::addWaiting(const QString &threadName, const QString &objectName){
    /* Parcours des files d'attente */
    for(WaitingQueue* queue : queues){
        /* On insère uniquement si il existe une file pour l'objet en question et
           et que le thread n'est pas dans la list */
        if(queue->name == objectName && !queue->threadNames.contains(threadName)){
            queue->threadNames.append(threadName);
        }
    }
    //Update de l'affichage (console)
    updateView();
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    /* Parcours des files d'attente */
    for(WaitingQueue* queue : queues){
        /* On supprime uniquement si il existe une file d'attente pour l'objet en question et
           et que le thread est présent dans la list */
        if(queue->name == objectName && queue->threadNames.contains(threadName)){
            queue->threadNames.removeOne(threadName);
        }
    }
}

void WaitingLogger::creatQueueObject(const QString &objectName){
    bool find = false;
    /* Parcours des files d'attente*/
    for(WaitingQueue* queue : queues){
        /* on cherche si il existe déjà une file d'attente pour l'objet en question */
        if(queue->name == objectName){
            find = true;
        }
    }
    /* Si la recherche n'a rien donné, on peut donc créer une nouvelle file d'attente */
    if(!find)
        queues.append(new WaitingQueue(objectName, QStringList()));
}

void WaitingLogger::rmQueueObject(const QString &objectName){
    WaitingQueue* queueToRm = NULL;
    /* Parcours des files d'attente*/
    for(WaitingQueue* queue : queues){
        /* on cherche la file d'attente à supprimer */
        if(queue->name == objectName){
            queueToRm = queue;
        }
    }
    /* Si la recherhe a donné un résultat, on peut donc supprimer la file d'attente pour l'objet en question */
    if(queueToRm)
        queues.removeOne(queueToRm);
}


void ReadWriteLogger::updateView()
{
    system("cls"); // Clear de la console (ne fonctionne que sur Windows !)
    cout << "<Enter> to continue <q>, <esc> to exit !" << endl;
    /* On parcors la liste des files d'attentes pour les affichers */
    for(WaitingQueue* queue : getQueues()){
        cout << queue->name.toStdString() << " : ";
        /* Parcours de la list des thread contenu dans une file d'attente */
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
