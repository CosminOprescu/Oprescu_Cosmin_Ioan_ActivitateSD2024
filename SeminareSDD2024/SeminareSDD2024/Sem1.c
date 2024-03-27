//60% examenul; 40%seminarul - 20% testul sapt 6-7(dupa vectori liste stive cozi hashtable) + 20% activitate seminar
//(de incarcar laboratoarele pe github + codat la tabla + test grila)
#include <stdio.h>
#include <malloc.h>

struct Masina {
	//nu avem metode in interiorul structurii
	char* marca;
	float capacitateCilindrica;
	int an;
};

void afisareMasina(const struct Masina* m) {
	if (m->marca != NULL) {
		printf("Marca:%s\n", m->marca);
	}
	printf("Capacitate Cilindrica:%5.2f\n", m->capacitateCilindrica);
	printf("An:%d\n\n", m->an);
}

struct Masina initializareMasina(const char* marca, int an, float cc) {
	struct Masina m;
	m.an = an;
	m.capacitateCilindrica = cc;
	if (marca != NULL) {
		m.marca = malloc(strlen(marca) + 1);
		strcpy(m.marca, marca);
	}
	else {
		m.marca = malloc(strlen("N/A") + 1);
		strcpy(m.marca, "N/A");
	}
	return m;
}

void dezalocareMasina(struct Masina* masina) {//fol pointer pt ca si la afisare am fol si asa se va afisa masina fara marca dupa ce o sterg
	free(masina->marca);//eliberam memoria pentru ca marca e vector de char
	masina->marca = NULL;
}

int main() {
	struct Masina masina1;
	//Dacia
	masina1.marca = (char*)malloc(sizeof(char) * (strlen("Dacia") + 1));
	//malloc returneaza pointer la void, adk un tip generic de data la care fol cast explicit pt ce tip de data am nevoie
	strcpy(masina1.marca, "Dacia");
	masina1.capacitateCilindrica = 1.9;
	masina1.an = 2023;

	afisareMasina(&masina1);
	dezalocareMasina(&masina1);

	struct Masina masina2 = initializareMasina("Seat", 2011, 2.49);

	afisareMasina(&masina2);
	dezalocareMasina(&masina2);

	afisareMasina(&masina2);

	return 0;
}