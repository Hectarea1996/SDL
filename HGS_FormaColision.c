
#include "HGS_FormaColision.h"

typedef struct HGS_FormaColision{

    int grupo;
    void * datos;
    HGS_Sprite * sprite;

    SDL_mutex * mutex;
    HGS_FormaGeometrica * forma;

    int priX,priY,ultX,ultY;

    int numAncho,numAlto;
    HGS_Elemento *** elemento;

    double * multFrames;

}HGS_FormaColision;


HGS_FormaColision * HGS_FormaColisionCrea(int HGS_FORMA, HGS_Sprite * sprite, double relX, double relY, double w, double h, int numAncho, int numAlto, void * datos, int grupo){

    HGS_FormaColision * nueva= malloc(sizeof(struct HGS_FormaColision));

    nueva->multFrames= HGS_ControlCogerMultFrames();

    nueva->grupo= grupo;
    nueva->datos= datos;
    nueva->sprite= sprite;

    nueva->numAncho= numAncho;
    nueva->numAlto= numAlto;

    nueva->priX= 0;
    nueva->priY= 0;
    nueva->ultX= 0;
    nueva->ultY= 0;

    nueva->mutex= SDL_CreateMutex();

    nueva->forma= HGS_FormaGeometricaCrea(HGS_FORMA,relX,relY,w,h);

    nueva->elemento= malloc(sizeof(struct HGS_Elemento**)*numAlto);
    for (int i=0; i<numAlto; i++){
        nueva->elemento[i]= malloc(sizeof(struct HGS_Elemento*)*numAncho);
    }

    for (int i=0; i<numAlto-1; i++){
        for (int j=0; j<numAncho-1; j++){
            nueva->elemento[i][j]= HGS_ListaElementosCreaElemento(&nueva->grupo,&nueva->datos,nueva,0);
        }
    }
    for (int i=0; i<numAlto-1; i++){
        nueva->elemento[i][numAncho-1]= HGS_ListaElementosCreaElemento(&nueva->grupo,&nueva->datos,nueva,1);
    }
    for (int j=0; j<numAncho-1; j++){
        nueva->elemento[numAlto-1][j]= HGS_ListaElementosCreaElemento(&nueva->grupo,&nueva->datos,nueva,2);
    }
    nueva->elemento[numAlto-1][numAncho-1]= HGS_ListaElementosCreaElemento(&nueva->grupo,&nueva->datos,nueva,3);

    return nueva;

}

void HGS_FormaColisionMover(HGS_FormaColision * forma, double relX, double relY){

    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionMover);
    HGS_FormaGeometricaMover(forma->forma,relX*(*forma->multFrames),relY*(*forma->multFrames));
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionMover);

}

void HGS_FormaColisionMoverRapido(HGS_FormaColision * forma, double relX, double relY){

    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionMoverRapido);
    HGS_FormaGeometricaMover(forma->forma,relX,relY);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionMoverRapido);

}

void HGS_FormaColisionAsignarPosicion(HGS_FormaColision * forma, double relX, double relY){

    double spX= 0;
    double spY= 0;
    if (forma->sprite!=NULL)
        HGS_SpriteCogerPosicion(forma->sprite,&spX,&spY);
    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionMueve);
    HGS_FormaGeometricaAsignarPosicion(forma->forma,spX+relX,spY+relY);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionMueve);

}


HGS_Elemento *** HGS_FormaColisionCogerElementos(HGS_FormaColision * formaColision){

    return formaColision->elemento;

}

void HGS_FormaColisionCogerNumCeldas(HGS_FormaColision * forma, int * numAncho, int * numAlto){

    *numAncho= forma->numAncho;
    *numAlto= forma->numAlto;

}

int HGS_FormaColisionInterseccion(HGS_FormaColision * forma1, HGS_FormaColision * forma2){

    HGS_BloquearMutex(forma1->mutex,HGS_FormaColisionMueve);
    HGS_BloquearMutex(forma2->mutex,HGS_FormaColisionMueve);

    int interseccion= HGS_FormaGeometricaInterseccion(forma1->forma,forma2->forma);

    HGS_DesbloquearMutex(forma2->mutex,HGS_FormaColisionMueve);
    HGS_DesbloquearMutex(forma1->mutex,HGS_FormaColisionMueve);

    return interseccion;

}

int HGS_FormaColisionCogerTipo(HGS_FormaColision * forma){

    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionCogerTipo);
    int tipo= HGS_FormaGeometricaCogerTipo(forma->forma);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionCogerTipo);

    return tipo;

}

void HGS_FormaColisionCogerPosicion(HGS_FormaColision * forma, double * x, double * y){

    double spX= 0;
    double spY= 0;
    double fcX= 0;
    double fcY= 0;
    if (forma->sprite!=NULL)
        HGS_SpriteCogerPosicion(forma->sprite,&spX,&spY);
    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionCogerPosicion);
    HGS_FormaGeometricaCogerPosicion(forma->forma,&fcX,&fcY);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionCogerPosicion);

    *x= spX+fcX;
    *y= spY+fcY;

}

int HGS_FormaColisionCoger(HGS_FormaColision * forma, double * x, double * y, double * wr, double * h){

    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionCoger);
    int tipo= HGS_FormaGeometricaCoger(forma->forma,x,y,wr,h);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionCoger);

    return tipo;

}

void HGS_FormaColisionCogerRectContenedor(HGS_FormaColision * forma, double * x, double * y, double * w, double * h){

    double spX= 0;
    double spY= 0;
    if (forma->sprite!=NULL)
        HGS_SpriteCogerPosicion(forma->sprite,&spX,&spY);
    HGS_BloquearMutex(forma->mutex,HGS_FormaColisionCogerPosicion);
    HGS_FormaGeometricaCogerRectContenedor(forma->forma,x,y,w,h);
    HGS_DesbloquearMutex(forma->mutex,HGS_FormaColisionCogerPosicion);

    (*x)+= spX;
    (*y)+= spY;

}

int HGS_FormaColisionCogerGrupo(HGS_FormaColision * forma){

    return forma->grupo;

}

int * HGS_FormaColisionCogerDatos(HGS_FormaColision * forma){

    return forma->datos;

}


void HGS_FormaColisionCogerCeldas(HGS_FormaColision * forma, int * priX, int * priY, int * ultX, int * ultY){

    *priX= forma->priX;
    *priY= forma->priY;
    *ultX= forma->ultX;
    *ultY= forma->ultY;

}

void HGS_FormaColisionAsignarCeldas(HGS_FormaColision * forma, int priX, int priY, int ultX, int ultY){

    forma->priX= priX;
    forma->priY= priY;
    forma->ultX= ultX;
    forma->ultY= ultY;

}

void HGS_FormaColisionLibera(HGS_FormaColision * forma){

    SDL_free(forma->mutex);
    for (int i=0; i<forma->numAlto; i++){
        for (int j=0; j<forma->numAncho; j++){
            HGS_ListaElementosLiberaElemento(forma->elemento[i][j]);
        }
    }
    for (int i=0; i<forma->numAlto; i++){
        free(forma->elemento[i]);
    }
    free(forma->elemento);
    free(forma);

}
