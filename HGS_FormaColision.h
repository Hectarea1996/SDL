#ifndef HGS_FORMACOLISION_H_INCLUDED
#define HGS_FORMACOLISION_H_INCLUDED

typedef struct HGS_FormaColision HGS_FormaColision;

#include "HGS_FormaGeometrica.h"
#include "HGS_Sprite.h"
#include "HGS_ListaElementos.h"
#include "HGS_DatosCompartidos.h"

/**
*   INFO: La creacion de una formaColision se realiza con la funcion
*         HGS_RejillaCreaFormaColision(). Ver HGS_Rejilla.h.
*
*   INFO: La posicion de la formaColision se calcula mediante la suma
*         de la posicion del sprite al que sigue (Si no lo sigue, se supondra dicha posicion como (0,0))
*         mas la posicion de la formaColision.
*
*   INFO: La posicion de un rectangulo se corresponde con su punto superior izquierda.
*         La posicion de un circulo se corresponde con su centro.
*/

/**
*   Mueve la formaColision a una velocidad de (relX,relY) unidades por segundo.
*
*   @param forma: FormaColision que se va a mover.
*   @param relX: Velocidad con la que la coordenada x de la formaColision va a variar.
*   @param relY: Velocidad con la que la coordenada y de la formaColision va a variar.
*/
void HGS_FormaColisionMover(HGS_FormaColision * forma, double relX, double relY);

/**
*   Mueve la formaColision a una distancia de (relX,relY) unidades.
*
*   @param forma: FormaColision que se va a mover.
*   @param relX: Distancia que la coordenada x de la formaColision va a variar.
*   @param relY: Distancia que la coordenada y de la formaColision va a variar.
*/
void HGS_FormaColisionMoverRapido(HGS_FormaColision * forma, double relX, double relY);

/**
*   Asigna la posicion a una formaColision.
*   AVISO: Para que la nueva posicion se vea reflejada en la rejilla debemos
*          actualizar la formaColision.
*
*   @param forma: FormaColision a la que se le asignara la posicion.
*   @param relX: Valor que se le asignara a la coordenada x de la formaColision.
*   @param relY: Valor que se le asignara a la coordenada y de la formaColision.
*/
void HGS_FormaColisionAsignarPosicion(HGS_FormaColision * forma, double relX, double relY);

/**
*   Funcion que devuelve el tipo de forma geometrica de la formaColision.
*
*   @param forma: FormaColision de la que se cogera la informacion.
*
*   @return Devuelve el tipo de forma geometrica de la formaColision. Se corresponde
*           con una de las macros HGS_FORMA_RECTANGULO, HGS_FORMA_CIRCULO y HGS_FORMA_PUNTO.
*/
int HGS_FormaColisionCogerTipo(HGS_FormaColision * forma);

/**
*   Rellena las variables x e y con la posicion de la formaColision.
*
*   @param forma: FormaColision de la que se obtendra la posicion.
*
*   @param x: Variable que se rellenara con la coordenada x de la posicion de la
*             formaColision.
*   @param y: Variable que se rellenara con la coordenada y de la posicion de la
*             formaColision.
*/
void HGS_FormaColisionCogerPosicion(HGS_FormaColision * forma, double * x, double * y);

/**
*   Funcion para coger toda la informacion sobre la forma geometrica de la formaColision.
*
*   @param forma: FormaColision de la cual se cogera la informacion.
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
*   @return Devuelve el tipo de la forma de colision correspondiente a las macros
*           HGS_FORMA_RECTANGULO, HGS_FORMA_CIRCULO y HGS_FORMA_PUNTO.
*/
int HGS_FormaColisionCoger(HGS_FormaColision * forma, double * x, double * y, double * wr, double * h);

/**
*   Libera la memoria usada por una formaColision.
*
*   @param forma: FormaColision que se va a liberar.
*/
void HGS_FormaColisionLibera(HGS_FormaColision * forma);



#endif // HGS_FORMACOLISION_H_INCLUDED
