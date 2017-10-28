#ifndef HGS_FORMAGEOMETRICA_H_INCLUDED
#define HGS_FORMAGEOMETRICA_H_INCLUDED

#define HGS_FORMA_RECTANGULO    1
#define HGS_FORMA_CIRCULO       2
#define HGS_FORMA_PUNTO         4

/**
*   Estructura de datos de una formaGeometrica.
*/
typedef struct HGS_FormaGeometrica HGS_FormaGeometrica;


#include <stdlib.h>
#include "HGS_Rectangulo.h"
#include "HGS_Circulo.h"
#include "HGS_Punto.h"

/**
*   Crea una forma geométrica.
*
*   @param HGS_FORMA: Sirve para indicar la forma geometrica deseada.
*   @param x: Coordenada x del punto superior izquierda del rectangulo que contiene a la forma
*             geométrica inscrita en él.
*   @param y: Coordenada y del punto superior izquierda del rectangulo que contiene a la forma
*             geométrica inscrita en él.
*   @param w: Ancho del rectangulo que contiene a la forma
*             geométrica inscrita en él.
*   @param h: Alto del rectangulo que contiene a la forma
*             geométrica inscrita en él. En el caso del circulo, h se cambiara por el valor de w.
*
*   @return Devuelve un puntero a la formaGeometrica.
*/
HGS_FormaGeometrica * HGS_FormaGeometricaCrea(int HGS_FORMA, double x, double y, double w, double h);

/**
*   Asigna una posicion a la formaGeometrica. La posicion es el punto superior izquierda del
*   rectangulo que contiene la formaGeometrica.
*
*   @param forma: FormaGeometrica a la que se le asignara la posicion.
*   @param x: Coordenada x que se le asignara a la formaGeometrica.
*   @param y: Coordenada y que se le asignara a la formaGeometrica.
*/
void HGS_FormaGeometricaAsignarPosicion(HGS_FormaGeometrica * forma, double x, double y);

/**
*   Funcion que retorna el tipo de una formaGeometrica.
*
*   @param forma: FormaGeometrica de la que se cogera la informacion.
*
*   @return Devuelve el tipo de la formaGeometrica.
*/
int HGS_FormaGeometricaCogerTipo(HGS_FormaGeometrica * forma);

/**
*   Funcion que devuelve la posicion de la formaGemetrica.
*
*   @param forma: FormaGeometrica de la que se cogera la posicion.
*   @param x: Variable que se rellenara con la coordenada x de la posicion de la
*             formaGeometrica.
*   @param y: Variable que se rellenara con la coordenada y de la posicion de la
*             formaGeometrica.
*/
void HGS_FormaGeometricaCogerPosicion(HGS_FormaGeometrica * forma, double * x, double * y);

/**
*   Funcion para coger toda la informacion sobre una formaColision.
*
*   @param forma: FormaColision de la cual se va a coger la informacion.
*   @param x: Variable que se rellenara con la siguiente informacion:
*               - Si la forma es un rectangulo: Coordenada x del punto superior izquierda
*                 del rectangulo.
*               - Si la forma es un circulo: Coordenada x del centro.
*               - Si la forma es un punto: Coordenada x del punto.
*   @param y: Variable que se rellenara con la siguiente informacion:
*               - Si la forma es un rectangulo: Coordenada y del punto superior izquierda
*                 del rectangulo.
*               - Si la forma es un circulo: Coordenada y del centro.
*               - Si la forma es un punto: Coordenada y del punto.
*   @param wr: Variable que se rellenara con la siguiente informacion:
*               - Si la forma es un rectangulo: Ancho del rectangulo.
*               - Si la forma es un circulo: Radio del circulo.
*   @param h: Variable que se rellenara con la siguiente informacion:
*               - Si la forma es un rectangulo: Alto del rectangulo.
*
*   @return Devuelve el tipo de la formaGeometrica correspondiente a las macros
*           HGS_FORMA_RECTANGULO, HGS_FORMA_CIRCULO y HGS_FORMA_PUNTO.
*/
int HGS_FormaGeometricaCoger(HGS_FormaGeometrica * forma, double * x, double * y, double * wr, double * h);

/**
*   Mueve en (x,y) unidades la posicion de la formaGeometrica.
*
*   @param forma: FormaGeometrica que se va a mover.
*   @param x: Cantidad que se sumara a la coordenada x de la formaGeometric.
*   @param y: Cantidad que se sumara a la coordenada y de la formaGeometric.
*/
void HGS_FormaGeometricaMover(HGS_FormaGeometrica * forma, double x, double y);

/**
*   Esta funcion devuelve el rectangulo que contiene a la forma geometrica inscrita en el.
*
*   @param forma: FormaGeometrica de la que se cogera su rectangulo que contiene a dicha formaGeometrica.
*   @param x: Coordenada x del rectangulo.
*   @param y: Coordenada y del rectangulo.
*   @param w: Ancho del rectangulo.
*   @param h: Alto del rectangulo.
*/
void HGS_FormaGeometricaCogerRectContenedor(HGS_FormaGeometrica * forma, double * x, double * y, double * w, double * h);

/**
*   Libera la memoria de una formaGeometrica.
*
*   @param forma: FormaGeometrica de la que se va a liberar la memoria.
*/
void HGS_FormaGeometricaLibera(HGS_FormaGeometrica * forma);

/**
*   Funcion para detectar si dos formaGeometrica intersectan.
*
*   @param forma1: Una de las formaGeometricas a estudiar.
*   @param forma2: Una de las formaGeometricas a estudiar.
*
*   @return La funcion retorna 1 si las formaGeometricas intersectan y 0 en caso contrario.
*/
int HGS_FormaGeometricaInterseccion(HGS_FormaGeometrica * forma1, HGS_FormaGeometrica * forma2);


#endif // HGS_FORMAGEOMETRICA_H_INCLUDED
