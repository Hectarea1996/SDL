#include "HGS_Sprite.h"



/**
*   Estructura para indicar la animacion y la imagen de la animacion que se va a dibujar.
*/
typedef struct HGS_Animacion{

    int animacion;
    int imagen;

}HGS_Animacion;


/**
*   Estructura de datos de un sprite.
*/
typedef struct HGS_Sprite{

    double x;
    double y;
    double w;
    double h;
    double anchorX;
    double anchorY;
    double tiempoImagen;
    HGS_Animacion animacion;
    HGS_Imagen * imagen;
    void * datos;
    SDL_mutex * mutexDatos;

    struct HGS_Sprite * sig;
    struct HGS_Sprite * ant;

    double * multFrame;

}HGS_Sprite;



//Funciones externas
extern int HGS_ImagenMaxImagenes(HGS_Imagen * imagen, int animacion);
extern void HGS_ImagenDibuja(HGS_Imagen * imagen, double x, double y, double w, double h, double anchorX, double anchorY, int animacion, int numImagen);
extern void HGS_ImagenDibujaCamara(HGS_Imagen * imagen, double x, double y, double w, double h, double anchorX, double anchorY, int animacion, int numImagen);
extern int HGS_ImagenMaxAnimaciones(HGS_Imagen * imagen);


HGS_Sprite * HGS_SpriteCrea(double x, double y, double w, double h, HGS_Imagen * imagen, void * datos){

    HGS_Sprite * nuevo= malloc(sizeof(struct HGS_Sprite));
    nuevo->anchorX= 0.5;
    nuevo->anchorY= 0.5;
    nuevo->ant= NULL;
    nuevo->sig= NULL;
    nuevo->datos= datos;
    nuevo->imagen= imagen;
    nuevo->x= x;
    nuevo->y= y;
    nuevo->w= w;
    nuevo->h= h;
    nuevo->animacion.animacion= 0;
    nuevo->animacion.imagen= 0;
    nuevo->tiempoImagen= 0;
    nuevo->mutexDatos= SDL_CreateMutex();
    nuevo->multFrame= HGS_ControlCogerMultFrames();

    return nuevo;

}

void HGS_SpriteLibera(HGS_Sprite * sprite){

    SDL_free(sprite->mutexDatos);
    free(sprite);

}

HGS_Sprite * HGS_SpriteCogerSig(HGS_Sprite * sprite){

    return sprite->sig;

}

HGS_Sprite * HGS_SpriteCogerAnt(HGS_Sprite * sprite){

    return sprite->ant;

}

void HGS_SpriteAsignarSig(HGS_Sprite * sprite, HGS_Sprite * sig){

    sprite->sig= sig;

}

void HGS_SpriteAsignarAnt(HGS_Sprite * sprite, HGS_Sprite * ant){

    sprite->ant= ant;

}

void * HGS_SpriteCogerDatosDibujo(HGS_Sprite * sprite){

    return sprite->datos;

}

void HGS_SpriteCogerPosicion(HGS_Sprite * sprite, double * x, double * y){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteCogerPosicionNivel);
    if (x!=NULL)
        *x= sprite->x;
    if (y!=NULL)
        *y= sprite->y;
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteCogerPosicionNivel);

}


void HGS_SpriteCogerAnchor(HGS_Sprite * sprite, double * anchorX, double * anchorY){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteCogerAnchor);
    if (anchorX!=NULL)
        *anchorX= sprite->anchorX;
    if (anchorY!=NULL)
        *anchorY= sprite->anchorY;
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteCogerAnchor);

}

void HGS_SpriteAsignarPosicion(HGS_Sprite * sprite, double x, double y){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteAsignarPosicion);
    sprite->x= x;
    sprite->y= y;
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteAsignarPosicion);

}

void HGS_SpriteMover(HGS_Sprite * sprite, double x, double y){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteMover);
    sprite->x+= x*(*sprite->multFrame);
    sprite->y+= y*(*sprite->multFrame);
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteMover);

}

void HGS_SpriteMoverRapido(HGS_Sprite * sprite, double x, double y){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteMoverRapido);
    sprite->x+= x;
    sprite->y+= y;
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteMoverRapido);

}

