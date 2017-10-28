#ifndef HGS_CAMARA_H_INCLUDED
#define HGS_CAMARA_H_INCLUDED


#include "HGS_Sprite.h"

/**
*   Funcion que rellena las variables x e y con las coordenadas correspondientes
*   con el punto superior izquierda de la camara.
*
*   @param x: Variable que se rellena con la coordenada x de la camara.
*   @param y: Variable que se rellena con la coordenada y de la camara.
*/
void HGS_CamaraCogerPosicion(double * x, double * y);

/**
*   Asigna limites al movimiento de la camara. Si la camara se sale de los limites,
*   se rectificara su posicion.
*       Si el limite izquierdo es mayor que el limite derecho, o el limite superior
*   es mayor que el limite inferior, la funcion no hara nada.
*
*   @param xIzq: Limite izquierdo. La coordenada x del punto superior izquierdo de la
*                camara no podra ser menor a este valor.
*   @param xDer: Limite derecho. La coordenada x del punto superior izquierdo de la
*                camara no podra ser mayor a este valor.
*   @param ySup: Limite superior. La coordenada y del punto superior izquierdo de la
*                camara no podra ser menor a este valor.
*   @param yInf: Limite inferior. La coordenada y del punto superior izquierdo de la
*                camara no podra ser mayor a este valor.
*/
void HGS_CamaraAsignarLimites(double xIzq, double xDer, double ySup, double yInf);

/**
*   Quita los limites de la camara.
*/
void HGS_CamaraQuitarLimites();

/**
*   Funcion para que la camara siga el movimiento de un sprite.
*
*   @param sprite: Sprite que se va a seguir.
*/
void HGS_CamaraSeguirSprite(HGS_Sprite * sprite);

/**
*   Asigna a la camara un desvio.
*   INFO: El calculo de la posicion de la camara se efectua mediante la suma
*         de la posicion propiamente dicha y el desvio.
*
*   @param desviox: El desvio de la coordenada x.
*   @param desvioy: El desvio de la coordenada y.
*/
void HGS_CamaraDesviarCamara(double desviox, double desvioy);

/**
*   Deja de seguir a un sprite. Si no se seguia a ningun sprite la funcion no hace nada.
*/
void HGS_CamaraNoSeguirSprite();

/**
*   Asigna una posicion a la camara si no se sigue a ningun sprite.
*
*   @param x: Coordenada x que se le asignara a la camara.
*   @param y: Coordenada y que se le asignara a la camara.
*/
void HGS_CamaraAsignarPosicion(double x, double y);

/**
*   Mueve la posicion de la camara a una velocidad de (x,y) unidades por segundo.
*
*   @param x: Velocidad de movimiento de la coordenada x.
*   @param y: Velocidad de movimiento de la coordenada y.
*/
void HGS_CamaraMover(double x, double y);

/**
*   Ejecutando esta funcion se bloqueara el movimiento horizontal de la camara.
*/
void HGS_CamaraBloquearMovHorizontal();

/**
*   Ejecutando esta funcion se bloqueara el movimiento vertical de la camara.
*/
void HGS_CamaraBloquearMovVertical();

/**
*   Desbloquea la camara si ha estado bloqueada anteriormente.
*/
void HGS_CamaraDesbloquear();


#endif // HGS_CAMARA_H_INCLUDED
