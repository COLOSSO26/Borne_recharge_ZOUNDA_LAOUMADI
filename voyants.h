#ifndef VOYANTS_H
#define VOYANTS_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <mem_sh.h>
#include <donnees.h>

#include "timer.h"


class Voyants
{
	
  public : 
  	Voyants();
 	void voyants_initialiser();
	void set_dispo(led etatLed);
	int dispo();
	void set_charge(led etatLed);
	void blink_charge();
	void blink_defaut();
	void set_defaut(led etatLed);
	void led_prise(led etatLed);
	void led_trappe(led etatLed);
	
	entrees* io;
  	int shmid;
  
	int disponible = 0; 
	int diff=0;

	
};

#endif // Boutons_H
