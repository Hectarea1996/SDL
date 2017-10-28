#ifndef HGS_SPRITE_H_INCLUDED
#define HGS_SPRITE_H_INCLUDED


/**
*   Estructura de datos de un sprite.
*/
typedef struct HGS_Sprite HGS_Sprite;

/**
*   Estructura de datos de una lista de sprites.
*/
typedef struct HGS_ListaSprites HGS_ListaSprites;


#include "HGS_DatosCompartidos.h"
#include "HGS_Imagen.h"
#include "stdlib.h"
#include "stdio.h"
#include "HGS_Control.h"


/**
*   Reserva memoria para un sprite.
*
*   @param x: Coordenada x del sprite.
*   @param y: Coordenada y del sprite.
*   @param imagen: Imagen del sprite que se utilizara para dibujar el sprite.
*   @param datos: Puntero a una estructura de datos que se utilizara para realizar
*                 un orden de dibujado personalizado. Ver HGS_ListaSpritesOrden().
*
*   @return Devuelve el sprite creado.
*/
HGS_Sprite * HGS_SpriteCrea(double x, double y, double w, double h, HGS_Imagen * imagen, void * datos);

/**
*   Libera la memoria de un sprite.
*
*   @param sprite: El sprite cuya memoria se liberara.
*/
void HGS_SpriteLibera(HGS_Sprite * sprite);

/**
*   Asigna las coordenadas de un sprite.
*
*   @param sprite: El sprite cuya posicion se va a actualizar.
*   @param x: Coordenada x del sprite.
*   @param y: Coordenada y del sprite.
*/
void HGS_SpriteAsignarPosicion(HGS_Sprite * sprite, double x, double y);

/**
*   Mueve de posicion el sprite tantas unidades de medida(pixeles) por segundo.
*   AVISO: Debe llamarse a la funcion HGS_ControlFrames(). Ver HGS_Control.h.
*
*   @param sprite: El sprite a mover.
*   @param x: Variacion en unidades de medida(pixeles) por segundo de la coordenada x.
*   @param y: Variacion en unidades de medida(pixeles) por segundo de la coordenada y.
*/
void HGS_SpriteMover(HGS_Sprite * sprite, double x, double y);

/**
*   Mueve de posicion el sprite tantas unidades de medida(pixeles).
*
*   @param sprite: El sprite a mover.
*   @param x: Variacion en unidades de medida(pixeles) de la coordenada x.
*   @param y: Variacion en unidades de medida(pixeles) de la coordenada y.
*/
void HGS_SpriteMoverRapido(HGS_Sprite * sprite, double x, double y);

/**
*   Asigna los valores anchor del sprite.
*   INFO: El valor anchor relaciona la posicion del sprite con las imagenes.
*            Puede contener valores entre 0 y 1.
*            - Si el anchor vale (0,0) la posicion del sprite coincidira con el
*               punto superior izquierda de la imagen.
*            - Si el anchor vale (0.5,0.5) la posicion del sprite coincidira con
*               centro de la imagen.
*            - Si el anchor vale (1,1) la posicion del sprite coincidira con el
*               punto inferior derecha de la imagen.
*
*   @param sprite: Sprite al que se le asignara los valores anchor.
*   @param anchorX: Valor anchor correspondiente a las coordenadas horizontales.
*   @param anchorY: Valor anchor correspondiente a las coordenadas verticales.
*/
void HGS_SpriteAsignarAnchor(HGS_Sprite * sprite, double anchorX, double anchorY);

/**
*   Rellena los parametros x e y con informacion sobre la posicion del sprite. Es seguro pasar NULL
*   a los parametros x e y.
*
*   @param sprite: Sprite del cual se sustraera la informacion.
*   @param x: Parametro que se rellenara con el valor de la coordenada x del sprite.
*   @param y: Parametro que se rellenara con el valor de la coordenada y del sprite.
*/
void HGS_SpriteCogerPosicion(HGS_Sprite * sprite, double * x, double * y);

