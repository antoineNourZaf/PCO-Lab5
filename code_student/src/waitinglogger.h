/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file waitinglogger.h
 *
 * Ces classes permetent de monitorer le processus et ses threads.
 * Une permière classe WaitingQueue contiendra une queue des threads
 * en attente sur un objet de synchronisation.
 *
 * La classe WaitingLogger est un singleton et contient la liste
 * de toutes les queues d'attente (WaitingQueue), et déclarera la méthode updateView()
 * Cette dernière est définie dans les classe dérivant WaitingLogger,
 * par exemple pour un affichage en console.
 *
 */
#ifndef WAITINGLOGGER_H
#define WAITINGLOGGER_H

#include <QStringList>
#include <QList>

class WaitingQueue
{
public:
    QString name;
    QStringList threadNames;
    WaitingQueue(QString objectName,QStringList threadNames);
};

class WaitingLogger
{
public:

    /**
     * @brief getInstance Returns the singleton
     * @return the only instance of WaitingLogger
     * This logger has to be a singleton, accessed by every synchronization
     * object
     */
    static WaitingLogger *getInstance();


    void addWaiting(const QString& threadName,const QString& objectName);

    void removeWaiting(const QString& threadName,const QString& objectName);

    void creatQueueObject(const QString& objectName);
    void rmQueueObject(const QString& objectName);


protected:
    WaitingLogger();

    QList<WaitingQueue *> getQueues() const;

    /**
     * @brief updateView Responsible for updating the view
     * This function should do what is required to update the view.
     * In this first version it could simply modify the display in
     * the terminal.
     */
    virtual void updateView() = 0;

    QList<WaitingQueue *> queues;

};


class ReadWriteLogger : public WaitingLogger
{
    friend WaitingLogger;

public:

    QStringList getResourceAccesses() const;

    /**
     * @brief addResourceAccess ajoute le thread à la liste de ceux ayant accès à la ressource critique
     * @param threadName le nom du thread
     */
    void addResourceAccess(const QString &threadName);

    /**
     * @brief removeResourceAccess retire le thread de la liste de ceux ayant accès à la RC
     * @param threadName le nom du thread
     */
    void removeResourceAccess(const QString &threadName);

protected:

    ReadWriteLogger();

    /**
     * @brief updateView Responsible for updating the view
     * This function should do what is required to update the view.
     * In this first version it could simply modify the display in
     * the terminal.
     */
    virtual void updateView();

    QStringList resourceAccesses; // la liste de ceux qui ont accès à la RC

};

#endif // WAITINGLOGGER_H
