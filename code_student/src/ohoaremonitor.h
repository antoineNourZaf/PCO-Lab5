/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file ohoaremonitor.h
 *
 * Cette classe déclare un moniteur de Hoare,
 * cependant les méhtode de synchronisation vont permettre le monitoring du processus
 * Ces méthodes prennent alors le nom du thread qui les appelle.
 *
 */
#ifndef OHOAREMONITOR_H
#define OHOAREMONITOR_H

#include "osemaphore.h"

class OHoareMonitor
{
private:
    OSemaphore* monitorMutex;
    OSemaphore* monitorSignal;
    int monitorNbSignal;
protected:

    class Condition {
        friend OHoareMonitor;
    public:
        Condition();
    private:
        OSemaphore*  waitingSem;
        int nbWaiting;
    };

public:
    OHoareMonitor();
    ~OHoareMonitor();

    /**
     * This function has to be called at the beginning of each function being
     * an entry point to the monitor.
     */
    void monitorIn(const QString& threadName);

    /**
     * This function has to be called at the end of each function being
     * an entry point to the monitor.
     */
    void monitorOut();

    /**
     * This function implements the waiting on a condition, as defined by Hoare.
     * When the thread is waken by a signal, it continues with the mutual
     * exclusion.
     */
    void wait(Condition &cond, const QString& threadName);

    /**
     * This function implements the signaling of a condition, as defined by
     * Hoare. If no thread is waiting for the condition, then nothing happens,
     * but if there is one the thread calling signal is suspended, waiting for
     * the other one to finish.
     */
    void signal(Condition &cond, const QString& threadName);

};

#endif // OHOAREMONITOR_H
