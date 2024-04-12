#ifndef BOUTONS_H
#define BOUTONS_H

#include <unistd.h>
#include <stdio.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <mem_sh.h>
#include <donnees.h>

class Boutons
{
	
  public : 
  	Boutons();
	int bouton_charge();
	int bouton_stop();
	void boutons_initialiser();
	
	entrees* io;
	int shmid;
	
	int bouton_stop_ap=0;
	int bouton_charge_ap=0;
};

#endif // Boutons_H
