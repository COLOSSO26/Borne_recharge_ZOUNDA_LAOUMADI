#include <iostream>
#include <vector>
#include "base_clients.h"

using namespace std;

//  DEFINE CODE ANSI
#define RESET   "\033[0m"        // code pour reset couleur par defaut et empecher de se propager ailleurs
#define GRAS    "\033[1m"
#define ROUGE   "\033[31m"
#define VERT   "\033[32m"
#define BLEU    "\033[34m"
#define CYAN    "\033[36m"

vector<int> num_clients = {24, 18, 16, 14, 2};    //vecteur pour stocker les numéros clients


bool Base_clients::authentifier(int num_carte)
{
	for(unsigned int i=0; i < num_clients.size(); i++)
	{
		if(num_clients[i]==num_carte)
		{
			cout<<VERT<<"Authentification réussie !"<<RESET<<endl;
			return true;
		}
		
	}
	// si num_carte = 0, on écrit rien car avant reprise on réinitialise num_carte à 0. Donc évite d'afficher erreur sans avoir encore saisi le numéro
		if (num_carte==0) 
		{
			return false;
		}  
		else 
		{
			cout<<ROUGE<<"Erreur, carte non enregistrée dans la base des clients"<<RESET<<endl<<endl;
			return false;
		}
		
}

void Base_clients::reprise(int numero_carte, int carte_debut)
{
	cout<<endl;
	cout<<"Réinsérer votre carte pour récuperer votre véhicule"<<endl;
    	cout<<endl;
         					
    while(numero_carte != carte_debut) // tant que carte pas reconnue
    {
		attente_insertion_carte(); // attente insertion
		numero_carte = lecture_numero_carte(); // lecture de la carte
		cout<<"Numéro de la carte : "<<numero_carte<<endl;
		if (numero_carte != carte_debut)
		{
			cout<<ROUGE<<"Erreur, carte non enregistrée dans la base des clients"<<RESET<<endl<<endl;
		}
	}
	cout<<VERT<<"Authentification réussie !"<<RESET<<endl;
    	cout<<"Veuillez retirer votre carte"<<endl;
    	attente_retrait_carte();
	cout<<endl;
}


void Base_clients::menu(int* choix)
 { 
 	cout<<endl;
    cout  << ROUGE<<"\t\t\t\t" <<GRAS<<" MENU BORNE DE RECHARGE"<< RESET<<endl<<endl;
    cout <<GRAS<< "\t\t\t 1. " << RESET << CYAN <<"Recharger véhicule" << RESET <<endl;
    cout <<GRAS<< "\t\t\t 2. " << RESET << CYAN <<"Session Administrateur" <<RESET << endl<<endl;
    cout << "SAISISSEZ VOTRE CHOIX : ";
    cin >> *choix;
    cout<<endl;
}


void Base_clients::afficherClients()
{
    cout<<GRAS<<"CLIENTS ADHÉRENTS"<<RESET<<endl;
    for (unsigned int i = 0; i < num_clients.size(); i++)
    {
        cout << "Client "<<i+1<<" = "<< CYAN<<num_clients[i] <<RESET<<endl; // i+1 pour afficher à partir de client 1
    }
    cout << endl;
}

void Base_clients::ajouterClient()
{
    int num_carte;
    //Base_clients::afficherClients(); //afficher les numéros carte pour savoir quel numéro ajouté
    cout << "Veuillez saisir le numéro du client à ajouter : ";
    cin >> num_carte;
    
    for (unsigned int i = 0; i < num_clients.size(); i++)
    {
        if (num_clients[i] == num_carte)
        {
            cout <<ROUGE<< "Impossible, client déjà existant" <<RESET<< endl<<endl;
            return;
        }
    }     
    num_clients.push_back(num_carte);
    cout << VERT<<"Client ajouté avec succès !" << RESET<<endl<<endl;;
}


void Base_clients::effacerClient()
{
	int num_carte;
	//Base_clients::afficherClients(); //afficher les numéros carte pour choisir leqeul surpprimer
	cout << "Veuillez saisir le numéro du client à effacer : ";
    cin >> num_carte;
    
    for (unsigned int i = 0; i < num_clients.size(); i++)
    {
        if (num_clients[i] == num_carte)
        {
            num_clients.erase(num_clients.begin() + i);    // supprime l'élément à la position i
            cout <<VERT<< "Client effacé avec succès !" <<RESET<< endl<<endl;
            return;
        }
    }
    cout <<ROUGE<< "Client non trouvé !" <<RESET<<endl;
}

// Fonction qui va englober ajouter et supprimer clients
void Base_clients::modifierClients() 
{
    int code;
    int choix;
    
    cout << "Veuillez saisir le mot de passe : ";
    cout<<GRAS<<BLEU;
    cin >> code;
	cout<<RESET;
    // Vérif du code
    if (code != 2625) 
    {
        cout << ROUGE<<"Code incorrect !" <<RESET<< endl;
        return;
    }

    // Affichage mini menu choix
    cout <<VERT<<"Code correct !"<<RESET<< endl<<endl;
    while(choix!= 4)
    {
    	cout << GRAS<<"\t\t 1."<<RESET<<" Afficher les clients adhérents" << endl;
    	cout << GRAS<<"\t\t 2."<<RESET<<" Ajouter un client" << endl;
    	cout << GRAS<<"\t\t 3."<<RESET<<" Supprimer un client" << endl;
    	cout << GRAS<<"\t\t 4."<<RESET<<" Quitter" << endl<<endl;
    	cout << "Votre choix : ";
    	cin >> choix;
    	cout<<endl;
	
    	switch (choix) 
    	{
    			case 1:
            		Base_clients::afficherClients();
        		break;
    		
        		case 2:
            		Base_clients::ajouterClient();
       			break;
            		
        		case 3:
            		Base_clients::effacerClient();
        		break;
        		
        		case 4:
        			cout<<GRAS<<"Session Administrateur terminée"<<endl<<endl;
        		break;
            		
        		default:
            		cout << "Choix incorrect." << endl;
        		break;
    	}
    }
}
