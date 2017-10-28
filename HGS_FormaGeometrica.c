
#include "HGS_FormaGeometrica.h"

//FUNCIONES ESTATICAS
int HGS_RectanguloCirculoInterseccion(HGS_FormaGeometrica * rect, HGS_FormaGeometrica * circ);
int HGS_PuntoRectanguloInterseccion(HGS_FormaGeometrica * punto, HGS_FormaGeometrica * rect);
int HGS_PuntoCirculoInterseccion(HGS_FormaGeometrica * punto, HGS_FormaGeometrica * circ);



typedef struct HGS_FormaGeometrica{

    int tipo;
    union{
        HGS_Circulo * circulo;
        HGS_Rectangulo * rectangulo;
        HGS_Punto * punto;
    }forma;

}HGS_FormaGeometrica;


HGS_FormaGeometrica * HGS_FormaGeometricaCrea(int HGS_FORMA, double x, double y, double w, double h){

    double radio;

    HGS_FormaGeometrica * forma= malloc(sizeof(struct HGS_FormaGeometrica));

    forma->tipo= HGS_FORMA;
    switch(HGS_FORMA){
        case HGS_FORMA_RECTANGULO:
            forma->forma.rectangulo= HGS_RectanguloCrea(x,y,w,h);
            break;
        case HGS_FORMA_CIRCULO:
            radio= w/2.0;
            forma->forma.circulo= HGS_CirculoCrea(x,y,radio);
            break;
        case HGS_FORMA_PUNTO:
            forma->forma.punto= HGS_PuntoCrea(x,y);
            break;
    }

    return forma;

}

void HGS_FormaGeometricaLibera(HGS_FormaGeometrica * forma){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloLibera(forma->forma.rectangulo);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoLibera(forma->forma.circulo);
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoLibera(forma->forma.punto);
            break;
    }

}

void HGS_FormaGeometricaAsignarPosicion(HGS_FormaGeometrica * forma, double x, double y){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloAsignarPosicion(forma->forma.rectangulo,x,y);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoAsignarPosicion(forma->forma.circulo,x,y);
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoAsignar(forma->forma.punto,x,y);
            break;
    }

}

int HGS_FormaGeometricaCogerTipo(HGS_FormaGeometrica * forma){

    return forma->tipo;

}

void HGS_FormaGeometricaCogerPosicion(HGS_FormaGeometrica * forma, double * x, double * y){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloCogerPosicion(forma->forma.rectangulo,x,y);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoCogerPosicion(forma->forma.circulo,x,y);
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoCoger(forma->forma.punto,x,y);
            break;
    }

}

int HGS_FormaGeometricaCoger(HGS_FormaGeometrica * forma, double * x, double * y, double * wr, double * h){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloCoger(forma->forma.rectangulo,x,y,wr,h);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoCoger(forma->forma.circulo,x,y,wr);
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoCoger(forma->forma.punto,x,y);
            break;
    }

    return forma->tipo;

}

void HGS_FormaGeometricaMover(HGS_FormaGeometrica * forma, double x, double y){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloMover(forma->forma.rectangulo,x,y);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoMover(forma->forma.circulo,x,y);
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoMover(forma->forma.punto,x,y);
            break;
    }

}

void HGS_FormaGeometricaCogerRectContenedor(HGS_FormaGeometrica * forma, double * x, double * y, double * w, double * h){

    switch(forma->tipo){
        case HGS_FORMA_RECTANGULO:
            HGS_RectanguloCoger(forma->forma.rectangulo,x,y,w,h);
            break;
        case HGS_FORMA_CIRCULO:
            HGS_CirculoCoger(forma->forma.circulo,x,y,w);
            (*x)-= *w;
            (*y)-= *w;
            (*w)*= 2;
            (*h)= *w;
            break;
        case HGS_FORMA_PUNTO:
            HGS_PuntoCoger(forma->forma.punto,x,y);
            *w= 0;
            *h= 0;
            break;
    }

}

int HGS_FormaGeometricaInterseccion(HGS_FormaGeometrica * forma1, HGS_FormaGeometrica * forma2){

    int tipoInterseccion= forma1->tipo | forma2->tipo;

    switch(tipoInterseccion){
        case HGS_FORMA_RECTANGULO | HGS_FORMA_RECTANGULO:
            return HGS_RectanguloInterseccion(forma1->forma.rectangulo,forma2->forma.rectangulo);
        case HGS_FORMA_CIRCULO | HGS_FORMA_CIRCULO:
            return HGS_CirculoInterseccion(forma1->forma.circulo,forma2->forma.circulo);
        case HGS_FORMA_RECTANGULO | HGS_FORMA_CIRCULO:
            if (forma1->tipo==HGS_FORMA_RECTANGULO)
                return HGS_RectanguloCirculoInterseccion(forma1,forma2);
            else
                return HGS_RectanguloCirculoInterseccion(forma2,forma1);
        case HGS_FORMA_PUNTO | HGS_FORMA_PUNTO:
            return HGS_PuntoInterseccion(forma1->forma.punto,forma2->forma.punto);
        case HGS_FORMA_PUNTO | HGS_FORMA_RECTANGULO:
            if (forma1->tipo==HGS_FORMA_PUNTO)
                return HGS_PuntoRectanguloInterseccion(forma1,forma2);
            else
                return HGS_PuntoRectanguloInterseccion(forma2,forma1);
        case HGS_FORMA_PUNTO==HGS_FORMA_CIRCULO:
            if (forma1->tipo==HGS_FORMA_PUNTO)
                return HGS_PuntoCirculoInterseccion(forma1,forma2);
            else
                return HGS_PuntoCirculoInterseccion(forma2,forma1);
    }

    //No deberia llegar nunca.
    return 0;

}



