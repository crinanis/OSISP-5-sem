#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void cycle(char* s)
{
	for (int i = 1; i < 50; i++)
	{
		sleep(1);
		printf("%i: %s, %d\n\n", getpid(), s, i);
	}
};

