//Elementele listei se citesc din fisier
//Se pot insera la inceput, la final sau in ordine crescatoare
//Putem sterge un element de pe o pozitie aleasa

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Auto Auto;
typedef struct Nod Nod;

struct Auto {
    char* marca;
    int nrUsi;
};

struct Nod {
    Auto info;
    Nod* next;
};

Auto initializare(char* marca, int nrUsi) {
    Auto automobil;
    automobil.marca = (char*)malloc((strlen(marca) + 1) * sizeof(char));
    strcpy(automobil.marca, marca);
    automobil.nrUsi = nrUsi;
    return automobil;
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        printf("%s %d\n", cap->info.marca, cap->info.nrUsi);
        cap = cap->next;
    }
}

Nod* inserareInceput(Nod* cap, Auto a) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info.marca = (char*)malloc(sizeof(char) * (strlen(a.marca) + 1));
    strcpy(nou->info.marca, a.marca);
    nou->info.nrUsi = a.nrUsi;
    nou->next = cap;
    cap = nou;
    return cap;
}

Nod* inserareFinal(Nod* cap, Auto a) {
    Nod* aux = cap;
    Nod* nou;
    nou = (Nod*)malloc(sizeof(Nod));
    nou->info = a;
    nou->next = NULL;
    if (cap == NULL) {
        cap = nou;
    }
    else {
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
    return cap;
}

Nod* stergereNodPozitieData(Nod* cap, int pozitie) {
    if (cap == NULL) {
        printf("Lista e goala.\n");
        return NULL;
    }

    if (pozitie == 0) {
        Nod* temp = cap;
        cap = cap->next;
        free(temp->info.marca);
        free(temp);
        return cap;
    }

    Nod* predecesor = cap;
    int nr = 0;
    while (nr < pozitie - 1 && predecesor->next != NULL) {
        predecesor = predecesor->next;
        nr++;
    }

    if (predecesor->next == NULL || pozitie < 0 || pozitie > nr + 1) {
        printf("Pozitie invalida!\n");
        return cap;
    }

    Nod* temp = predecesor->next;//retin nodul pe care vr sa-l sterg
    predecesor->next = temp->next;//atribuie val nodului urm celui pe care il sterg
    free(temp->info.marca);
    free(temp);
    return cap;
}

Nod* inserareCrescatoare(Nod* cap, Auto a) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info.marca = (char*)malloc(sizeof(char) * (strlen(a.marca) + 1));
    strcpy(nou->info.marca, a.marca);
    nou->info.nrUsi = a.nrUsi;
    nou->next = NULL;

    if (cap == NULL || a.nrUsi < cap->info.nrUsi) {
        nou->next = cap;
        cap = nou;
        return cap;
    }
    Nod* temp = cap;
    while (temp->next != NULL && temp->next->info.nrUsi < a.nrUsi) {
        temp = temp->next;
    }
    nou->next = temp->next;
    temp->next = nou;
    return cap;
}

void main() {
    int n;
    char buffer[20];
    Auto a;
    Nod* cap = NULL;
    
    FILE* f = fopen("masini.txt", "r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%s", buffer);
        a.marca = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(a.marca, buffer);
        fscanf(f, "%d", &a.nrUsi);
        //cap = inserareInceput(cap, a);
        //cap = inserareFinal(cap, a);
        cap = inserareCrescatoare(cap, a);
    }
    fclose(f);
    afisareLista(cap);
    printf("\n");

    /*stergereNodPozitieData(cap, 3);
    afisareLista(cap);
    printf("\n");*/

    /*inserareCrescatoare(cap, initializare("Ford", 3));
    afisareLista(cap);
    printf("\n");*/

}
