
#include "HGS_Punto.h"

typedef struct HGS_Punto{

    double x;
    double y;

}HGS_Punto;

HGS_Punto * HGS_PuntoCrea(double x, double y){

    HGS_Punto * nuevo= malloc(sizeof(HGS_Punto));

    nuevo->x= x;
    nuevo->y= y;

    return nuevo;

}

void HGS_PuntoLibera(HGS_Punto * punto){

    free(punto);

}

void HGS_PuntoCoger(HGS_Punto * punto, double * x, double * y){

    *x= punto->x;
    *y= punto->y;

}

void HGS_PuntoAsignar(HGS_Punto * punto, double x, double y){

    punto->x= x;
    punto->y= y;

}

void HGS_PuntoMover(HGS_Punto * punto, double x, double y){

    punto->x+= x;
    punto->y+= y;

}

int HGS_PuntoInterseccion(HGS_Punto * punto1, HGS_Punto * punto2){

    return punto1->x==punto2->x && punto1->y==punto2->y;

}