void HGS_SpriteAsignarAnchor(HGS_Sprite * sprite, double anchorX, double anchorY){

    HGS_BloquearMutex(sprite->mutexDatos,SpriteAsignarAnchor);
    if (anchorX >=0 && anchorX<=1)
        sprite->anchorX= anchorX;
    if (anchorY >=0 && anchorY<=1)
        sprite->anchorY= anchorY;
    HGS_DesbloquearMutex(sprite->mutexDatos,SpriteAsignarAnchor);

}

void HGS_SpriteSiguienteImagen(HGS_Sprite * sprite, int imagSec){

    sprite->tiempoImagen+= imagSec*(*sprite->multFrame);

    if (sprite->tiempoImagen>1.0){
        HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteSiguienteImagen);
        int maxImagen= HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion);
        if (maxImagen-1>sprite->animacion.imagen)
            sprite->animacion.imagen+= 1;
        HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteSiguienteImagen);
        sprite->tiempoImagen--;
    }


}

void HGS_SpriteSiguienteImagenBucle(HGS_Sprite * sprite, int imagSec){

    sprite->tiempoImagen+= imagSec*(*sprite->multFrame);

    if (sprite->tiempoImagen>1.0){
        HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteSiguienteImagen);
        int maxImagen= HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion);
        sprite->animacion.imagen= (sprite->animacion.imagen+1)%maxImagen;
        HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteSiguienteImagen);
        sprite->tiempoImagen--;
    }


}


void HGS_SpriteEscogerAnimacion(HGS_Sprite * sprite, int animacion){
    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
    int maxAnimacion= HGS_ImagenMaxAnimaciones(sprite->imagen);
    if (animacion >= maxAnimacion)
        sprite->animacion.animacion= maxAnimacion-1;
    else if (sprite->animacion.animacion < 0)
        sprite->animacion.animacion= 0;
    else
        sprite->animacion.animacion= animacion;
    int maxImagen= HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion);
    if (sprite->animacion.imagen >= maxImagen)
        sprite->animacion.imagen= maxImagen-1;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
}


void HGS_SpriteEscogerImagen(HGS_Sprite * sprite, int imagen){
    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
    int maxImagen= HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion);
    if (imagen < 0)
        sprite->animacion.imagen= 0;
    else if (imagen >= maxImagen)
        sprite->animacion.imagen= maxImagen-1;
    else
        sprite->animacion.imagen= imagen;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
}


void HGS_SpriteEscogerAnimacionImagen(HGS_Sprite * sprite, int animacion, int imagen){
    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
    int maxAnimacion= HGS_ImagenMaxAnimaciones(sprite->imagen);
    int maxImagen= HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion);
    if (sprite->animacion.animacion < 0)
        sprite->animacion.animacion= 0;
    else if (animacion >= maxAnimacion)
        sprite->animacion.animacion= maxAnimacion-1;
    else
        sprite->animacion.animacion= animacion;
    if (imagen < 0)
        sprite->animacion.imagen= 0;
    else if (imagen >= maxImagen)
        sprite->animacion.imagen= maxImagen-1;
    else
        sprite->animacion.imagen= imagen;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteEscogerAnimacion);
}

int HGS_SpriteCogerAnimacionActual(HGS_Sprite * sprite){

    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteCogerAnimacionActual);
    int numAnimacion= sprite->animacion.animacion;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteCogerAnimacionActual);

    return numAnimacion;

}

int HGS_SpriteCogerImagenActual(HGS_Sprite * sprite){

    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteCogerImagenActual);
    int numImagen= sprite->animacion.imagen;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteCogerImagenActual);

    return numImagen;

}

int HGS_SpriteUltimaImagen(HGS_Sprite * sprite){

    HGS_BloquearMutex(sprite->mutexDatos,HGS_SpriteUltimaImagen);
    int ultImagen= (sprite->animacion.imagen==HGS_ImagenMaxImagenes(sprite->imagen,sprite->animacion.animacion)-1);
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_SpriteUltimaImagen);

    return ultImagen;

}

