#include "HGS_ES.h"

typedef struct HGS_Tecla{

    //SDL_mutex * mutexTecla;
    int teclaMod;
    int eventoKeyDown;
    int eventoKeyUp;
    int estado;

}HGS_Tecla;

HGS_Tecla teclaASCII[128];


static void HGS_ESTecladoInicializar(){

    for (int i=0; i<128; i++){
        teclaASCII[i].estado= 0;
        teclaASCII[i].eventoKeyDown= 0;
        teclaASCII[i].eventoKeyUp= 0;
        teclaASCII[i].teclaMod= 0;
    }

}

static void HGS_ESTecladoCambiarTecla(int tecla, int tipoEvento, int teclaMod){

    if (tecla<0 || tecla>127) return;

    //SDL_LockMutex(teclaASCII[tecla].mutexTecla);
    switch(tipoEvento){
        case SDL_KEYDOWN:
            teclaASCII[tecla].eventoKeyDown= 1;
            teclaASCII[tecla].estado= 1;
            teclaASCII[tecla].teclaMod= teclaMod;
            break;
        case SDL_KEYUP:
            teclaASCII[tecla].eventoKeyUp= 1;
            teclaASCII[tecla].estado= 0;
            break;
    }
    //SDL_UnlockMutex(teclaASCII[tecla].mutexTecla);

}

int HGS_ESTecladoTeclaPulsada(int SDLK_KEY, int * Mod){

    if (SDLK_KEY<0 || SDLK_KEY>127) return -1;

    //SDL_LockMutex(teclaASCII[SDLK_KEY].mutexTecla);
    int keyDown= teclaASCII[SDLK_KEY].eventoKeyDown;
    teclaASCII[SDLK_KEY].eventoKeyDown= 0;
    if (Mod!=NULL)
        *Mod= teclaASCII[SDLK_KEY].teclaMod;
    //SDL_UnlockMutex(teclaASCII[SDLK_KEY].mutexTecla);
    return keyDown;

}

int HGS_ESTecladoTeclaLevantada(int SDLK_KEY){

    if (SDLK_KEY<0 || SDLK_KEY>127) return -1;

    //SDL_LockMutex(teclaASCII[SDLK_KEY].mutexTecla);
    int keyUp= teclaASCII[SDLK_KEY].eventoKeyUp;
    teclaASCII[SDLK_KEY].eventoKeyUp= 0;
    //SDL_UnlockMutex(teclaASCII[SDLK_KEY].mutexTecla);
    return keyUp;

}

int HGS_ESTecladoTeclaEstado(int SDLK_KEY, int * Mod){

    if (SDLK_KEY<0 || SDLK_KEY>127) return -1;

    //SDL_LockMutex(teclaASCII[SDLK_KEY].mutexTecla);
    int keyState= teclaASCII[SDLK_KEY].estado;
    if (Mod!=NULL)
        *Mod= teclaASCII[SDLK_KEY].teclaMod;
    //SDL_UnlockMutex(teclaASCII[SDLK_KEY].mutexTecla);

    return keyState;

}



//----------------------------------------

typedef struct HGS_PosicionRaton{

    int x;
    int y;

}HGS_PosicionRaton;

typedef struct HGS_teclaRaton{

    int estado;
    int eventoButtonDown;
    HGS_PosicionRaton PosicionDown;
    int eventoButtonUp;
    HGS_PosicionRaton PosicionUp;

}HGS_teclaRaton;


HGS_teclaRaton teclaRaton[3];
HGS_PosicionRaton posicionRaton;
int ruedaRaton;


static void HGS_ESRatonInicializar(){

    for (int i=0; i<3; i++){
        teclaRaton[i].estado= 0;
        teclaRaton[i].eventoButtonDown= 0;
        teclaRaton[i].eventoButtonUp= 0;
    }

    posicionRaton.x= 0;
    posicionRaton.y= 0;

    ruedaRaton= 0;

}

static void HGS_ESRatonCambiarTecla(int tecla, int tipoEvento, int x, int y){

    //Tecla ira de 1 a 3. Nosotros necesitamos los valores de 0 a 2.
    tecla--;

    if (tecla<0 || tecla>2) return;

    switch (tipoEvento){
        case SDL_MOUSEBUTTONDOWN:
            teclaRaton[tecla].eventoButtonDown= 1;
            teclaRaton[tecla].estado= 1;
            teclaRaton[tecla].PosicionDown.x= x;
            teclaRaton[tecla].PosicionDown.y= y;
            break;
        case SDL_MOUSEBUTTONUP:
            teclaRaton[tecla].eventoButtonUp= 1;
            teclaRaton[tecla].estado= 0;
            teclaRaton[tecla].PosicionUp.x= x;
            teclaRaton[tecla].PosicionUp.y= y;
            break;
        case SDL_MOUSEMOTION:
            posicionRaton.x= x;
            posicionRaton.y= y;
            break;
        case SDL_MOUSEWHEEL:
            ruedaRaton= y;
            break;
    }

}

int HGS_ESRatonBotonPulsado(int SDL_button, int * x, int * y){

    SDL_button--;

    if (SDL_button<0 || SDL_button>2) return -1;

    int teclaPulsada= teclaRaton[SDL_button].eventoButtonDown;
    teclaRaton[SDL_button].eventoButtonDown= 0;

    if (teclaPulsada){
        if (x!=NULL)
            *x= teclaRaton[SDL_button].PosicionDown.x;
        if (y!=NULL)
            *y= teclaRaton[SDL_button].PosicionDown.y;
    }

    return teclaPulsada;

}

int HGS_ESRatonBotonLevantado(int SDL_button, int * x, int * y){

    SDL_button--;

    if (SDL_button<0 || SDL_button>2) return -1;

    int teclaLevantada= teclaRaton[SDL_button].eventoButtonUp;
    teclaRaton[SDL_button].eventoButtonUp= 0;

    if (teclaLevantada){
        if (x!=NULL)
            *x= teclaRaton[SDL_button].PosicionUp.x;
        if (y!=NULL)
            *y= teclaRaton[SDL_button].PosicionUp.y;
    }

    return teclaLevantada;

}

int HGS_ESRatonBotonEstado(int SDL_button){

    SDL_button--;

    if (SDL_button<0 || SDL_button>2) return -1;

    return teclaRaton[SDL_button].estado;

}

int HGS_ESRatonRueda(){

    int rueda= ruedaRaton;
    ruedaRaton= 0;
    return rueda;

}


//----------------------------------------


//AQUI VAN LOS EVENTOS DE LOS JOYSTICKS. LE TOCA A DAVID :D.


//----------------------------------------

SDL_Event * evento;

void HGS_ESCapturarEventos(){

    while(SDL_PollEvent(evento)){
        switch(evento->type){
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                HGS_ESTecladoCambiarTecla(evento->key.keysym.sym,evento->type,evento->key.keysym.mod);
                break;
            case SDL_MOUSEMOTION:
                HGS_ESRatonCambiarTecla(1,evento->type,evento->motion.x,evento->motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                HGS_ESRatonCambiarTecla(evento->button.button,evento->type,evento->button.x,evento->button.y);
                break;
            case SDL_MOUSEWHEEL:
                HGS_ESRatonCambiarTecla(1,evento->type,evento->wheel.x,evento->wheel.y);
                break;
        }
    }

}

void HGS_ESInicializar(){

    //Captura de eventos.
    evento= malloc(sizeof(SDL_Event));

    //Teclado.
    HGS_ESTecladoInicializar();

    //Raton.
    HGS_ESRatonInicializar();

}

void HGS_ESLiberar(){

    SDL_free(evento);

}








