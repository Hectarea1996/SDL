#ifndef HGS_WRAPPER_H_INCLUDED
#define HGS_WRAPPER_H_INCLUDED

/**
*   HGS_Wrapper es un peque�o motor gr�fico que emplea funciones de SDL.
*   Permite dise�ar un videojuego en 2D de manera sencilla.
*   Contiene funciones para manejar la ventana, la c�mara, animaciones,
*   detector de colisiones y m�s.
*   Esto es Open Source, as� que si�ntete libre de mirar y aprender.
*/


#include "HGS_Control.h"
#include "HGS_Camara.h"
#include "HGS_Imagen.h"
#include "HGS_Rejilla.h"
#include "HGS_FormaColision.h"
#include "HGS_Sprite.h"
#include "HGS_Ventana.h"
#include "HGS_ES.h"


/**
*   Inicializa el subsistema de video.
*/
void HGS_WrapperInicializar();

/**
*   Libera todos los subsistemas.
*/
void HGS_WrapperLiberar();





#endif // HGS_WRAPPER_H_INCLUDED
