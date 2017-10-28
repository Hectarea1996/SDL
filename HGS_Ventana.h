#ifndef HGS_VENTANA_H_INCLUDED
#define HGS_VENTANA_H_INCLUDED

#include <SDL2/SDL.h>
#include "stdlib.h"
#include "stdio.h"
#include "HGS_Camara.h"

/**
*   Crea una ventana.
*
*   @param titulo: Especifica el titulo de la ventana.
*   @param w: Ancho de la ventana.
*   @param h: Altura de la ventana.
*   @param fullscreen: Si es 0, la ventana se creara en modo ventana. En caso contrario
*                      la ventana se creara en modo pantalla completa.
*/
void HGS_VentanaCrea(const char * titulo, int w, int h, int fullscreen);

/**
*   Funcion para reflejar todos los cambios de dibujo realizados sobre la ventana.
*/
void HGS_VentanaActualiza();

/**
*   Libera y cierra la ventana.
*/
void HGS_VentanaLibera();


#endif // HGS_VENTANA_H_INCLUDED
