#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Galerie Galerie;
struct Galerie {
	int cod;
	char* nume;
	float pretIntrare;
};

typedef struct nod nod;
struct nod {
	Galerie info;
	nod* next;
};

typedef struct HashTable HashTable;
struct HashTable {
	nod** vector;
	int dim;
};

HashTable initHashTable(int dimensiune) {
	HashTable h;
	h.dim = dimensiune;
	h.vector = (nod**)malloc(sizeof(nod*) * dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		h.vector[i] = NULL;
	}

	return h;
}

Galerie initGalerie(int cod, const char* nume, float pretIntrare) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(g.nume, nume);
	g.pretIntrare = pretIntrare;

	return g;
}

int calculHash(int cod, const char* nume, int dimensiune) {
	if (dimensiune > 0) {
		int rez = cod * strlen(nume);
		return rez % dimensiune;
	}
	return -1;
}

void inserareLaFinal(nod** cap, Galerie g) {
	nod* temp = (nod*)malloc(sizeof(nod));
	temp->info = g;
	temp->next = NULL;

	if (*cap) {
		nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = temp;
	}
	else {
		*cap = temp;
	}
}

void inserareGalerieInTabela(HashTable h, Galerie g) {
	if (h.dim > 0) {
		int pozitie = calculHash(g.cod, g.nume, h.dim);

		if (h.vector[pozitie] != NULL) {	// coliziune
			inserareLaFinal(&(h.vector[pozitie]), g);
		}
		else {								// nu avem coliziune
			inserareLaFinal(&(h.vector[pozitie]), g);
		}
	}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}

void afisareListaGalerii(nod* cap) {
	while (cap) {
		afisareGalerie(cap->info);
		cap = cap->next;
	}
}

void afisareTabela(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i] != NULL) {
			printf("Clusterul: %d\n", i + 1);
			afisareListaGalerii(h.vector[i]);
		}
		printf("\n");
	}
}

Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable h) {
	int pozitie = calculHash(cod, nume, h.dim);

	if (pozitie >= 0 && pozitie < h.dim) {
		nod* p = h.vector[pozitie];

		while (p && p->info.cod != cod && strcmp(p->info.nume, nume) != 0) {
			p = p->next;
		}

		if (p) {
			return p->info; // shallow copy
		}
		else {
			return initGalerie(-1, "N/A", 0);
		}
	}
	else {
		return initGalerie(-1, "N/A", 0);
	}
}

void main() {
	Galerie g1 = initGalerie(1, "Orizont", 10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);


	HashTable tabela = initHashTable(5);

	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);

	afisareTabela(tabela);

	Galerie g = cautaGalerieDupaCheie(1, "Orizont", tabela);
	afisareGalerie(g);
}