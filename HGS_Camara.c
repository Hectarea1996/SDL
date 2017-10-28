
#include "HGS_Camara.h"

typedef struct HGS_Camara{

    int limites;
    double limIzq;
    double limDer;
    double limSup;
    double limInf;
    int bloqueoX;
    int bloqueoY;
    HGS_Sprite * sprite;
    double x;
    double y;
    int w;
    int h;
    double desviox;
    double desvioy;
    SDL_mutex * mutex;

    double * multFrames;

}HGS_Camara;

HGS_Camara camara;

void HGS_CamaraInicializa(int w, int h){

    camara.bloqueoX= 0;
    camara.bloqueoY= 0;

    camara.sprite= NULL;

    camara.x= 0;
    camara.y= 0;
    camara.w= w;
    camara.h= h;
    camara.desviox= 0;
    camara.desvioy= 0;

    camara.mutex= SDL_CreateMutex();

    camara.multFrames= HGS_ControlCogerMultFrames();

}

void HGS_CamaraCogerPosicion(double * x, double * y){

    *x= 0;
    *y= 0;
    double xSprite=0;
    double ySprite=0;

    HGS_BloquearMutex(camara.mutex,HGS_CamaraCogerPosicion);
    if (camara.sprite!=NULL){
        HGS_SpriteCogerPosicion(camara.sprite,&xSprite,&ySprite);
        if (!camara.bloqueoX){
            (*x)+= xSprite;
        }
        if (!camara.bloqueoY){
            (*y)+= ySprite;
        }
    }

    (*x)+= camara.x + camara.desviox;
    (*y)+= camara.y + camara.desvioy;

    if (camara.limites){
        if ((*x)<camara.limIzq) (*x)=camara.limIzq;
        else if ((*x)>camara.limDer) (*x)=camara.limDer;
        if ((*y)<camara.limSup) (*y)=camara.limSup;
        else if ((*y)>camara.limInf) (*y)=camara.limInf;
    }
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraCogerPosicion);

}

void HGS_CamaraSeguirSprite(HGS_Sprite * sprite){

    if (sprite!=NULL){
        HGS_BloquearMutex(camara.mutex,HGS_CamaraSeguirSprite);
        //La camara apunta al sprite.
        camara.sprite= sprite;
        //Asignamos el correcto desvio.
        camara.x= -camara.w*0.5;
        camara.y= -camara.h*0.5;
        HGS_DesbloquearMutex(camara.mutex,HGS_CamaraSeguirSprite);
    }

}

void HGS_CamaraAsignarLimites(double xIzq, double xDer, double ySup, double yInf){

    camara.limites= 1;
    if (xIzq>=xDer || ySup>=yInf) return;
    camara.limIzq= xIzq;
    camara.limDer= xDer;
    camara.limSup= ySup;
    camara.limInf= yInf;

}

void HGS_CamaraQuitarLimites(){

    camara.limites= 0;

}

void HGS_CamaraDesviarCamara(double desviox, double desvioy){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraDesviarSeguimiento);
    camara.desviox= desviox;
    camara.desvioy= desvioy;
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraDesviarSeguimiento);

}

void HGS_CamaraNoSeguirSprite(){

    if (camara.sprite!=NULL){
        double spriteX, spriteY;
        HGS_BloquearMutex(camara.mutex,HGS_CamaraNoSeguirSprite);
        HGS_SpriteCogerPosicion(camara.sprite,&spriteX,&spriteY);
        camara.x+= spriteX;
        camara.y+= spriteY;
        camara.sprite= NULL;
        HGS_DesbloquearMutex(camara.mutex,HGS_CamaraNoSeguirSprite);
    }

}

void HGS_CamaraAsignarPosicion(double x, double y){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraAsignarPosicion);
    if (camara.sprite==NULL){
        if (!camara.bloqueoX)
            camara.x= x;
        if (!camara.bloqueoY)
            camara.y= y;
    }
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraAsignarPosicion);

}

void HGS_CamaraMover(double x, double y){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraMover);
    if (camara.sprite==NULL){
        if (!camara.bloqueoX)
            camara.x+= x*(*camara.multFrames);
        if (!camara.bloqueoY)
            camara.y+= y*(*camara.multFrames);
    }
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraMover);
}

void HGS_CamaraBloquearMovHorizontal(){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraBloquearMovHorizontal);
    if (camara.sprite!=NULL && !camara.bloqueoX){
        double spriteX;
        HGS_SpriteCogerPosicion(camara.sprite,&spriteX,NULL);
        camara.x+= spriteX;
    }
    camara.bloqueoX=1;
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraBloquearMovHorizontal);

}

void HGS_CamaraBloquearMovVertical(){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraBloquearMovVertical);
    if (camara.sprite!=NULL && camara.bloqueoY!=1){
        double spriteY;
        HGS_SpriteCogerPosicion(camara.sprite,NULL,&spriteY);
        camara.y+= spriteY;
    }
    camara.bloqueoY=1;
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraBloquearMovVertical);

}

void HGS_CamaraDesbloquear(){

    HGS_BloquearMutex(camara.mutex,HGS_CamaraDesbloquear);
    if (camara.sprite!=NULL && camara.bloqueoX!=0){
        camara.x= -camara.w*0.5;
    }
    camara.bloqueoX=0;
    if (camara.sprite!=NULL && camara.bloqueoY!=0){
        camara.y= -camara.h*0.5;
    }
    camara.bloqueoY=0;
    HGS_DesbloquearMutex(camara.mutex,HGS_CamaraDesbloquear);

}

/*
void HGS_VentanaTerremoto(double magnitud){
    double angulo= rand()%360;
    double x= sin(angulo);
    double y= cos(angulo);
    if (SDL_LockMutex(ventana.mutex)<0){
        printf("VentanaTerremoto|SDL_LockMutex: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ventana.camara.desviox= x*magnitud;
    ventana.camara.desvioy= y*magnitud;
    if (SDL_UnlockMutex(ventana.mutex)<0){
        printf("VentanaTerremoto|SDL_UnlockMutex: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void HGS_VentanaPararTerremoto(){
    if (SDL_LockMutex(ventana.mutex)<0){
        printf("VentanaPararTerremoto|SDL_LockMutex: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ventana.camara.desviox= 0;
    ventana.camara.desvioy= 0;
    if (SDL_UnlockMutex(ventana.mutex)<0){
        printf("VentanaPararTerremoto|SDL_UnlockMutex: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
}*/