/**
*   Devuelve los datos de dibujado del sprite.
*
*   @param sprite: Sprite del cual se cogeran los datos de dibujado.
*
*   @return Devuelve un puntero a los datos de dibujado del sprite.
*/
void * HGS_SpriteCogerDatosDibujo(HGS_Sprite * sprite);

/**
*   Funcion para pasar a la siguiente imagen del sprite a una velocidad del parametro
*      imagSec(imagenes por segundo). Una vez se llega a la ultima imagen la funcion no
*      hace nada.
*   AVISO: Esta funcion hace uso del tiempo, por lo que debe usarse el mismo numero de veces
*             que la funcion HGS_ControlFrames(). Ver HGS_Control.h.
*
*   @param sprite: Sprite del cual se cambiara la imagen.
*   @param imagSec: Especifica la velocidad en imagenes por segundo con la que se
*                      cambiaran las imagenes del sprite.
*/
void HGS_SpriteSiguienteImagen(HGS_Sprite * sprite, int imagSec);

/**
*   Funcion para pasar a la siguiente imagen del sprite a una velocidad del parametro
*      imagSec(imagenes por segundo). Despues de la ultima imagen se vuelve a pasar a la
*      primera.
*   AVISO: Esta funcion hace uso del tiempo, por lo que debe usarse el mismo numero de veces
*             que la funcion HGS_ControlFrames(). Ver HGS_Control.h.
*
*   @param sprite: Sprite del cual se cambiara la imagen.
*   @param imagSec: Especifica la velocidad en imagenes por segundo con la que se
*                      cambiaran las imagenes del sprite.
*/
void HGS_SpriteSiguienteImagenBucle(HGS_Sprite * sprite, int imagSec);

/**
*   Permite escoger la animacion del sprite manteniendo el numero de la imagen de la animacion anterior.
*      Si la nueva animacion posee un numero maximo de imagenes menor al numero de imagen actual, se
*      cambiara dicho numero a la ultima imagen de la animacion.
*
*   @param sprite: Sprite al que se le cambiara la animacion.
*   @param animacion: Numero de la animacion que se asignra.
*/
void HGS_SpriteEscogerAnimacion(HGS_Sprite * sprite, int animacion);

/**
*   Permite escoger la imagen de la animacion actual del sprite.
*      Se rectificara dicho numero a la ultima imagen o a la primera si el valor pasado como parametro
*   es mayor que el numero maximo de imagenes en la animacion actual o menor que 0 respectivamente.
*
*   @param sprite: Sprite al que se cambiara la imagen de la animacion.
*   @param imagen: Numero de la imagen al que se quiere cambiar.
*/
void HGS_SpriteEscogerImagen(HGS_Sprite * sprite, int imagen);

/**
*   Permite escoger la animacion y la imagen de dicha animacion de un sprite usando las mismas
*      rectificaciones que en las funciones anteriores si es necesario.
*
*   @param sprite: Sprite al que se le cambiara la animacion y la imagen.
*   @param animaion: Numero de la animacion que se asignra.
*   @param imagen: Numero de la imagen al que se quiere cambiar.
*/
void HGS_SpriteEscogerAnimacionImagen(HGS_Sprite * sprite, int animacion, int imagen);

/**
*   Funcion que devuelve el numero de la animacion que se esta dibujando.
*
*   @param sprite: Sprite del cual se cogera el valor a devolver.
*
*   @return El numero de la animacion que se esta dibujando.
*/
int HGS_SpriteCogerAnimacionActual(HGS_Sprite * sprite);

/**
*   Funcion que devuelve el numero de la imagen que se esta dibujando.
*
*   @param sprite: Sprite del cual se cogera el valor a devolver.
*
*   @return El numero de la imagen que se esta dibujando.
*/
int HGS_SpriteCogerImagenActual(HGS_Sprite * sprite);

