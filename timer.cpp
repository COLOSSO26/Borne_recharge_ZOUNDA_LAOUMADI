#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

Timer::Timer()
{	
	io=acces_memoire(&shmid);
	if (io==NULL) printf("Erreur pas de mem sh\n");
}

void Timer::timer_raz()
{ 
	depart_timer = io->timer_sec;
}

int Timer::timer_valeur()
{
	return io->timer_sec - depart_timer;
}

