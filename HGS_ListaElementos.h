#ifndef HGS_LISTAELEMENTOS_H_INCLUDED
#define HGS_LISTAELEMENTOS_H_INCLUDED

typedef struct HGS_Elemento HGS_Elemento;
typedef struct HGS_ListaElementos HGS_ListaElementos;


#include "HGS_FormaColision.h"


HGS_ListaElementos * HGS_ListaElementosCrea();

HGS_Elemento * HGS_ListaElementosCreaElemento(int * grupo, void * datos, HGS_FormaColision * formaColision, int marcaPosicion);

int HGS_ListaElementosCogerMarca(HGS_Elemento * elemento);

int * HGS_ListaElementosCogerDatos(HGS_Elemento * elemento);

int HGS_ListaElementosCogerGrupo(HGS_Elemento * elemento);

void HGS_ListaElementosInsertaElemento(HGS_ListaElementos * lista, HGS_Elemento * elemento);

void HGS_ListaElementosExtraeElemento(HGS_ListaElementos * lista, HGS_Elemento * elemento);

HGS_Elemento * HGS_ListaElementosSiguienteElemento(HGS_Elemento * elemento);

HGS_Elemento * HGS_ListaElementosAnteriorElemento(HGS_Elemento * elemento);

void HGS_ListaElementosLibera(HGS_ListaElementos * lista);

void HGS_ListaElementosLiberaElemento(HGS_Elemento * elemento);



#endif // HGS_LISTAELEMENTOS_H_INCLUDED
