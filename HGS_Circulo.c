
#include "HGS_Circulo.h"


typedef struct HGS_Circulo{

    double x;
    double y;
    double r;

}HGS_Circulo;



HGS_Circulo * HGS_CirculoCrea(double x, double y, double r){

    HGS_Circulo * nuevo= malloc(sizeof(struct HGS_Circulo));

    nuevo->x= x;
    nuevo->y= y;
    nuevo->r= r;

    return nuevo;

}

void HGS_CirculoCogerPosicion(HGS_Circulo * circ, double * x, double * y){

    if (x!=NULL)
        *x= circ->x;
    if (y!=NULL)
        *y= circ->y;

}

double HGS_CirculoCogerRadio(HGS_Circulo * circ){

    return circ->r;

}

void HGS_CirculoCoger(HGS_Circulo * circulo, double * x, double * y, double * r){

    if (x!=NULL)
        *x= circulo->x;
    if (y!=NULL)
        *y= circulo->y;
    if (r!=NULL)
        *r= circulo->r;

}

void HGS_CirculoAsignarPosicion(HGS_Circulo * circulo, double x, double y){

    circulo->x= x;
    circulo->y= y;

}

void HGS_CirculoMover(HGS_Circulo * circulo, double x, double y){

    circulo->x+= x;
    circulo->y+= y;

}

int HGS_CirculoInterseccion(HGS_Circulo * circ1, HGS_Circulo * circ2){

    double difX= circ1->x-circ2->x;
    double difY= circ1->y-circ2->y;
    double distancia= sqrt(pow(difX,2)+pow(difY,2));
    if (distancia<circ1->r+circ2->r)
        return 1;
    return 0;

}

void HGS_CirculoLibera(HGS_Circulo * circulo){

    free(circulo);

}



