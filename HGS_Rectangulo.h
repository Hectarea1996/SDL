#ifndef HGS_RECTANGULO_H_INCLUDED
#define HGS_RECTANGULO_H_INCLUDED

/**
*   Estructura de datos de un rectangulo.
*/
typedef struct HGS_Rectangulo HGS_Rectangulo;

#include <stdlib.h>

/**
*   Funcion que crea un rectangulo.
*
*   @param x: Coordenada x del rectangulo.
*   @param y: Coordenada y del rectangulo.
*   @param w: Ancho del rectangulo.
*   @param h: Alto del rectangulo.
*
*   @return Devuelve un puntero al rectangulo creado.
*/
HGS_Rectangulo * HGS_RectanguloCrea(double x, double y, double w, double h);

/**
*   Funcion que rellena las variables x,y con la posicion del rectangulo.
*
*   @param rectangulo: Rectangulo del que se va a coger la posicion.
*   @param x: Coordenada x del punto superior izquierda del rectangulo.
*   @param y: Coordenada y del punto superior izquierda del rectangulo.
*/
void HGS_RectanguloCogerPosicion(HGS_Rectangulo * rectangulo, double * x, double * y);

/**
*   Funcion que rellena las variables x,y,w,h con informacion sobre el rectangulo.
*
*   @param rectangulo: Rectangulo del que se va a coger la informacion.
*   @param x: Coordenada x del punto superior izquierda del rectangulo.
*   @param y: Coordenada y del punto superior izquierda del rectangulo.
*   @param w: Ancho del rectangulo.
*   @param h: Alto del rectangulo.
*/
void HGS_RectanguloCoger(HGS_Rectangulo * rectangulo, double * x, double * y, double * w, double * h);

/**
*   Asigna una posicion a un rectangulo.
*
*   @param rectangulo: Rectangulo al que se le asignara la posicion.
*
*   @param x: Coordenada x que se le asignara al rectangulo.
*   @param y: Coordenada y que se le asignara al rectangulo.
*/
void HGS_RectanguloAsignarPosicion(HGS_Rectangulo * rectangulo, double x, double y);

/**
*   Mueve el rectangulo una cantidad de (x,y) unidades.
*
*   @param rectangulo: Rectangulo que se va a mover.
*   @param x: Cantidad que se incrementara a la coordenada x del rectangulo.
*   @param y: Cantidad que se incrementara a la coordenada y del rectangulo.
*/
void HGS_RectanguloMover(HGS_Rectangulo * rectangulo, double x, double y);

/**
*   Funcion que estudia si dos rectangulos intersectan.
*
*   @param rect1: Uno de los rectangulos.
*   @param rect2: Uno de los rectangulos.
*
*   @return La funcion devuelve 1 si los rectangulos intersectan y 0 en otro caso.
*/
int HGS_RectanguloInterseccion(HGS_Rectangulo * rect1, HGS_Rectangulo * rect2);

/**
*   Libera la memoria ocupada por un rectangulo.
*
*   @param rectangulo: Rectangulo que se va a liberar.
*/
void HGS_RectanguloLibera(HGS_Rectangulo * rectangulo);


#endif // HGS_RECTANGULO_H_INCLUDED
