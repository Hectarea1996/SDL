#ifndef HGS_CONTROL_H_INCLUDED
#define HGS_CONTROL_H_INCLUDED

#include "stdio.h"
#include <SDL2/SDL.h>


/**
*   Funcion que actualiza la variable multFrames.
*      La variable multFrames varia conforme la velocidad del juego.
*   Esta variable es usada por funciones de otras librerias de HGS_Wrapper
*   para mantener una velocidad constante en cualquier PC.
*/
void HGS_ControlFrames();

/**
*   Funcion que devuelve un puntero a la variable multFrames.
*   AVISO: Esta variable no esta protegida mediante exclusion mutua.
*             Debe usarse en el mismo hilo que las funciones que especifican
*          el uso de esta variable.
*
*   @return Devuelve el puntero a la variable multFrames.
*/
double * HGS_ControlCogerMultFrames();

#endif // HGS_CONTROL_H_INCLUDED
