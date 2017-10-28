#ifndef ENTRADASALIDA_H_INCLUDED
#define ENTRADASALIDA_H_INCLUDED


#include "SDL2/SDL.h"
#include "stdio.h"
#include "stdlib.h"


//General

/**
*   Inicializa el sistema de captura de eventos.
*/
void HGS_ESInicializar();

/**
*   Libera el sistema de captura de eventos.
*/
void HGS_ESLiberar();

/**
*   Funcion para capturar los eventos producidos desde la ultima vez que se llamo
*      a esta funcion.
*/
void HGS_ESCapturarEventos();



//Teclado

/**
*   Funcion para comprobar si se ha pulsado una tecla del teclado.
*
*   @param SDLK_KEY: Clave SDL para representar una tecla del teclado.
*   @param Mod: Puntero a un entero que se rellenara con la informacion
*                  de una tecla especial si se pulso junto a la tecla SDLK_KEY.
*               Esta informacion se corresponde con claves de SDL para representar
*               estas teclas especiales.
*
*   @return Devuelve 1 si la tecla pasada como parametro se pulso y 0 en caso contrario.
*              Si esta funcion devolvio 1 para una tecla, las proximas llamadas retornaran
*           0 para dicha tecla hasta que no se vuelva a pulsar de nuevo.
*/
int HGS_ESTecladoTeclaPulsada(int SDLK_KEY, int * Mod);

/**
*   Funcion para comprobar si se ha dejado de pulsar una tecla del teclado.
*
*   @param SDLK_KEY: Clave SDL para representar una tecla del teclado.
*
*   @return Devuelve 1 si la tecla pasada como parametro se dejo de pulsar y 0 en caso contrario.
*              Si esta funcion devolvio 1 para una tecla, las proximas llamadas retornaran
*           0 para dicha tecla hasta que no se vuelva a dejar de pulsar de nuevo.
*/
int HGS_ESTecladoTeclaLevantada(int SDLK_KEY);

/**
*   Funcion para comprobar el estado de una tecla del teclado.
*
*   @param SDLK_KEY: Clave SDL para representar una tecla del teclado.
*   @param Mod: Puntero a un entero que se rellenara con la informacion
*                  de una tecla especial si se pulso junto a la tecla SDLK_KEY.
*               Esta informacion se corresponde con claves de SDL para representar
*               estas teclas especiales.
*
*   @return La funcion devuelve 1 si la tecla esta pulsada y 0 en caso contrario.
*/
int HGS_ESTecladoTeclaEstado(int SDLK_KEY, int * Mod);



//Raton

/**
*   Funcion para comprobar si se ha pulsado un boton del raton y las coordenadas
*   en el que se produjo la pulsacion. Si no se produjo la pulsacion las variables x e y
*   no se actualizaran.
*
*   @param SDL_button: Se trata del boton del que se quiere saber la informacion.
*                         Los posibles valores a introducir son:
*                           - SDL_BUTTON_LEFT: Boton izquierdo.
*                           - SDL_BUUTON_MIDDLE: Boton central.
*                           - SDL_BUTTON_RIGHT: Boton derecho.
*   @param x: Coordenada x del lugar donde se ha producido la pulsacion. Es seguro pasar NULL.
*   @param y: Coordenada y del lugar donde se ha producido la pulsacion. Es seguro pasar NULL.
*
*   @return Devuelve 1 si se ha pulsado el boton y 0 en caso contrario.
*/
int HGS_ESRatonBotonPulsado(int SDL_button, int * x, int * y);

/**
*   Funcion para comprobar si se ha levantado un boton del raton y las coordenadas
*   en el que se dejo de pulsar. Si no se dejo de pulsar el boton las variables x e y
*   no se actualizaran.
*
*   @param SDL_button: Se trata del boton del que se quiere saber la informacion.
*                         Los posibles valores a introducir son:
*                           - SDL_BUTTON_LEFT: Boton izquierdo.
*                           - SDL_BUUTON_MIDDLE: Boton central.
*                           - SDL_BUTTON_RIGHT: Boton derecho.
*   @param x: Coordenada x del lugar donde se dejo de pulsar. Es seguro pasar NULL.
*   @param y: Coordenada y del lugar donde se dejo de pulsar. Es seguro pasar NULL.
*
*   @return Devuelve 1 si se dejo de pulsar el boton y 0 en caso contrario.
*/
int HGS_ESRatonBotonLevantado(int SDL_button, int * x, int * y);

/**
*   Funcion para saber el estado de un boton del raton.
*
*   @param SDL_button: Se trata del boton del que se quiere saber la informacion.
*                         Los posibles valores a introducir son:
*                           - SDL_BUTTON_LEFT: Boton izquierdo.
*                           - SDL_BUUTON_MIDDLE: Boton central.
*                           - SDL_BUTTON_RIGHT: Boton derecho.
*
*   @return Devuelve 1 si el boton esta pulsado y 0 en caso contrario.
*/
int HGS_ESRatonBotonEstado(int SDL_button);

/**
*   Funcion que devuelve la cantidad de movimiento del la rueda del raton.
*
*   @return Deuelve un numero mayor que 0 si la rueda se ha movido hacia arriba,
*              menor que 0 si se ha movido hacia abajo y 0 si no se ha movido.
*/
int HGS_ESRatonRueda();


#endif // ENTRADASALIDA_H_INCLUDED
