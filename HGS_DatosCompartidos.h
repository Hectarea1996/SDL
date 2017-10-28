#ifndef HGS_DATOSCOMPARTIDOS_H_INCLUDED
#define HGS_DATOSCOMPARTIDOS_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>

#define HGS_BloquearMutex(M,F); \
    if (SDL_LockMutex(M)<0){ \
        printf(#F"|SDL_LockMutex: %s: ",SDL_GetError()); \
        exit(EXIT_FAILURE); \
    }

#define HGS_DesbloquearMutex(M,F); \
    if (SDL_UnlockMutex(M)<0){ \
        printf("F|SDL_UnlockMutex: %s: ",SDL_GetError()); \
        exit(EXIT_FAILURE); \
    }



//Estructuras de datos.

/**
*   Estructura de datos de un rectangulo.
*/
typedef struct HGS_Rectangulo{

    double x;
    double y;
    double w;
    double h;

}HGS_Rectangulo;



#endif // HGS_DATOSCOMPARTIDOS_H_INCLUDED
