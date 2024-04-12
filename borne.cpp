#include <iostream>
#include "memoire_borne.h"
#include "donnees_borne.h"

#include "lecteurcarte.h"

int main()
{

    LecteurCarte lecteurcarte;
    Voyants voyants;
    Boutons bouton;
    
	lecteurcarte.initialiser();
	voyants.voyants_initialiser();
	bouton.boutons_initialiser();
	
    while (1)
    {
        lecteurcarte.lire_carte();
    }

}
