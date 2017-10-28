#ifndef HGS_PUNTO_H_INCLUDED
#define HGS_PUNTO_H_INCLUDED

typedef struct HGS_Punto HGS_Punto;


#include <stdlib.h>


HGS_Punto * HGS_PuntoCrea(double x, double y);

void HGS_PuntoLibera(HGS_Punto * punto);

void HGS_PuntoCoger(HGS_Punto * punto, double * x, double * y);

void HGS_PuntoAsignar(HGS_Punto * punto, double x, double y);

void HGS_PuntoMover(HGS_Punto * punto, double x, double y);

int HGS_PuntoInterseccion(HGS_Punto * punto1, HGS_Punto * punto2);

#endif // HGS_PUNTO_H_INCLUDED
