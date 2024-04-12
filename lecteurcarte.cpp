#include "lecteurcarte.h"


enum Etat {MENU, ADMIN, INSERT_CARTE,AUTH_CORRECT, AUTH_INCORRECT,STOP_PDT_CHARGMT, DEFAUT, ETAT1, ETAT2, ETAT3, ETAT4};
Etat etatCourant;

LecteurCarte::LecteurCarte() {}

void LecteurCarte::initialiser()
{
	initialisations_ports();
}

void LecteurCarte::lire_carte()
{
	
	
	switch (etatCourant)
		{
			case MENU :
				baseclient.menu(&choix_menu);	
	
				if(choix_menu==1)
				{etatCourant = INSERT_CARTE;}
				else if(choix_menu==2)
				{etatCourant = ADMIN;}
				
			break;
			
			
			case INSERT_CARTE :
			
				cout<<"VEUILLEZ INSERER VOTRE CARTE SVP"<<endl;
				attente_insertion_carte();
				numero_carte=lecture_numero_carte();  // lecture de la carte
				
				carte_debut = numero_carte; // on stocke num_carte du debut pour la reprise voiture			

				cout<<"Numéro de la carte : "<<numero_carte<<endl;
				cout<<endl;
				cout<<"Veuillez retirer votre carte"<<endl;
				attente_retrait_carte();
				
		
				// Vérification de la carte 
				if(baseclient.authentifier(numero_carte) && voyants.dispo()) // si client ok + voyant disponible vert
				{	
					etatCourant = AUTH_CORRECT;
				}
				else
				{
					etatCourant = AUTH_INCORRECT;
				}
				
			break;
		
										// ************************************************//
				
		 	case AUTH_CORRECT : 
		 	
		 	timer.timer_raz(); // on initialise depart_timer
			cout<<" - Appuyez sur BOUTON CHARGE pour charger votre véhicule "<<endl;
			cout<<" - Appuyez sur BOUTON STOP pour arrêter "<<endl<<endl;
			cout<<" /!\\ Vous avez 60s pour faire un choix /!\\"<<endl<<endl;
			
			// tant que la diffirence entre depart_timer et l'horloge actuelle est inferieur à 60 
			// Ou pas d'appui sur le bouton charge ou stop on reste dans la boucle
		 	while((duree <= 16) && (appui_charge!=1) && (appui_stop!=1))
		 	{
				duree = timer.timer_valeur();   // on récupère la valeur du timer
				//cout<<"Temps = "<<duree<<endl;
				
				appui_stop = bouton.bouton_stop();  // regarder l'état du bouton stop
		    	appui_charge = bouton.bouton_charge();  // regarder l'état du bouton charge
				
				// on fait clignoter la led charge pendant 8secondes
				if (duree <= 8)
				{
					voyants.blink_charge();
				}
				else {voyants.set_charge(OFF);}
				
				
				if (appui_charge==1)
				{
					voyants.set_dispo(OFF);
					voyants.set_charge(ROUGE);
						
					etatCourant = ETAT1;
				}
				
				if (appui_stop==1 || duree >= 10)
				{						
					etatCourant = DEFAUT;    		
				}
		 	}
		 				
			break;
			
											// ************************************************//
				
			case ETAT1 : 
				
				//Après les 60secondes, on regarde si bouton charge a été appuye, on deverouille la trappe 
				//On genere PWM de 12V DC
	 			prise.deverouiller_trappe();
	  			generateur.generer_PWM(DC); 
	  			
				cout<<"VEUILLEZ BRANCHER LA PRISE !"<<endl;
				while( (valeur_tension != 9) && (appui_stop != 1))
				{
					valeur_tension = generateur.tension(); // on récupère la valeur de la tension que gene_u retourne sur le fil pilote
		 			// si tension vaut 9 on met le voyant prise à vert et on verrouille la trappe 
					//cout<<"Tension prise disponible DC = "<<valeur_tension<<endl; 
					appui_stop = bouton.bouton_stop();
					
					if (valeur_tension==9)
					{
						voyants.led_prise(VERT);
						prise.verouiller_trappe();
						generateur.generer_PWM(AC_1K);    // Generer tension AC
						usleep(1000000);
						prise_branchee = 1;
						
						etatCourant = ETAT2;
					} 
					else if (appui_stop==1)  
					{						
						etatCourant = DEFAUT;    		
					}
					
				}
			break;
			
													//************************************************//
			
			case ETAT2 : 
				// Fermer contacteur AC et recuperer son etat
				// Verifier si contacteur est bien fermé
				etatContacteur_AC = generateur.ouvrir_fermer_AC(1);
				
				if (etatContacteur_AC==1)
				{
					generateur.generer_PWM(AC_CL); // Generer un signal PWM de 1KHz à rapport cyclique variable
					cout<<"Tension = "<< valeur_tension<<endl;
					etatCourant = ETAT3;	
				}
				valeur_tension=0; // Réinitialiser la valeur de tension récupérée
				
			break ;
			
													//************************************************//
			
			
			
			case ETAT3 : 						
				
			// Attente de la charge batterie 
				while ((valeur_tension!=9) && (appui_stop != 1))
				{
					cout<<"Rechargement de la batterie : tension AC = "<<valeur_tension<<endl;
					valeur_tension = generateur.tension();   // récuperer valeur tension
					appui_stop = bouton.bouton_stop();     // recuperer etat bouton stop
					
			
					
				
					// Si tension = 9 (chargement terminé)
					if ( valeur_tension==9)
					{
							//cout<<"Tension AC = "<< valeur_tension<<endl; 
         					etatContacteur_AC = generateur.ouvrir_fermer_AC(0); // ouvrir contacteur AC
         					numero_carte = 0; // réinitialiser num_carte pour entrer dans boucle while en dessous
         					baseclient.reprise(numero_carte, carte_debut); // on s'authentifie avant de pouvoir débrancher la prise 
         					
         					generateur.generer_PWM(DC); // generer tension DC
         					usleep(1000000);
         					voyants.set_charge(VERT);
         					
         					etatCourant = ETAT4;
					}
					// si un appui sur stop est détécté pendant le chargement, on s'authentifie pour l'arrêter
					else if (appui_stop == 1) 
					{
						
						etatCourant = STOP_PDT_CHARGMT;    		
					}
				}
				break ;
				
													//***********************************************//
				
				case ETAT4 : 	
		
					prise.deverouiller_trappe(); // deverouiller trappe
					cout<<"VEUILLEZ DEBRANCHER LA PRISE !"<<endl;
					// Attente de débrancher 
					while ((valeur_tension!=12 ) && (prise_branchee == 1))
					{	
						valeur_tension= generateur.tension();
						
						if (valeur_tension==12)
						{	
							voyants.led_prise(OFF);
							voyants.set_charge(OFF);
							voyants.set_dispo(VERT);
						}
					}
					cout<<endl;
					etatCourant = DEFAUT;
				
				break;
				
													//************************************************//
			
			case STOP_PDT_CHARGMT :
	
				cout<<"Réauthentifier vous pour arrêter le chargement de la voiture "<<endl;
				cout<<endl;
         					
				numero_carte=0;
				
       				baseclient.reprise(numero_carte, carte_debut); // on s'authentifie avant de pouvoir débrancher la prise	
						
				etatContacteur_AC = generateur.ouvrir_fermer_AC(0); // ouvrir contacteur AC
				generateur.generer_PWM(DC); // generer tension DC
         		usleep(1000000);
         		voyants.set_charge(VERT);
			
				etatCourant = ETAT4;
			break;			
			
													//************************************************//
			
				
			case AUTH_INCORRECT : 
				timer.timer_raz(); // on initialise depart_timer
				cout<<"BLINK LED DEFAUT 8s "<<endl;
				
		 		while(duree <= 8)
		 		{
					duree = timer.timer_valeur();   // on récupère la valeur du timer
					
					if (duree <= 8)
					{
						voyants.blink_defaut();
					}
					else {voyants.set_defaut(OFF);}
		 		}
		 		cout<<endl;
		 		etatCourant = DEFAUT; 		
				
			break;	
			
													//************************************************//
			
			case DEFAUT :
				
				generateur.generer_PWM(STOP);
				cout<<"L'EXCES DE VITESSE TUE, SOYEZ PRUDENT !"<<endl;
				cout<<endl;
				usleep(2000000); // Attendre 2sec avant de reprendre
				
				voyants.voyants_initialiser();
				bouton.boutons_initialiser();
				
				duree=0;
				appui_stop = 0;
				appui_charge=0;
				carte_debut = 0;
				
				etatCourant = MENU;		
			break;
			
			case ADMIN :
			
				baseclient.modifierClients() ;
				etatCourant = MENU;	
				
			break;		
			
		}
}

