#include <unistd.h>
#include <stdio.h>
#include "voyants.h"
	
Voyants::Voyants()
{
	io=acces_memoire(&shmid);
	if (io==NULL) printf("Erreur pas de mem sh\n");
}

void Voyants::voyants_initialiser()
{
	io->led_charge=OFF;
	io->led_dispo = VERT;
	io->led_defaut=OFF;
	io->led_prise=OFF;
	io->led_trappe=OFF;
}


void Voyants::set_dispo(led etatLed)
{
	io->led_dispo = etatLed ;
}


int Voyants::dispo()
{
	if(io->led_dispo==VERT)
	{
		disponible = 1;
	}
	return disponible ;
}

void Voyants::set_charge(led etatLed)
{
	io->led_charge = etatLed;
}


void Voyants::set_defaut(led etatLed)
{
	io->led_defaut = etatLed;
}

void Voyants::led_prise(led etatLed)
{
	io->led_prise = etatLed;
}

void Voyants::blink_charge()
{	
		if (io->timer_sec % 2 == 0)
		{
			io->led_charge = OFF ;
		}
		else 
		{
			io->led_charge = VERT;
		}
}


void Voyants::blink_defaut()
{
		if (io->timer_sec %2 == 0)
		{
			io->led_defaut = OFF ;
		}
		else 
		{
			io->led_defaut = ROUGE;
		}
}

void Voyants::led_trappe(led etatLed)
{
	io->led_trappe = etatLed;
}