void HGS_SpriteDibuja(HGS_Sprite * sprite){

    HGS_BloquearMutex(sprite->mutexDatos,HGS_EscenaDibujaSprite);
    double x= sprite->x;
    double y= sprite->y;
    double w= sprite->w;
    double h= sprite->h;
    double anchorX= sprite->anchorX;
    double anchorY= sprite->anchorY;
    HGS_Imagen * imagen= sprite->imagen;
    int animacion= sprite->animacion.animacion;
    int numImagen= sprite->animacion.imagen;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_EscenaDibujaSprite);

    HGS_ImagenDibuja(imagen,x,y,w,h,anchorX,anchorY,animacion,numImagen);

}

void HGS_SpriteDibujaCamara(HGS_Sprite * sprite){

    HGS_BloquearMutex(sprite->mutexDatos,HGS_EscenaDibujaSprite);
    double x= sprite->x;
    double y= sprite->y;
    double w= sprite->w;
    double h= sprite->h;
    double anchorX= sprite->anchorX;
    double anchorY= sprite->anchorY;
    HGS_Imagen * imagen= sprite->imagen;
    int animacion= sprite->animacion.animacion;
    int numImagen= sprite->animacion.imagen;
    HGS_DesbloquearMutex(sprite->mutexDatos,HGS_EscenaDibujaSprite);

    HGS_ImagenDibujaCamara(imagen,x,y,w,h,anchorX,anchorY,animacion,numImagen);

}



//------------------------------------
//------------------------------------
//------------------------------------


/**
*   Estructura de datos de una lista de sprites.
*/
typedef struct HGS_ListaSprites{

        HGS_Sprite * listaSprites;
        HGS_Sprite * ultimoSprites;
        HGS_Sprite * listaPendientes;
        HGS_Sprite * ultimoPendientes;
        HGS_Sprite * listaColocadora;
        HGS_Sprite * ultimoColocadora;
        SDL_mutex * mutexListas;

        double (*orden)(HGS_Sprite * sprite, void * datosDibujado);

}HGS_ListaSprites;


static double HGS_SpriteOrdenNinguno(HGS_Sprite * sprite, void * datos){

    return 0;

}

static double HGS_SpriteOrdenY(HGS_Sprite * sprite, void * datos){

    double y;
    HGS_SpriteCogerPosicion(sprite,NULL,&y);

    return y;

}

HGS_ListaSprites * HGS_ListaSpritesCrea(){

    HGS_ListaSprites * listaSprites= malloc(sizeof(struct HGS_ListaSprites));

    listaSprites->listaColocadora= NULL;
    listaSprites->listaPendientes= NULL;
    listaSprites->listaSprites= NULL;
    listaSprites->ultimoColocadora= NULL;
    listaSprites->ultimoPendientes= NULL;
    listaSprites->ultimoSprites= NULL;
    listaSprites->mutexListas= SDL_CreateMutex();
    listaSprites->orden= HGS_SpriteOrdenNinguno;

    return listaSprites;

}

void HGS_ListaSpritesLibera(HGS_ListaSprites * lista){

    SDL_free(lista->mutexListas);
    free(lista);

}


void HGS_ListaSpritesInserta(HGS_ListaSprites * listaSprites, HGS_Sprite * sprite){

    //Bloquemos los punteros de las listas de sprites.
    HGS_BloquearMutex(listaSprites->mutexListas,HGS_EscenaInsertaSprite);

    //Mantenemos los mutex del sprite y los punteros de las listas
    //para dar prioridad a esta parte antes que a la de dibujo.
    if (listaSprites->listaSprites!=NULL){

        HGS_Sprite * it = listaSprites->listaSprites;
        double valor1= listaSprites->orden(sprite,HGS_SpriteCogerDatosDibujo(sprite));
        int colocado=0;
        while (it!=NULL && !colocado){

            double valor2= listaSprites->orden(it,HGS_SpriteCogerDatosDibujo(it));

            if (valor1 <= valor2){
                HGS_Sprite * izq= HGS_SpriteCogerAnt(it);
                if (izq!=NULL){
                    sprite->sig= it;
                    sprite->ant= izq;
                    it->ant= sprite;
                    izq->sig= sprite;
                }
                else{
                    sprite->ant=NULL;
                    sprite->sig=it;
                    it->ant=sprite;
                    listaSprites->listaSprites= sprite;
                }
                colocado=1;
            }
            HGS_Sprite * itSig= it->sig;
            it= itSig;
        }
        if (!colocado){
            sprite->ant= listaSprites->ultimoSprites;
            sprite->sig= NULL;
            listaSprites->ultimoSprites->sig= sprite;
            listaSprites->ultimoSprites= sprite;
        }
    }
    else{
        listaSprites->listaSprites= sprite;
        listaSprites->ultimoSprites= sprite;
        sprite->ant=NULL;
        sprite->sig=NULL;
    }
    HGS_DesbloquearMutex(listaSprites->mutexListas,HGS_EscenaInsertaSprite);

}