/**
*   Funcion para averiguar si se esta dibujando la ultima imagen de una animacion.
*
*   @param sprite: Sprite del cual se extraera la informacion.
*
*   @return Devuelve 1 si la imagen es la ultima de la animacion y 0 en caso contrario.
*/
int HGS_SpriteUltimaImagen(HGS_Sprite * sprite);

/**
*   Dibuja un sprite directamente sobre la pantalla. Es decir, si el sprite se encuentra
*   en la posicion (x,y), el sprite se dibujara a partir de los pixeles (x,y) de la pantalla.
*
*   @param sprite: El sprite a dibujar.
*/
void HGS_SpriteDibuja(HGS_Sprite * sprite);

/**
*   Dibuja un sprite en pantalla ajustando su posicion mediante la camara de la pantalla.
*   Si la posicion del sprite es (x,y) y la camara se situa en (j,k), el sprite se dibujara
*   en pantalla a partir de la posicion (x-j,y-k).
*
*   @param sprite: El sprite a dibujar.
*/
void HGS_SpriteDibujaCamara(HGS_Sprite * sprite);



//---------------------------------
//---------------------------------
//---------------------------------


#define HGS_ORDEN_PERSONALIZADO 0
#define HGS_ORDEN_NINGUNO       1
#define HGS_ORDEN_Y             2


/**
*   Crea una lista de sprites vacia.
*
*   @return La funcion devuelve un puntero a la lista de sprites.
*/
HGS_ListaSprites * HGS_ListaSpritesCrea();

/**
*   Libera una lista de sprites.
*   AVISO: No libera los sprites que puedan estar dentro de la lista.
*
*   @param lista: Lista que se va a liberar.
*/
void HGS_ListaSpritesLibera(HGS_ListaSprites * lista);

/**
*   Funcion para elegir el orden de los sprites en la lista. El orden se establece con un valor
*   que retorna una funcion para cada sprite. Seguidamente ordenamos dichos valores de menor a mayor.
*   Por defecto no hay orden en la lista: El que entra se situara al comienzo de la lista.
*
*   @param listaSprites: La listaSprites a la que se cambiara el orden de sus sprites.
*   @param modo: Se refiere al tipo de orden de la lista. Si se usa el orden HGS_ORDEN_PERSONALIZADO
*                debemos pasar un puntero a una funcion, que es la funcion que se ejecutara para
*                obtener el valor usado para ordenar cada sprite.
*   @param orden: Es el puntero a funcion. Recibe como parametros el sprite que se va a ordenar y
*                un puntero a una estructura de datos que se paso al sprite en su creacion.
*/
void HGS_ListaSpritesOrden(HGS_ListaSprites * listaSprites, int modo, double (*orden)(HGS_Sprite * sprite, void * datos));

/**
*   Inserta un sprite a la lista de forma ordenada.
*   Esta funcion NO reserva memoria.
*
*   @param listaSprites: Lista de sprites en la que se insertara el sprite.
*   @param sprite: Sprite que se insertara en la lista.
*/
void HGS_ListaSpritesInserta(HGS_ListaSprites * listaSprites, HGS_Sprite * sprite);

/**
*   Extrae un sprite de la lista de sprites.
*
*   @param listaSprites: Lista de sprites de la que se extraera el sprite.
*   @param sprite: Sprite que se extraera de la lista.
*/
void HGS_ListaSpritesExtrae(HGS_ListaSprites * listaSprites, HGS_Sprite * sprite);

/**
*   Dibuja la lista de sprites directamente sobre la pantalla.
*   Ademas se reordena la lista.
*
*   @param listaSprites: Lista de sprites que se va a dibujar y ordenar.
*/
void HGS_ListaSpritesDibuja(HGS_ListaSprites * listaSprites);

/**
*   Dibuja la lista de sprites mediante el ajuste de la camara.
*   Ademas se reordena la lista.
*
*   @param listaSprites: Lista de sprites que se va a dibujar y ordenar.
*/
void HGS_ListaSpritesDibujaCamara(HGS_ListaSprites * listaSprites);


#endif // HGS_SPRITE_H_INCLUDED
