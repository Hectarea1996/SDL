
#ifndef HGS_REJILLACOLISION_H_INCLUDED
#define HGS_REJILLACOLISION_H_INCLUDED

/**
*   Estructura de datos de una rejilla.
*   La rejilla sirve para detectar colisiones. La rejilla no es mas que una tabla donde se almacenan las FormasColision.
*/
typedef struct HGS_Rejilla HGS_Rejilla;

#include "HGS_Sprite.h"
#include "HGS_DatosCompartidos.h"
#include "HGS_ListaElementos.h"
#include "HGS_Tareas.h"
#include <stdlib.h>
#include <stdio.h>


/**
*   Crea una estructuras de datos de una rejilla.
*
*   @param x: Coordenada x del punto superior izquierda de la rejilla.
*   @param y: Coordenada y del punto superior izquierda de la rejilla.
*   @param ancho: Es el ancho de la rejilla.
*   @param alto: Es la altura de la rejilla.
*   @param wCelda: Es el ancho de cada celda de la tabla.
*   @param hCelda: Es la altura de cada celda de la tabla.
*
*   INFO: Se recomienda poner una altura y anchura similar a la mayoria de las FormasColision.
*   AVISO: Si las dimensiones de la rejilla no son proporcionales a las dimensiones de cada celda
*          se hara una rectificacion a las dimensiones de la celda disminuyendolas hasta ser
*          proporcionales a las dimensiones de las celdas.
*
*   @return Se devuelve un puntero a la estructura de la rejilla.
*/
HGS_Rejilla * HGS_RejillaCrea(double x, double y, double ancho, double alto, double wCelda, double hCelda);

/**
*   Libera la memoria reservada de una rejilla.
*
*   @param rejilla: Rejilla que se va a liberar.
*/
void HGS_RejillaLibera(HGS_Rejilla * rejilla);

/**
*   Crea una forma de colision a partir de una rejilla. Esta formaColision solo debe insertarse
*   en esta rejilla y no en otra.
*
*   @param rejilla: Rejilla de la cual se creara la formaColision.
*   @param sprite: La formaColision cogera la posicion de este sprite para cambiar su posicion.
*   @param datos: Puntero a una estructura de datos que se pasara a la funcion pasada como parametro en
*                 HGS_RejillaFormaColisionActua().
*   @param grupo: Entero que permite distinguir cada formaColision.
*   @param HGS_FORMA: Forma que tendra la formaColision. Puede variar entre HGS_FORMA_RECTANGULO,
*                     HGS_FORMA_CIRCULO, HGS_FORMA_PUNTO.
*   @param relX: Para cada forma tenemos un significado:
*                   - HGS_FORMA_RECTANGULO: Coordenada x del punto superior izquierdo.
*                   - HGS_FORMA_CIRCULO: Coordenada x del centro.
*                   - HGS_FORMA_PUNTO: Coordenada x del punto.
*   @param relY: Para cada forma tenemos un significado:
*                   - HGS_FORMA_RECTANGULO: Coordenada y del punto superior izquierdo.
*                   - HGS_FORMA_CIRCULO: Coordenada y del centro.
*                   - HGS_FORMA_PUNTO: Coordenada y del punto.
*   @param w: Para cada forma tenemos un significado:
*                   - HGS_FORMA_RECTANGULO: Anchura del rectangulo.
*                   - HGS_FORMA_CIRCULO: Diametro del circulo.
*                   - HGS_FORMA_PUNTO: Se ignora.
*   @param h: Para cada forma tenemos un significado:
*                   - HGS_FORMA_RECTANGULO: Altura del rectangulo.
*                   - HGS_FORMA_CIRCULO: Se ignora.
*                   - HGS_FORMA_PUNTO: Se ignora.
*
*   @return Devuelve un puntero a la estructura de la FormaColision.
*/
HGS_FormaColision * HGS_RejillaCreaFormaColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, int HGS_FORMA, double relX, double relY, double w, double h);

/**
*   Crea una rectangulo de colision a partir de una rejilla. Esta formaColision solo debe insertarse
*   en esta rejilla y no en otra.
*
*   @param rejilla: Rejilla de la cual se creara la formaColision.
*   @param sprite: La formaColision cogera la posicion de este sprite para cambiar su posicion.
*   @param datos: Puntero a una estructura de datos que se pasara a la funcion pasada como parametro en
*                 HGS_RejillaFormaColisionActua().
*   @param grupo: Entero que permite distinguir cada formaColision.
*   @param relX: Coordenada x del punto superior izquierda del rectangulo que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*   @param relY: Coordenada y del punto superior izquierda del rectangulo que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*   @param w: Anchura del rectangulo.
*   @param h: Altura del rectangulo.
*
*   @return Devuelve un puntero a la estructura de la FormaColision.
*/
HGS_FormaColision * HGS_RejillaCreaRectanguloColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY, double w, double h);

