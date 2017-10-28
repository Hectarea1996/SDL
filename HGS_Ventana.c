
#include "HGS_Ventana.h"


extern void HGS_CamaraInicializa(int w, int h);



/**
*   Estructura de datos de la ventana.
*/
typedef struct Ventana{

    SDL_Window * ventana;
    SDL_Renderer * render;

}Ventana;


/**
*   Variable que representa la ventana.
*/
Ventana ventana;



void HGS_VentanaCrea(const char * titulo, int w, int h, int fullscreen){

    if (fullscreen) ventana.ventana=SDL_CreateWindow(titulo,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,0,0,SDL_WINDOW_FULLSCREEN_DESKTOP);
    else ventana.ventana=SDL_CreateWindow(titulo,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,0);

    if (ventana.ventana==NULL){
        printf("Error en HGS_CreaVentana|SDL_CreateWindow: %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ventana.render= SDL_CreateRenderer(ventana.ventana,-1,SDL_RENDERER_ACCELERATED);

    int winW,winH;
    SDL_GetWindowSize(ventana.ventana,&winW,&winH);
    HGS_CamaraInicializa(winW,winH);

}

SDL_Renderer * HGS_VentanaCogerRenderer(){

    return ventana.render;

}

void HGS_VentanaDibujaImagenCamara(SDL_Texture * imagen, double x, double y, double w, double h){

    static SDL_Rect rect;
    double camaraX,camaraY;
    HGS_CamaraCogerPosicion(&camaraX,&camaraY);
    rect.x= x-camaraX;
    rect.y= y-camaraY;
    rect.w= w;
    rect.h= h;
    SDL_RenderCopy(ventana.render,imagen,NULL,&rect);

}


void HGS_VentanaDibujaImagen(SDL_Texture * imagen, double x, double y, double w, double h){

    static SDL_Rect rect;
    rect.x= x;
    rect.y= y;
    rect.w= w;
    rect.h= h;
    SDL_RenderCopy(ventana.render,imagen,NULL,&rect);

}


void HGS_VentanaActualiza(){

    SDL_RenderPresent(ventana.render);

}

void HGS_VentanaLibera(){

    SDL_DestroyRenderer(ventana.render);
    SDL_DestroyWindow(ventana.ventana);

}







