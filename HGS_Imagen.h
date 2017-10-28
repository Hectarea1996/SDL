#ifndef HGS_IMAGEN_H_INCLUDED
#define HGS_IMAGEN_H_INCLUDED

/**
*   Estructura de datos de una imagen.
*/
typedef struct HGS_Imagen HGS_Imagen;


#include "HGS_DatosCompartidos.h"
#include "stdlib.h"
#include <SDL/SDL_image.h>

/**
*   Funcion que crea una HGS_Imagen que contiene una unica imagen con formato BMP (cambiara).
*
*   @param nombre: Nombre del archivo a cargar. Se debe incluir la extension del archivo.
*                  Se pueden utilizar tanto rutas absolutas como rutas relativas.
*                  Las rutas relativas se hacen respecto el directorio donde se ejecuta el
*                  programa.
*
*   @return Devuelve un puntero de una HGS_Imagen.
*/
HGS_Imagen * HGS_ImagenCrea(char * nombre);

/**
*   Funcion que crea una HGS_Imagen que contiene varias imagenes con formato BMP (cambiara).
*   Las imagenes se agrupan en animaciones.
*
*   @param nombre: Nombre de la carpeta donde se guardan las imagenes a cargar.
*                  Dentro de dicha carpeta se deben crear carpetas con los nombres
*                  AnimacionX, donde la X para la primera carpeta debe ser 0. La funcion
*                  dejara de buscar cuando no encuentre la carpeta con el proximo numero.
*                  Dentro de cada carpeta AnimacionX las imagenes deben estar ordenadas con
*                  los nombres ImagenY donde Y debe comenzar en 0 para la primera imagen e ir aumentando
*                  para las siguientes.
*                  Se pueden utilizar tanto rutas absolutas como rutas relativas.
*                  Las rutas relativas se hacen respecto el directorio donde se ejecuta el
*                  programa.
*                  EJEMPLO:
*                     CarpetaPersonaje:
*                           - Animacion0:
*                                 · Imagen0
*                                 · Imagen1
*                                 · Imagen2
*                           - Animacion1:
*                                 · Imagen0
*                                 · Imagen1
*                                 · Imagen2
*                                 · Imagen3
*                                 · ...
*                           ...
*
*   @return Devuelve un puntero de una HGS_Imagen.
*/
HGS_Imagen * HGS_ImagenAnimadaCrea(char * carpeta);

/**
*   Funcion para liberar la memoria de una HGS_Imagen.
*
*   @param imagen: Imagen que se va a liberar.
*/
void HGS_ImagenLibera(HGS_Imagen * imagen);


//HILOS

/**
*   Para aumentar la eficiencia del programa se proporcionan las siguientes funciones
*   para ejecutar las funciones de dibujado en un hilo diferente.
*       De esta forma se ejecutan las funciones del programa a la vez que se ejecutan
*   las de dibujado.
*/

/**
*   Funcion que crea el hilo. Este hilo se trata de un bucle infinito que ejecuta en cada iteracion
*   la funcion que se le pasa como parametro.
*       El hilo solo ejecutara dicha funcion si llamamos a la funcion HGS_ImagenDarPermisoHiloDibujo().
*
*   @param accionDibujo: Funcion que se ejecuta en cada iteracion del bucle.
*   @param datos: Estructura que se utilizara como parametro de la funcion accionDibujo.
*/
void HGS_ImagenCreaHiloDibujo(int (*accionDibujo)(void * datos),void * datos);

/**
*   Permite al hilo que ejecute una iteraccion. Si no se llama a esta funcion el hilo quedara
*   bloqueado hasta que se ejecute esta funcion.
*/
void HGS_ImagenDarPermisoHiloDibujo();

/**
*   Funcion para indicar al hilo que debe terminar su ejecucion. Aunque se indique que debe terminar,
*   quiza no termine al acabar esta funcion. Por eso se debe ejecutar seguidamente a la siguiente funcion.
*/
void HGS_ImagenTerminaHilo();

/**
*   Funcion que espera a que el hilo termine. Una vez terminado, libera la memoria que se reservo con
*   la creacion del mismo.
*/
void HGS_ImagenEsperarHiloDibujo();


#endif // HGS_IMAGEN_H_INCLUDED
