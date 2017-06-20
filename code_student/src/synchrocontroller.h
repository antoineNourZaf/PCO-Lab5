/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file synchrocontroller.h
 *
 * Cette classe assure le contrôle du flux du processus.
 * Elle permet de pauser l'exécution du programme et de la continuer,
 * en se basant sur une sémpahore.
 *
 */
#ifndef SYNCHROCONTROLLER_H
#define SYNCHROCONTROLLER_H

#include <QSemaphore>

class SynchroController
{
    QSemaphore* semaphore;
    SynchroController();
public:
    static SynchroController *getInstance();

    void pause();

    void resume();
};

#endif // SYNCHROCONTROLLER_H
