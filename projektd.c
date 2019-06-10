#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/random.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int proc, proc1, proc2, proc3; // zmienne globalne
#define WRITE 1
#define READ 0
#define BUFF_SIZE 128


void koniec(int sig)
{
	kill(proc1, SIGKILL);
	kill(proc2, SIGKILL);
	kill(proc3, SIGKILL);
	kill(proc, SIGKILL);

}



int main(void)
{
	int liczba;
	int pdes[2];
	pipe(pdes);
	int x;

	char hex[BUFF_SIZE];
	char text[BUFF_SIZE];

	FILE *plik;


	proc1 = fork();



	if (proc1 == 0)
	{
		
		fflush(stdout);

		signal(SIGUSR1, koniec);
		

		sleep(1);
		printf("\n Jak mam działać?.\n");
		printf("1 - Pobieraj liczby\n");
		printf("2 - Czytanie z pliku\n");
		printf("3 - Liczby losowe\n");

		int decyzja;
		scanf(" %d", &decyzja);


		close(pdes[READ]);

		switch (decyzja)
		{

		case 1: {
			while (1)
			{
				sleep(1);
				printf("\nPodaj liczbe: ");
				fflush(stdout);
				scanf("%d", &liczba);
				fflush(stdin);
				write(pdes[WRITE], &liczba, sizeof(liczba));
			}
		}break;


		case 2: {
			FILE *plik;
			plik = fopen("dane.txt", "r");
			if (plik == NULL) printf("Brak pliku o podanej nazwie");
			else
			{
				while (feof(plik) == 0)
				{
					sleep(1);
					fscanf(plik, "%d", &liczba);
					write(pdes[WRITE], &liczba, sizeof(liczba));
				}
				fclose(plik);
			}
		}break;


		case 3: {
			FILE *file;
			file = fopen("wejscie.txt", "w+");
			while (1)
			{

				int urnd = open("/dev/urandom", O_RDONLY);
				read(urnd, &liczba, sizeof(int));
				close(urnd);
				if (liczba < 0) liczba = -liczba;
				liczba = liczba % 500;
				sleep(1);
				fprintf(file, "%d\n", liczba);
				fflush(file);

				//sleep(1);
				write(pdes[WRITE], &liczba, sizeof(liczba));
				fflush(stdout);

			}
			fclose(file);
		}break;

		default: {
			printf("Nieprawidlowa opcja! \n");
			return 0;
		}break;

		}
		return 0;


	}
	proc2 = fork();
	if (proc2 == 0)
	{
		close(pdes[WRITE]);

		proc1 = getpid();
		while (1)// informowanie nas o działaniu procesu
		{

			read(pdes[READ], &x, sizeof(x));// pobranie wyniku
			//printf("Proces 2: przyjąlem  %d i zaczynam zamieniac \n", x);

			sprintf(hex, "%x", x);
			plik = fopen("liczby.txt", "w+");
			fprintf(plik, "%s\n", hex);
			fclose(plik);
			printf("%s", hex);
			sleep(1);
		}

	}
	proc3 = fork();
	if (proc3 == 0)
	{
		//sleep(5);
		int a = 0;

		proc2 = getpid();
		while (1) // informowanie nas o działaniu procesu
		{
			plik = fopen("liczby.txt", "r");

			if(plik) {
				fscanf(plik, "%s", text);
				fclose(plik);
				if (text[0] != '\0') {
					printf("%s", text);
				}
				fflush(stdout);
				printf(" ");
				a++;

				if (a % 15 == 0)
				{
					printf("\n");
				}
				unlink("liczby.txt");
			}
			sleep(1);
		}
		sleep(1);
	}
	proc = getpid();

	signal(SIGUSR1, koniec);
	
	FILE *plik1 = fopen("procesy.txt", "w+");
	fprintf(plik1, "%d\n", proc);
	fprintf(plik1, "%d\n", proc1);
	fprintf(plik1, "%d\n", proc2);
	fprintf(plik1, "%d\n", proc3);
	fclose(plik1);
	
	for (;;)
	{
		sleep(2);
	}
	fclose(plik1);

	return 0;
}
