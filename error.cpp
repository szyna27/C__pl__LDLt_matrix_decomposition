#include <stdio.h>
#define MAX_ERR 5

static char* p[] = { "",
	" odczytywanie danych",
	" otwarcie pliku",
	" brak pamieci",
	" element zerowy na przekatnej",
	" nieznany ",
};

void error(int nr, char* str)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}