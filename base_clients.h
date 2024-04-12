#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <lcarte.h>

class Base_clients
{
  public : 
	bool authentifier(int num_carte);
	void reprise(int num_carte, int carte_debut);
	void menu(int* choix);
	void afficherClients();
	void ajouterClient();
	void effacerClient();
	void modifierClients();
};

#endif // LECTEURCARTE_H
