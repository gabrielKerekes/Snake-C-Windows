#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define maxSize 100

typedef struct had
{
	int size, smer, x, y;
}HAD;

int smer(int smer, int hSmer)
{
	if ( hSmer == smer )
		return hSmer;
	else if ( hSmer == 0 && smer == 1 )
		return hSmer;
	else if ( hSmer == 1 && smer == 0 )
		return hSmer;
	else if ( hSmer == 2 && smer == 3 )
		return hSmer;
	else if ( hSmer == 3 && smer == 2 ) 
		return hSmer;
	
	return smer;
}

void jedlo(int *zjedol, HAD telo[maxSize], int *body, int bSizeX, int bSizeY)
{
	static int jedlox = 0, jedloy = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point;
	int i, este = 0;

	if ( *zjedol == 1 )
	{
		do{
			jedlox = rand()%(bSizeX-1) + 1;
			jedloy = rand()%(bSizeY-1) + 1;
			este = 0;
			for ( i = 0; i < telo[0].size; i++ )
			{
				if ( telo[i].x == jedlox && telo[i].y == jedloy )
					este = 1;
				
			}
		}while ( este == 1 );
		point.X = jedlox;
		point.Y = jedloy;
		SetConsoleCursorPosition(hConsole, point);
		printf("N");
		*zjedol = 0;
	}
	else
	{
		point.X = jedlox;
		point.Y = jedloy;
		SetConsoleCursorPosition(hConsole, point);
		printf("N");
	}
	if ( telo[0].x == jedlox && telo[0].y == jedloy )
	{
		telo[0].size++;
		*zjedol = 1;
		*body += 9;
	}
}

void bludisko(int bSizeX, int bSizeY)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point;
	int i;
	
	for ( i = 0; i < bSizeX; i++ )
	{
		point.X = i;
		point.Y = 0;
		SetConsoleCursorPosition(hConsole, point);
		printf("_");
	}
		
	for ( i = 0; i < bSizeX; i++ )
	{
		point.X = i;
		point.Y = bSizeY;
		SetConsoleCursorPosition(hConsole, point);
		printf("_");
	}

	for ( i = 1; i <= bSizeY; i++ )
	{
		point.X = 0; 
		point.Y = i;
		SetConsoleCursorPosition(hConsole, point);
		printf("|");
	}
	
	for ( i = 1; i <= bSizeY; i++ )
	{
		point.X = bSizeX; 
		point.Y = i;
		SetConsoleCursorPosition(hConsole, point);
		printf("|");
	}
}

char koniec(int body)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point;
	char c;
	Sleep(1000);
	system("cls");
	//bludisko();
	point.X = 32;
	point.Y = 12;
	SetConsoleCursorPosition(hConsole, point);
	printf("KOKOT Try harder next time!");
	point.Y = 13;
	SetConsoleCursorPosition(hConsole, point);
	printf("Skore: %i\n\n", body);
	Sleep(3000);
	return 27;
}

char doSeba(HAD telo[maxSize], int body)
{
	int i;
	char c;

	for ( i = 1; i < telo[0].size - 1; i++ )
	{
		if ( telo[0].x == telo[i].x && telo[0].y == telo[i].y )
		{
			koniec(body);
			return 27;
		}
	}
	return 1;
}

void snake(int speed, int bSizeX, int bSizeY)
{
	char c = 0;
	int i, tmpx[maxSize], tmpy[maxSize], zjedol = 1, body = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point = {10, 12};
	HAD telo[maxSize];
	
	telo[0].smer = 3;
	telo[0].size = 4;
	telo[0].x = bSizeX/2;
	telo[0].y = bSizeY/2;
	telo[1].x = telo[0].x - 1;
	telo[1].y = telo[0].y;
	telo[2].x = telo[0].x - 2;
	telo[2].y = telo[0].y;
	bludisko(bSizeX, bSizeY);

	do{
		jedlo(&zjedol, &telo[0], &body, bSizeX, bSizeY);
		if ( _kbhit() )
		{
			c = _getch();
		}
		switch ( c ) 
		{
		case 72: //up
		case 'w':
			telo[0].smer = smer(0, telo[0].smer);
			break;
		case 80: //down
		case 's':
			telo[0].smer = smer(1, telo[0].smer);
			break;
		case 75: //left
		case 'a':
			telo[0].smer = smer(2, telo[0].smer);
			break;
		case 77: //right
		case 'd':
			telo[0].smer = smer(3, telo[0].smer);
			break;
		case 59:
			bludisko(bSizeX, bSizeY);
			break;
		}
		for ( i = 0; i < telo[0].size; i++ )
		{
			tmpx[i] = telo[i].x;
			tmpy[i] = telo[i].y;
		}
		for ( i = 1; i < telo[0].size; i++ )
		{
			telo[i].x = tmpx[i-1];
			telo[i].y = tmpy[i-1];
		}
		switch ( telo[0].smer )
		{
		case 0: //up
			telo[0].y--;
			break;
		case 1: //down
			telo[0].y++;
			break;
		case 2: //left
			telo[0].x--;
			break;
		case 3: //right
			telo[0].x++;
			break;
		}
		point.X = bSizeX - 10;
		point.Y = bSizeY + 2;
		SetConsoleCursorPosition(hConsole, point);
		printf("Body %i", body); 
		jedlo(&zjedol, telo, &body, bSizeX, bSizeY);
		point.X = telo[0].x;
		point.Y = telo[0].y;
		SetConsoleCursorPosition(hConsole, point);
		printf("O");
		for ( i = 1; i < telo[0].size; i++)
		{
			point.X = telo[i].x;
			point.Y = telo[i].y;
			SetConsoleCursorPosition(hConsole, point);
			if ( i == telo[0].size - 1)
			{
				if ( telo[i].y == bSizeY )
					printf("_");
				else
					printf(" ");
			}
			else
				printf("O");
		}
		c = doSeba(telo, body);
		if ( telo[0].x > bSizeX - 1 || telo[0].y > bSizeY
			|| telo[0].x < 1 || telo[0].y < 1 )
			c = koniec(body);
		Sleep(1000 - (speed*100));
	}while ( c != 27 );
}

int main()
{
	int volba, speed = 9, xSize = 20, ySize = 20;
	
	srand(time(0));
	
	do{
		printf("Welcome to Snake roflEdition\n\t1. Nova Hra\n\t2. Zmen rychlost\n\t3. Zmen velkost bludiska\n\t0. Koniec\nVasa volba: ");
		scanf_s("%i", &volba);
		
		switch (volba)
		{
		case 1:
			system("cls");
			snake(speed, xSize, ySize);
			break;
		case 2:
			printf("Zadajte rychlost (od 1 do 9): ");
			scanf_s("%i", &speed);
			break;
		case 3:
			printf("Zadajte sirku (max. 80): ");
			scanf_s("%i", &xSize);
			printf("Zadajte vysku (max.20): ");
			scanf_s("%i", &ySize);
			break;
		}
	}while ( volba != 0 );


	system("cls");
	system("pause");
	return 0;
}