/**
*   Crea un circulo de colision a partir de una rejilla. Esta formaColision solo debe insertarse
*   en esta rejilla y no en otra.
*
*   @param rejilla: Rejilla de la cual se creara la formaColision.
*   @param sprite: La formaColision cogera la posicion de este sprite para cambiar su posicion.
*   @param datos: Puntero a una estructura de datos que se pasara a la funcion pasada como parametro en
*                 HGS_RejillaFormaColisionActua().
*   @param grupo: Entero que permite distinguir cada formaColision.
*   @param relX: Coordenada x del centro del circulo que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*   @param relY: Coordenada y del centro del circulo que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*   @param r: Radio del circulo.
*
*   @return Devuelve un puntero a la estructura de la FormaColision.
*/
HGS_FormaColision * HGS_RejillaCreaCirculoColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY, double r);

/**
*   Crea un punto de colision a partir de una rejilla. Esta formaColision solo debe insertarse
*   en esta rejilla y no en otra.
*
*   @param rejilla: Rejilla de la cual se creara la formaColision.
*   @param sprite: La formaColision cogera la posicion de este sprite para cambiar su posicion.
*   @param datos: Puntero a una estructura de datos que se pasara a la funcion pasada como parametro en
*                 HGS_RejillaFormaColisionActua().
*   @param grupo: Entero que permite distinguir cada formaColision.
*   @param relX: Coordenada x del punto que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*   @param relY: Coordenada y del punto que se sumara a la
*                posicion del sprite. Si el sprite es NULL, esta posicion se tomara como la propia
*                de la formaColision.
*
*   @return Devuelve un puntero a la estructura de la FormaColision.
*/
HGS_FormaColision * HGS_RejillaCreaPuntoColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY);

/**
*   Inserta una formaColision en la rejilla, de forma que comenzara a ser posible su deteccion mediante colisiones.
*
*   @param rejilla: Rejilla en la que se insertara la formaColision.
*   @param forma: FormaColision que se va a insertar en la rejilla.
*/
void HGS_RejillaFormaColisionInsertar(HGS_Rejilla * rejilla, HGS_FormaColision * forma);

/**
*   Extrae una formaColision de una rejilla, haciendo imposible su deteccion mediante colisiones.
*
*   @param rejilla: Rejilla de la cual se va a extraer la formaColision.
*   @param forma: FormaColision que se va a extraer.
*/
void HGS_RejillaFormaColisionExtraer(HGS_Rejilla * rejilla, HGS_FormaColision * forma);

/**
*   Actualiza en la rejilla la posicion de una formaColision.
*
*   @param rejilla: Rejilla donde se encuentra la formaColision.
*   @param forma: FormaColision cuya posicion en la rejilla se va a actualizar.
*/
void HGS_RejillaFormaColisionActualizar(HGS_Rejilla * rejilla, HGS_FormaColision * forma);

/**
*   Ejecuta una funcion por cada formaColision que intersecte con la que se pasa como parametro.
*
*   @param forma: Se buscaran todas las formasColision que intersecten con esta.
*   @param accion: Funcion que se ejecutara cuando se encuentre una formaColision que intersecta
*                  con la formaColision forma.
*                  Los parametros de la funcion se corresponden con:
*                     - grupoSrc: Grupo de la formaColision forma.
*                     - datosSrc: Puntero a la estructura de datos de la formaColision forma que
*                                 se proporciono en su creacion.
*                     - grupoDst: Grupo de la formaColision que se ha encontrado.
*                     - datosDst: Puntero a la estructura de datos de la formaColision que se ha
*                                 encontrado que se proporciono en su creacion.
*                  La funcion debe retornar 0 si queremos seguir con la busqueda. Si es distinto de
*                  0, se dejara de buscar y la funcion principal terminara.
*/
void HGS_RejillaFormaColisionActua(HGS_FormaColision * forma, int (*accion)(int grupoSrc, void * datosSrc, int grupoDst,void * datosDst));


#endif // HGS_REJILLA_H_INCLUDED
