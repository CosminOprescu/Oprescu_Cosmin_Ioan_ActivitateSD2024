#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dim) {//dim e pointer pt ca o vom modifica 
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dim) + 1));
	copie[(*dim)] = aeroport;
	for (int i = 0; i < (*dim); i++)
	{
		copie[i] = vector[i];
	}

	if (vector != NULL) {
		free(vector);
	}

	(*dim)++;
	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*nrAeroporturi) = 0;
		char buffer[100];//aloc static pt ca compilatorul dezaloca memoria automat; pot aloca dinamic doar dupa ce citesc, dar am nev de buffer ca sa citesc
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";//cauta virgula; daca nu o gaseste cauta new line
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);//la nrAeroporturi nu punem nimic pt ca sunt ambele de tip pointer la int

		}
		fclose(f);
	}
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu id %d, din %s, are %d terminale\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}

struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int idCautat) {
	for (int i = 0; i < dim; i++) {
		if (aeroporturi[i].id == idCautat) {
			return aeroporturi[i];
		}
	}
	struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = -1;
	aeroport.nume = NULL;
	return aeroport;
}

void dezalocare(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
		free(aeroporturi[i]);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void main() {
	int dimensiune = 3;
	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);
	printf("\n");
	dezalocare(&aeroporturi, &dimensiune);
}