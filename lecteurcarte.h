#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <iostream>

#include "base_clients.h"
#include "voyants.h"
#include "boutons.h"
#include "timer.h"
#include "prise.h"
#include "generateur_save.h"

using namespace std;


class LecteurCarte
{

  public : 
  LecteurCarte();
	void initialiser();
	void lire_carte();

	Base_clients baseclient; // déclaration type base client
	Voyants voyants;		
	Boutons bouton;
	Timer timer;
	Prise prise;
	Generateur_save generateur;
	
	int choix_menu;
	int numero_carte;
	int duree=0;
	int appui_stop = 0;
	int appui_charge=0;
	int prise_branchee = 0;
	float valeur_tension;
	int etatContacteur_AC;
	int carte_debut;

};

#endif // LECTEURCARTE_H
