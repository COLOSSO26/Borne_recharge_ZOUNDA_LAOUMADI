#ifndef TIMER_H
#define TIMER_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <mem_sh.h>
#include <donnees.h>



class Timer
{
	entrees* io;
  	int shmid;
  	
  	public:
  	Timer();
	void timer_raz();
	int timer_valeur();
	
	int depart_timer ;
  	
};

#endif 