void HGS_ListaSpritesExtrae(HGS_ListaSprites * listaSprites, HGS_Sprite * sprite){

    //Bloqueamos los punterros de las listas
    HGS_BloquearMutex(listaSprites->mutexListas,HGS_EscenaExtraerSprite);

    //Lo sacamos
    HGS_Sprite * izq= sprite->ant;
    HGS_Sprite * der= sprite->sig;
    if (izq!=NULL){
        izq->sig=der;
    }
    else{
        if (listaSprites->listaSprites==sprite){
            listaSprites->listaSprites= der;
        }
        else if (listaSprites->listaPendientes==sprite){
            listaSprites->listaPendientes= der;
        }
        else if (listaSprites->listaColocadora==sprite){
            listaSprites->listaColocadora= der;
        }
    }
    if (der!=NULL){
        der->ant=izq;
    }
    else{
        if (listaSprites->ultimoSprites==sprite){
            listaSprites->ultimoSprites= izq;
        }
        else if (listaSprites->ultimoPendientes==sprite){
            listaSprites->ultimoPendientes= izq;
        }
        else if (listaSprites->listaColocadora==sprite){
            listaSprites->ultimoColocadora= izq;
        }
    }
    sprite->ant=NULL;
    sprite->sig=NULL;

    //Desbloquemos los punteros de las listas de los sprites
    HGS_DesbloquearMutex(listaSprites->mutexListas,HGS_EscenaExtraerSprite);

}


void HGS_ListaSpritesOrden(HGS_ListaSprites * listaSprites, int modo, double (*orden)(HGS_Sprite * sprite, void * datos)){

    switch (modo){
        case HGS_ORDEN_PERSONALIZADO:
            listaSprites->orden= orden;
            break;
        case HGS_ORDEN_NINGUNO:
            listaSprites->orden= HGS_SpriteOrdenNinguno;
            break;
        case HGS_ORDEN_Y:
            listaSprites->orden= HGS_SpriteOrdenY;
            break;
    }

}


static void HGS_SpritePendiente(HGS_ListaSprites * listaSprites, HGS_Sprite * sprite){

    if (listaSprites->listaPendientes!=NULL){
        HGS_Sprite * it= listaSprites->listaPendientes;
        int colocado=0;
        double valor1= listaSprites->orden(sprite,sprite->datos);
        while (it!=NULL && !colocado){
            double valor2= listaSprites->orden(it,it->datos);
            if (valor1 <= valor2){
                HGS_Sprite * izq= it->ant;
                sprite->ant= izq;
                sprite->sig= it;
                it->ant= sprite;
                if (izq!=NULL){
                    izq->sig= sprite;
                }
                else{
                    listaSprites->listaPendientes= sprite;
                }
                colocado=1;
            }
            it= it->sig;
        }
        if (!colocado){
            listaSprites->ultimoPendientes->sig= sprite;
            sprite->ant= listaSprites->ultimoPendientes;
            listaSprites->ultimoPendientes= sprite;
        }
    }
    else{
        listaSprites->listaPendientes= sprite;
        listaSprites->ultimoPendientes= sprite;
        sprite->ant=NULL;
        sprite->sig=NULL;
    }

}


