
#include "HGS_ListaElementos.h"

typedef struct HGS_Elemento{

    int * grupo;
    void * datos;
    HGS_FormaColision * forma;    //Para saber su posicion.
    int marcaPosicion;      //1 si esta en el extremo derecho, 2 si esta en la parte inferior, 3 si esta en el final, y 0 en otro caso.
    struct HGS_Elemento * sig;
    struct HGS_Elemento * ant;

}HGS_Elemento;


typedef struct HGS_ListaElementos{

    HGS_Elemento * primerElemento;

}HGS_ListaElementos;


HGS_ListaElementos * HGS_ListaElementosCrea(){

    HGS_ListaElementos * nueva= malloc(sizeof(struct HGS_ListaElementos));
    nueva->primerElemento= NULL;

    return nueva;

}

HGS_Elemento * HGS_ListaElementosCreaElemento(int * grupo, void * datos, HGS_FormaColision * forma, int marcaPosicion){

    HGS_Elemento * nuevo= malloc(sizeof(struct HGS_Elemento));

    nuevo->grupo= grupo;
    nuevo->datos= datos;
    nuevo->forma= forma;
    nuevo->marcaPosicion= marcaPosicion;
    nuevo->ant= NULL;
    nuevo->sig= NULL;

    return nuevo;

}

int HGS_ListaElementosCogerMarca(HGS_Elemento * elemento){

    return elemento->marcaPosicion;

}

int HGS_ListaElementosCogerGrupo(HGS_Elemento * elemento){

    return *elemento->grupo;

}

int * HGS_ListaElementosCogerDatos(HGS_Elemento * elemento){

    return elemento->datos;

}


void HGS_ListaElementosInsertaElemento(HGS_ListaElementos * lista, HGS_Elemento * elemento){

    if(lista->primerElemento==NULL){
        lista->primerElemento= elemento;
        elemento->ant= NULL;
        elemento->sig= NULL;
    }
    else{
        elemento->sig= lista->primerElemento;
        lista->primerElemento->ant= elemento;
        lista->primerElemento= elemento;
        elemento->ant= NULL;
    }

}

void HGS_ListaElementosExtraeElemento(HGS_ListaElementos * lista, HGS_Elemento * elemento){

    HGS_Elemento * izq= elemento->ant;
    HGS_Elemento * der= elemento->sig;
    elemento->ant= NULL;
    elemento->sig= NULL;

    if (izq==NULL && der==NULL){
        if (lista->primerElemento==elemento){
            lista->primerElemento= NULL;
        }
    }
    else{
        if (izq!=NULL)
            izq->sig= der;
        else if(lista->primerElemento==elemento)
            lista->primerElemento= der;
        if (der!=NULL)
            der->ant= izq;
    }

}

HGS_Elemento * HGS_ListaElementosSiguienteElemento(HGS_Elemento * elemento){

    return elemento->sig;

}

HGS_Elemento * HGS_ListaElementosAnteriorElemento(HGS_Elemento * elemento){

    return elemento->ant;

}

void HGS_ListaElementosLibera(HGS_ListaElementos * lista){

    free(lista);

}

void HGS_ListaElementosLiberaElemento(HGS_Elemento * elemento){

    free(elemento);

}

