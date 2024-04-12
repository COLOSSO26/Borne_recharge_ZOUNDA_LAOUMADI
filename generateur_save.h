#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

#include <unistd.h>
#include <stdio.h>

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <mem_sh.h>
#include <donnees.h>

class Generateur_save
{
  public : 
  	Generateur_save();
 	void generer_PWM(pwm etatPWM);
	float tension();
	int ouvrir_fermer_AC(int valeur);
	
	entrees* io;
	int shmid;
	
	int valeur;
	int val_contacteur_AC;
};

#endif // GENERATEUR_SAVE_H
