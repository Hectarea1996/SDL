#ifndef HGS_CIRCULO_H_INCLUDED
#define HGS_CIRCULO_H_INCLUDED

/**
*   Estructura de datos de un circulo.
*/
typedef struct HGS_Circulo HGS_Circulo;

#include <math.h>
#include <stdlib.h>

/**
*   Crea la estructura de datos de un circulo.
*
*   @param x: Coordenada x del circulo.
*   @param y: Coordenada y del circulo.
*   @param r: Radio del circulo.
*
*   @return Se devuelve un puntero a la estructura de datos del circulo.
*/
HGS_Circulo * HGS_CirculoCrea(double x, double y, double r);

/**
*   Permite coger la posicion del centro del circulo.
*
*   @param circulo: El circulo del que se quiere la informacion.
*   @param x: Puntero a la variable en la que se rellenara la informacion
*                correspondiente a la coordenada x del circulo.
*   @param y: Puntero a la variable en la que se rellenara la informacion
*                correspondiente a la coordenada y del circulo.
*/
void HGS_CirculoCogerPosicion(HGS_Circulo * circ, double * x, double * y);

/**
*   Permite recuperar la informacion de un circulo.
*
*   @param circulo: El circulo del que se quiere la informacion.
*   @param x: Puntero a la variable en la que se rellenara la informacion
*                correspondiente a la coordenada x del circulo.
*   @param y: Puntero a la variable en la que se rellenara la informacion
*                correspondiente a la coordenada y del circulo.
*   @param r: Puntero a la variable en la que se rellenara la informacion
*                correspondiente al radio del circulo.
*/
void HGS_CirculoCoger(HGS_Circulo * circulo, double * x, double * y, double * r);

/**
*   Permite recuperar el radio del circulo.
*
*   @param circ: Circulo del cual se recuperara el radio.
*
*   @return Se devuelve el radio del circulo.
*/
double HGS_CirculoCogerRadio(HGS_Circulo * circ);

/**
*   Funcion para asignarle una posicion al circulo.
*
*   @param circulo: Circulo al que se le asignara la posicion.
*   @param x: Coordenada x que se le asignara al circulo.
*   @param y: Coordenada y que se le asignara al circulo.
*/
void HGS_CirculoAsignarPosicion(HGS_Circulo * circulo, double x, double y);

/**
*   Funcion que incrementara las coordenadas del circulo en la cantidad que
*      se pase como parametro.
*
*   @param circulo: Circulo que se movera.
*   @param x: Cantidad que se incrementara a la coordenada x del circulo.
*   @param y: Cantidad que se incrementara a la coordenada y del circulo.
*/
void HGS_CirculoMover(HGS_Circulo * circulo, double x, double y);

/**
*   Funcion para comprobar si dos circulos intersectan.
*
*   @param circ1: Uno de los circulos.
*   @param circ2: El otro circulo.
*
*   @return Devuelve 1 si los circulos intersectan y 0 en caso contrario.
*/
int HGS_CirculoInterseccion(HGS_Circulo * circ1, HGS_Circulo * circ2);

/**
*   Libera la memoria que ocupa un circulo.
*
*   @param circulo: Circulo que se va a liberar.
*/
void HGS_CirculoLibera(HGS_Circulo * circulo);

#endif // HGS_CIRCULO_H_INCLUDED
