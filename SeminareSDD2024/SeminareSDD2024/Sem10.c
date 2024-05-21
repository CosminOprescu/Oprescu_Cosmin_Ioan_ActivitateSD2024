#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev {
	int id;
	int nrMedii;
	float* medii;
};

struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};

void inserare(Nod** radacina, Elev e) {
	if (*radacina) {
		if (e.id < (*radacina)->info.id) {
			inserare(&((*radacina)->st), e);
		}
		else {
			inserare(&((*radacina)->dr), e);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = e;//shallow copy
		nou->st = NULL;
		nou->dr = NULL;
		*radacina = nou;
	}
}

Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = (float*)malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &e.medii[i]);
	}
	return e;
}

Nod* citireFisier(char* numeFisier) {
	Nod* arbore = NULL;
	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* f = fopen(numeFisier, "r");
		int n;
		fscanf(f, "%d", &n);
		for (int i = 0; i < n; i++) {
			Elev e = citireElev(f);
			inserare(&arbore, e);
		}
		fclose(f);
	}
	return arbore;
}

void afisareElev(Elev e) {
	printf("Elevul cu id-ul %d are %d medii, acelea fiind: ", e.id, e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%5.2f ", e.medii[i]);
	}
	printf("\n");
}

void afisareSRD(Nod* arbore) {
	if (arbore != NULL) {
		afisareSRD(arbore->st);
		afisareElev(arbore->info);
		afisareSRD(arbore->dr);
	}
}

float calculeazaMedieElev(Elev e) {
	float suma = 0;
	for (int i = 0; i < e.nrMedii; i++) {
		suma += e.medii[i];
	}
	return suma / e.nrMedii;
}

float calculeazaSumaNote(Nod* arbore, int* nrNote) {
	if (arbore != NULL) {
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		float sumaS = calculeazaSumaNote(arbore->st, nrNote);
		float sumaD = calculeazaSumaNote(arbore->dr, nrNote);
		(*nrNote) += arbore->info.nrMedii;
		return suma + sumaS + sumaD;
	}
	else {
		return 0;
	}
}

float calculeazaMedieGenerala(Nod* arbore) {
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0) {
		return suma / nrNote;
	}
	else {
		return 0;
	}
}

void main() {//de fct si functia de cautare
	Nod* arbore = citireFisier("Elevi.txt");
	afisareSRD(arbore);

	printf("Media este: %5.2f", calculeazaMedieGenerala(arbore));
}