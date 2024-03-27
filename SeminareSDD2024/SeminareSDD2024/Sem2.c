#include <malloc.h>
#include <stdio.h>

struct Calculator {
	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int nrPorturi) {
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);
	c.pret = pret;
	c.nrPorturi = nrPorturi;
	return c;
}

void afisareCalculator(struct Calculator c) {
	printf("Calculatorul cu seria %s, costa %5.2f si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}

void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare) {
	if (nrCalculatoare > 0 && vector != NULL) {
		for (int i = 0; i < nrCalculatoare; i++) {
			afisareCalculator(vector[i]);
		}
	}
}

struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate) {
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (strlen(calculatoare[i].serie) + 1));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
}

struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi) {
	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			(*nrCalculatoarePorturi)++;//dereferentiere pt a nu modifica adresa
		}
	}
	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);
		}
	}
	return v;
}

//fct care gaseste primul calculator cu un pret dat si il afiseaza doar pe primul daca sunt mai multe
struct Calculator returneazaCalculator(struct Calculator c, struct Calculator* calculatoare, float pretDat, int nrCalculatoare) {
	int k = 1;
	while (k != 0) {
		for (int i = 0; i < nrCalculatoare; i++) {
			if (calculatoare[i].pret = pretDat) {
				k = 0;
				return calculatoare[i];
			}
		}
	}
}

void dezalocare(struct Calculator** vector, int* dim) {//facem si vectorul nul si dimensiunea 0 de aceea le transmitem prin adresa pe ambele 
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].serie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main() {
	//id curs 41166
	//cheia de acces e 3854
	//vector structura liniara omogena, liniara, care ocupa o zona de memorei contigua
	//int v[10];//alocat static pe stack si ca ocupa 4(dimensiunea int)x10 octeti;
	//int* v1;//alocare dinamica cu ajutorul unui pointer cu adresa catre primul element;

		//declaram un vector de calculatoare
	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++) {
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}

	afisareVectorCalculatoare(calculatoare, nrCalculatoare);
	int nrCalculatoareCopiate = 3;
	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);
	printf("\n\n");
	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoareCopiate);

	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);
	printf("\n\n");
	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);

	dezalocare(&calculatoare, &nrCalculatoare);
}