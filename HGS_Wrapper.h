#ifndef HGS_WRAPPER_H_INCLUDED
#define HGS_WRAPPER_H_INCLUDED

/**
*   HGS_Wrapper es un pequeño motor gráfico que emplea funciones de SDL.
*   Permite diseñar un videojuego en 2D de manera sencilla.
*   Contiene funciones para manejar la ventana, la cámara, animaciones,
*   detector de colisiones y más.
*   Esto es Open Source, así que siéntete libre de mirar y aprender.
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