void HGS_ListaSpritesDibuja(HGS_ListaSprites * listaSprites){

    HGS_BloquearMutex(listaSprites->mutexListas,HGS_EscenaDibujaSprites);
    HGS_Sprite * it = listaSprites->listaSprites;
    HGS_Sprite * itsig;
    if (listaSprites->listaPendientes!=NULL){
        listaSprites->listaColocadora= listaSprites->listaPendientes;
        listaSprites->listaPendientes=NULL;
        listaSprites->ultimoPendientes=NULL;
    }
    while (it!=NULL){
        itsig= it->sig;
        double valorIt= listaSprites->orden(it,it->datos);
        double valorItSig=0;
        if (itsig != NULL){
            valorItSig= listaSprites->orden(itsig,itsig->datos);
        }
        while (listaSprites->listaColocadora!=NULL && listaSprites->orden(listaSprites->listaColocadora,listaSprites->listaColocadora->datos) <= valorIt){
            //Quitamos la imagen de la lista.
            HGS_Sprite * nueva= listaSprites->listaColocadora;
            listaSprites->listaColocadora=nueva->sig;

            if (listaSprites->listaColocadora!=NULL) listaSprites->listaColocadora->ant=NULL;

            //La metemos en la lista buena.
            HGS_Sprite * izq= it->ant;
            nueva->ant=izq;
            nueva->sig=it;
            it->ant=nueva;
            if (izq!=NULL){
                izq->sig=nueva;
            }
            else listaSprites->listaSprites=nueva;

            //Dibujamos la imagen.
            HGS_SpriteDibuja(nueva);
        }
        if (itsig!=NULL && valorIt > valorItSig){

            HGS_Sprite * derecha=itsig->sig;
            it->sig= derecha;
            if (derecha!=NULL)
                derecha->ant= it;
            else{
                listaSprites->ultimoSprites= it;
            }
            itsig->ant=NULL;
            itsig->sig=NULL;
            HGS_SpriteDibuja(itsig);
            HGS_SpritePendiente(listaSprites, itsig);

        }
        else {
            HGS_SpriteDibuja(it);
            it= it->sig;
        }
    }

    HGS_DesbloquearMutex(listaSprites->mutexListas,HGS_EscenaDibujaSprites);

}


void HGS_ListaSpritesDibujaCamara(HGS_ListaSprites * listaSprites){

    HGS_BloquearMutex(listaSprites->mutexListas,HGS_EscenaDibujaSprites);
    HGS_Sprite * it = listaSprites->listaSprites;
    HGS_Sprite * itsig;
    if (listaSprites->listaPendientes!=NULL){
        listaSprites->listaColocadora= listaSprites->listaPendientes;
        listaSprites->listaPendientes=NULL;
        listaSprites->ultimoPendientes=NULL;
    }
    while (it!=NULL){
        itsig= it->sig;
        double valorIt= listaSprites->orden(it,it->datos);
        double valorItSig=0;
        if (itsig != NULL){
            valorItSig= listaSprites->orden(itsig,itsig->datos);
        }
        while (listaSprites->listaColocadora!=NULL && listaSprites->orden(listaSprites->listaColocadora,listaSprites->listaColocadora->datos) <= valorIt){
            //Quitamos la imagen de la lista.
            HGS_Sprite * nueva= listaSprites->listaColocadora;
            listaSprites->listaColocadora=nueva->sig;

            if (listaSprites->listaColocadora!=NULL) listaSprites->listaColocadora->ant=NULL;

            //La metemos en la lista buena.
            HGS_Sprite * izq= it->ant;
            nueva->ant=izq;
            nueva->sig=it;
            it->ant=nueva;
            if (izq!=NULL){
                izq->sig=nueva;
            }
            else listaSprites->listaSprites=nueva;

            //Dibujamos la imagen.
            HGS_SpriteDibujaCamara(nueva);
        }
        if (itsig!=NULL && valorIt > valorItSig){

            HGS_Sprite * derecha=itsig->sig;
            it->sig= derecha;
            if (derecha!=NULL)
                derecha->ant= it;
            else{
                listaSprites->ultimoSprites= it;
            }
            itsig->ant=NULL;
            itsig->sig=NULL;
            HGS_SpriteDibujaCamara(itsig);
            HGS_SpritePendiente(listaSprites, itsig);

        }
        else {
            HGS_SpriteDibujaCamara(it);
            it= it->sig;
        }
    }

    HGS_DesbloquearMutex(listaSprites->mutexListas,HGS_EscenaDibujaSprites);

}


