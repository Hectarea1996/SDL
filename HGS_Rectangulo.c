
#include "HGS_Rectangulo.h"


typedef struct HGS_Rectangulo{

    double x;
    double y;
    double w;
    double h;

}HGS_Rectangulo;


HGS_Rectangulo * HGS_RectanguloCrea(double x, double y, double w, double h){

    HGS_Rectangulo * nuevo= malloc(sizeof(struct HGS_Rectangulo));

    nuevo->x= x;
    nuevo->y= y;
    nuevo->w= w;
    nuevo->h= h;

    return nuevo;

}

void HGS_RectanguloCogerPosicion(HGS_Rectangulo * rectangulo, double * x, double * y){

    if (x!=NULL)
        *x= rectangulo->x;
    if (y!=NULL)
        *y= rectangulo->y;

}

void HGS_RectanguloCoger(HGS_Rectangulo * rectangulo, double * x, double * y, double * w, double * h){

    if (x!=NULL)
        *x= rectangulo->x;
    if (y!=NULL)
        *y= rectangulo->y;
    if (w!=NULL)
        *w= rectangulo->w;
    if (h!=NULL)
        *h= rectangulo->h;

}

void HGS_RectanguloAsignarPosicion(HGS_Rectangulo * rectangulo, double x, double y){

    rectangulo->x= x;
    rectangulo->y= y;

}

void HGS_RectanguloMover(HGS_Rectangulo * rectangulo, double x, double y){

    rectangulo->x+= x;
    rectangulo->y+= y;

}

int HGS_RectanguloInterseccion(HGS_Rectangulo * rect1, HGS_Rectangulo * rect2){

    if (rect1->x<rect2->x+rect2->w &&
        rect1->y<rect2->y+rect2->h &&
        rect2->x<rect1->x+rect1->w &&
        rect2->y<rect1->y+rect1->h)
            return 1;
    return 0;

}

void HGS_RectanguloLibera(HGS_Rectangulo * rectangulo){

    free(rectangulo);

}
