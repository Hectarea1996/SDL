
#include "HGS_Wrapper.h"


void HGS_WrapperInicializar(){

    //Inicializamos el modo de video.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("Error: %s",SDL_GetError());

    //Inicializamos el modo de audio.

    //Inicializamos el modo de red.

}


void HGS_WrapperLiberar(){

    SDL_Quit();

}