//FUNCIONES ESTATICAS


int HGS_RectanguloCirculoInterseccion(HGS_FormaGeometrica * rect, HGS_FormaGeometrica * circ){

    double rectX,rectY,rectW,rectH;
    double circX,circY,circR;
    HGS_RectanguloCoger(rect->forma.rectangulo,&rectX,&rectY,&rectW,&rectH);
    HGS_CirculoCoger(circ->forma.circulo,&circX,&circY,&circR);

    //Banda vertical
    if (circX>rectX && circX<rectX+rectW){
        //Centro dentro del rectangulo
        if (circY>rectY && circY<rectY+rectH){
            return 1;
        }
        //Centro encima del rectangulo
        if (circY<=rectY){
            double dist= rectY-circY;
            if (dist<circR){
                return 1;
            }
        }
        //Centro debajo del rectangulo
        else{
            double dist= circY-(rectY+rectH);
            if (dist<circR){
                return 1;
            }
        }
    }
    //Banda horizontal
    else if (circY>rectY && circY<rectY+rectH){
        //Centro dentro del rectangulo
        if (circX>rectX && circX<rectX+rectW){
            return 1;
        }
        //Centro a la izquierda del rectangulo
        if (circX<=rectX){
            double dist= rectX-circX;
            if (dist<circR){
                return 1;
            }
        }
        //Centro a la derecha del rectangulo
        else{
            double dist= circX-(rectX+rectW);
            if (dist<circR){
                return 1;
            }
        }
    }
    //En ninguna banda
    else{
        //Centro a la izquierda del rectangulo
        if (circX<=rectX){
            //Centro encima del rectangulo
            if (circY<=rectY){
                double diffX= rectX-circX;
                double diffY= rectY-circY;
                double dist= sqrt(pow(diffX,2)+pow(diffY,2));
                if (dist<circR){
                    return 1;
                }
            }
            //Centro debajo del rectangulo
            else{
                double diffX= rectX-circX;
                double diffY= circY-(rectY+rectH);
                double dist= sqrt(pow(diffX,2)+pow(diffY,2));
                if (dist<circR){
                    return 1;
                }
            }
        }
        //Centro a la derecha del rectangulo
        else{
            //Centro encima del rectangulo
            if (circY<=rectY){
                double diffX= circX-(rectX+rectW);
                double diffY= rectY-circY;
                double dist= sqrt(pow(diffX,2)+pow(diffY,2));
                if (dist<circR){
                    return 1;
                }
            }
            //Centro debajo del rectangulo
            else{
                double diffX= circX-(rectX+rectW);
                double diffY= circY-(rectY+rectH);
                double dist= sqrt(pow(diffX,2)+pow(diffY,2));
                if (dist<circR){
                    return 1;
                }
            }
        }
    }

    return 0;

}

int HGS_PuntoRectanguloInterseccion(HGS_FormaGeometrica * punto, HGS_FormaGeometrica * rect){

    int interseccion= 0;
    double xPunto,yPunto;
    double xRect,yRect,wRect,hRect;

    HGS_PuntoCoger(punto->forma.punto,&xPunto,&yPunto);
    HGS_RectanguloCoger(rect->forma.rectangulo,&xRect,&yRect,&wRect,&hRect);

    if (xPunto>xRect && xPunto<xRect+wRect && yPunto>yRect && yPunto<yRect+hRect) interseccion= 1;

    return interseccion;

}

int HGS_PuntoCirculoInterseccion(HGS_FormaGeometrica * punto, HGS_FormaGeometrica * circ){

    int interseccion= 0;
    double xPunto,yPunto;
    double xCirc,yCirc,rCirc;

    HGS_PuntoCoger(punto->forma.punto,&xPunto,&yPunto);
    HGS_CirculoCoger(circ->forma.circulo,&xCirc,&yCirc,&rCirc);

    double diffX= xPunto-xCirc;
    double diffY= yPunto-yCirc;
    if (sqrt(diffX*diffX+diffY*diffY)<rCirc) interseccion= 1;

    return interseccion;

}
