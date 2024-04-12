#include "generateur_save.h"


Generateur_save::Generateur_save()
{
	io=acces_memoire(&shmid);
	if (io==NULL) printf("Erreur pas de mem sh\n");
}

void Generateur_save::generer_PWM(pwm etatPWM)
{
	io->gene_pwm = etatPWM;
}


float Generateur_save::tension()
{
	return io->gene_u;	
}

int Generateur_save::ouvrir_fermer_AC(int valeur)
{
	io->contacteur_AC = valeur;
	
	return io->contacteur_AC;
}
