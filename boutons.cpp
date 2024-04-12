#include "boutons.h"


Boutons::Boutons()
{
	io=acces_memoire(&shmid);
	if (io==NULL) printf("Erreur pas de mem sh\n");
}

void Boutons::boutons_initialiser()
{
	io->bouton_charge = 0;
	io->bouton_stop = 0;
}


int  Boutons::bouton_charge()
{

	if (io->bouton_charge==1)
	{
		bouton_charge_ap=1;
	}
	else
	{
		bouton_charge_ap=0;
	}
	return bouton_charge_ap;
}


int  Boutons::bouton_stop()
{

	if (io->bouton_stop==1)
	{
		bouton_stop_ap=1;
	}
	else 
	{
		bouton_stop_ap=0;
	}
	return bouton_stop_ap;
}
