// rationaleZahlen.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define pi 3.14159265
#pragma warning (disable: 4996)

struct Rzahl
{
	int z;
	int n;
};

void newline(char* chaine)
{
	size_t len = strlen(chaine);
	if (len > 0 && (chaine[len - 1] == '\n'))
	{
		chaine[len - 1] = '\0'; // Entfernt das Zeichen '\n' am Ende des Strings
	}
}

void newlineLoeschen(char* chaine)
{
	int count = 0;
	for (int i = 0; chaine[i]; i++)
	{
		if (chaine[i] != ' ')
		{
			chaine[count++] = chaine[i];
		}
	}
	chaine[count] = '\0';

	size_t len = strlen(chaine);
	if (len > 0 && (chaine[len - 1] == '\n'))
	{
		chaine[len - 1] = '\0'; // Entfernt das Zeichen '\n' am Ende des Strings
	}

}

int ggt(int x, int y)
{
	if (y == 0)
		if (x == 0)
			return 1; // der ggt von 0 und 0 ist 1 (per Def.)
		else
			return x;
	else
		return ggt(y, (x % y));
}

Rzahl operator*(Rzahl r1, Rzahl r2)
{
	Rzahl res = { 0,0 };
	int t = 0;
	res.z = r1.z * r2.z;
	res.n = r1.n * r2.n;
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;

}

Rzahl operator/(Rzahl r1, Rzahl r2)
{
	Rzahl res = { 0,0 };
	int t = 0;
	res.z = r1.z * r2.n;
	res.n = r1.n * r2.z;
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

Rzahl operator+(Rzahl r1, Rzahl r2)
{
	Rzahl res = { 0,0 };
	int t = 0;
	res.z = (r1.z * r2.n) + (r2.z * r1.n);
	res.n = (r1.n * r2.n);
	t = ggt(res.z, res.n);
	res.z = res.z / t;
	res.n = res.n / t;
	return res;
}

Rzahl inv(Rzahl r)
{
	Rzahl res = { r.n, r.z };
	return res;
}

Rzahl kurz(Rzahl r)
{
	int t = ggt(r.z, r.n);
	r.z = r.z / t;
	r.n = r.n / t;
	return r;
}

Rzahl erweit(Rzahl r, int f = 1)
{
	r.z = r.z * f;
	r.n = r.n * f;
	return r;
}

bool vergleich(Rzahl r1, Rzahl r2)
{
	if ((r1.z == r2.z) && (r1.n == r2.n))
		return true;
	else
		return false;
}

void print(int z, int n)
{
	if (n < 0 || z < 0)
	{
		if (n == 1)
			printf("%i\n\n", z);
		else if ((z > 0 && n < 0) || (z < 0 && n < 0))
			printf("%i/%i\n\n", (-1) * z, (-1) * n);
		else
			printf("%i/%i\n\n", z, n);
	}
	else
	{
		if (n == 1)
			printf("%i\n\n", z);
		else
		printf("%i/%i\n\n", z, n);
	}
		

}
double _strtod (const char* str)
{
	char* endptr;
	double result = strtod(str, &endptr);

	// Check if the entire string was parsed, and if not, return 0.0
	if (*endptr != '\0') 
	{
		result = 0.0;
	}

	return result;
}

void main(void)
{
	char input[100];
	int value[4];
	Rzahl r1 = { 0,0 };
	Rzahl r2 = { 0,0 };
	Rzahl res = { 0,0 };
	int f = 1;
	printf("\tBRUCHRECHNER\n\t=========================\n");
	while (1)
	{
		Loop:
		printf(">> ");
		fgets(input, sizeof(input), stdin);
		newlineLoeschen(input);

		if (strstr(input, "*") != NULL)
		{
			char* token = strtok(input, " /*()");
			for (int i = 0; i < 4; i++)
			{
				value[i] = _strtod(token);
				if (_strtod(token) == 0.0)
				{
					printf("Invalid input '%s'\n\n", token);
					goto Loop;
				}

				token = strtok(NULL, " /*()");
			}
			r1 = { value[0],value[1] };
			r2 = { value[2], value[3] };
			res = r1 * r2;
			printf("ans = ");
			print(res.z, res.n);
		}
		else if(strstr(input, ":") != NULL)
		{
			char* token = strtok(input, " /:()");
			for (int i = 0; i < 4; i++)
			{
				value[i] = _strtod(token);
				if (_strtod(token) == 0.0)
				{
					printf("Invalid input '%s'\n\n", token);
					goto Loop;
				}
				token = strtok(NULL, " /:()");
			}
			r1 = { value[0],value[1] };
			r2 = { value[2], value[3] };
			res = r1 / r2;
			printf("ans = ");
			print(res.z, res.n);

		}

		else if (strstr(input, "-") != NULL || strstr(input,"+"))
		{
			if (sscanf(input, "(%i/%i) - (%i/%i)", &r1.z, &r1.n, &r2.z, &r2.n) == 4)
			{
				r2.z = (-1) * r2.z;
				res = r1 + r2;
				printf("ans = ");
				print(res.z, res.n);
			}
			else if  (sscanf(input, "%i/%i - %i/%i", &r1.z, &r1.n, &r2.z, &r2.n) == 4)
			{
				r2.z = (-1) * r2.z;
				res = r1 + r2;
				printf("ans = ");
				print(res.z, res.n);
			}
			else if (sscanf(input, "(%i/%i) + (%i/%i)", &r1.z, &r1.n, &r2.z, &r2.n) == 4)
			{
				res = r1 + r2;
				printf("ans = ");
				print(res.z, res.n);
			}
			else if (sscanf(input, "%i/%i + %i/%i", &r1.z, &r1.n, &r2.z, &r2.n) == 4)
			{
				res = r1 + r2;
				printf("ans = ");
				print(res.z, res.n);
			}
			else
			{
				printf("Invalid Input\n\n");
				continue;
			}
;
		}
		else if (strstr(input, "inv") != NULL)
		{
			if (sscanf(input, "inv (%i/%i)", &r1.z, &r1.n) == 2)
			{
				res = inv(r1);
				printf("ans = ");
				print(res.z, res.n);
			}
			else
			{
				printf("Invalid Input\n\n");
				continue;
			}

		}

		else if (sscanf(input, "%i/%i", &r1.z, &r1.n) >= 1)
		{
			if (sscanf(input, "%i/%i", &r1.z, &r1.n) == 2)
			{
				res = kurz(r1);
				printf("ans = ");
				print(res.z, res.n);
			}
			
			else
			{
				printf("Invalid Input\n\n");
				continue;
			}

		}

		else if (strstr(input, "erweit") != NULL)
		{
			
			if (sscanf(input, "erweit (%i/%i, %i)", &r1.z, &r1.n, &f) == 3)
			{
				res = erweit(r1, f);
				printf("ans = ");
				print(res.z, res.n);
			}

			else
			{
				printf("Invalid Input\n\n");
				continue;
			}

		}

		else if (strstr(input, "vergleich") != NULL)
		{
			if (sscanf(input, "vergleich (%i/%i, %i/%i)", &r1.z, &r1.n, &r2.z, &r2.n) == 4)
			{
				bool res = vergleich(r1, r2);
				if (res == true)
					printf("Die beide rationale Zahlen sind gleich.\n\n");
				else
					printf("Die beide rationale Zhalen sind ungleich\n\n");
			}
			else
			{
				printf("Invalid Input\n\n");
				continue;
			}


		}

		else if (strncmp(input, "exit", 3) == 0)
		{
			printf("\nAnwender hat das Programm beendet\n");
			break;
		}

	}

}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
