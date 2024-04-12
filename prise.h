#ifndef PRISE_H
#define PRISE_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <mem_sh.h>
#include <donnees.h>

#include "voyants.h"

using namespace std;

class Prise
{
  public : 
  	Prise();
	void verouiller_trappe();
	void deverouiller_trappe();
	int set_prise();
	Voyants voyant;
	
	entrees* io;
	int shmid;
	int prise_branche;
};

#endif // PRISE_H
