#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int proc,proc1,proc2,proc3;
int PROC[4];

int main(void)
{
FILE *plik;

plik=fopen("procesy.txt","r");

if(plik == NULL) printf("Plik nie istnieje");

else
	{
		int i,j;
	for (i=0;i<4;i++)
		{
			fscanf(plik,"%d",&PROC[i]);
		}
		
		int temp;
    
    for(i = 1; i < 4; i++ )
    {
        temp = PROC[ i ];
        
        for( j = i - 1; j >= 0 && PROC[ j ] > temp; j-- )
             PROC[ j + 1 ] = PROC[ j ];
        
        PROC[ j + 1 ] = temp;
    }
	
	}
	proc=PROC[0];
	proc1=PROC[1];
	proc2=PROC[2];
	proc3=PROC[3];
	printf("Proces Macierzysty):  %d\n",proc);
	printf("Proces K1:  %d\n",proc1);
	printf("Proces K2:  %d\n",proc2);
	printf("Proces K3:  %d\n",proc3);
	int wybor_proc,wybor_syg,PID;
	fclose(plik);
	for(;;)
	{
	printf("\nKtóry proces ma otrzymac sygnal \n");
	printf("1 - proces M (inicjujacy)\n");
	printf("2 - proces K1\n");
	printf("3 - proces K2\n");
	printf("4 - proces K3\n");
	scanf("%d",&wybor_proc);
	
	
	printf("Jaki sygnal chcesz wyslac? \n");
	printf("1 - sygnal zakonczenia\n");
	printf("2 - sygnal zatrzymania\n");
	printf("3 - sygnal wznowienia\n");
	scanf("%d",&wybor_syg);
	
	
	
	
	
	if(wybor_syg==1)
	{
		printf("koncze M\n");
		unlink("wejscie.txt");
		unlink("procesy.txt");
		unlink("liczby.txt");
		kill(proc,SIGUSR1);
		
		sleep(2);
		kill(getpid(),SIGKILL);
		
	}
	

	else if (wybor_syg == 3 && wybor_proc == 1)
	{
		printf("wznawiam M\n");
		kill(proc1, SIGCONT);
		kill(proc2, SIGCONT);
		kill(proc3, SIGCONT);
		kill(proc, SIGCONT);

	}
	else if (wybor_syg == 3 && wybor_proc == 2)
	{
		printf("wznawiam P1\n");
		kill(proc, SIGCONT);
		kill(proc2, SIGCONT);
		kill(proc3, SIGCONT);
	}
	else if (wybor_syg == 3 && wybor_proc == 3)
	{
		printf("wznawiam P2\n");
		kill(proc1, SIGCONT);
		kill(proc2, SIGCONT);
		kill(proc3, SIGCONT);
	}
	else if (wybor_syg == 3 && wybor_proc == 4)
	{
		printf("wznawiam P3\n");
		kill(proc1, SIGCONT);
		kill(proc2, SIGCONT);
		kill(proc3, SIGCONT);
	}


	else if(wybor_syg==2 && wybor_proc==1)
	{
		printf("wstrzymuje M\n");
		kill(proc1,SIGSTOP);
		kill(proc2,SIGSTOP);
		kill(proc3,SIGSTOP);
	}
	else if(wybor_syg==2 && wybor_proc== 2)
	{
		printf("wstrzymuje P1\n");
		kill(proc1,SIGSTOP);
		kill(proc2,SIGSTOP);
		kill(proc3,SIGSTOP);
	}
	else if(wybor_syg==2 && wybor_proc==3)
	{
		printf("wstrzymuje P2\n");
		kill(proc1,SIGSTOP);
		kill(proc2,SIGSTOP);
		kill(proc3,SIGSTOP);
		
	}
	else if(wybor_syg==2 && wybor_proc==4)
	{
		printf("wstrzymuje P3\n");
		kill(proc1,SIGSTOP);
		kill(proc2,SIGSTOP);
		kill(proc3,SIGSTOP);
		
	}
	

	
	else 
	{
		printf("Sprobuj jeszcze raz\n");
		continue;
		}
}


return 0;
}
