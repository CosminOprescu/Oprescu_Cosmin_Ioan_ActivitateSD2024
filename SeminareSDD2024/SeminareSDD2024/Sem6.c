#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod {
	Biblioteca info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* head;//primul nod
	Nod* tail;//ultimul nod
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {//avem pointer la lista dubla pt ca aceasta se va modifica
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = b;//am fct shallow copy
	nou->prev = NULL;
	nou->next = listaDubla->head;
	if (listaDubla->head) {
		listaDubla->head->prev = nou;
	}
	else {
		listaDubla->tail = nou;
	}
	listaDubla->head = nou;
}

void afisareListaDublaInceput(ListaDubla listaDubla) {
	while (listaDubla.head) {
		printf("Biblioteca: %s; Numar carti: %d; Numar cititori: %d\n", listaDubla.head->info.nume,
			listaDubla.head->info.nrCarti, listaDubla.head->info.nrCititori);
		listaDubla.head = listaDubla.head->next;
	}
	printf("\n");
}

void stergeNodDupaNume(ListaDubla* listaDubla, const char* nume) {
	Nod* aux = listaDubla->head;
	while (aux && strcmp(nume, aux->info.nume) != 0) {
		aux = aux->next;
	}
	if (aux) {
		if (aux == listaDubla->head) {
			if (aux == listaDubla->tail) {
				listaDubla->head = NULL;
				listaDubla->tail = NULL;
			}
			else {
				listaDubla->head = listaDubla->head->next;
				listaDubla->head->prev = NULL;
			}
		}
		else {
			if (aux == listaDubla->tail) {
				aux->prev->next = NULL;
				listaDubla->tail = aux->prev;
			}
			else {
				aux->next->prev = aux->prev;
				aux->prev->next = aux->next;
			}
		}
	}
	free(aux->info.nume);
	free(aux);
}

void stergereTotalaLista(ListaDubla* listaDubla) {
	while (listaDubla->head) {
		free(listaDubla->head->info.nume);
		Nod* aux = listaDubla->head;
		listaDubla->head = listaDubla->head->next;
		free(aux);
	}
	listaDubla->head = NULL;
	listaDubla->tail = NULL;
}

int nrCartiTotal(ListaDubla listaDubla) {
	int rezultat = 0;
	while (listaDubla.tail) {
		rezultat += listaDubla.tail->info.nrCarti;
		listaDubla.tail = listaDubla.tail->prev;
	}
	return rezultat;
}

void main() {
	Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	Biblioteca b4 = initializare("Mihail Sadoveanu", 300, 50);

	ListaDubla listaDubla;//avem un obiect
	listaDubla.head = NULL;
	listaDubla.tail = NULL;

	inserareInceput(&listaDubla, b1);
	inserareInceput(&listaDubla, b2);
	inserareInceput(&listaDubla, b3);
	afisareListaDublaInceput(listaDubla);

	/*stergeNodDupaNume(&listaDubla, "Ioan Slavici");
	afisareListaDublaInceput(listaDubla);

	stergeNodDupaNume(&listaDubla, "Mihai Eminescu");
	afisareListaDublaInceput(listaDubla);

	stergeNodDupaNume(&listaDubla, "Tudor Arghezi");
	afisareListaDublaInceput(listaDubla);*/

	/*stergereTotalaLista(&listaDubla);
	afisareListaDublaInceput(listaDubla);*/

	int rezultat = nrCartiTotal(listaDubla);
	printf("%d", rezultat);
}