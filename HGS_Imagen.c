#include "HGS_Imagen.h"

//Funciones externas.
extern SDL_Renderer * HGS_VentanaCogerRenderer();

extern void HGS_VentanaDibujaImagen(SDL_Texture * imagen, double x, double y, double w, double h);
extern void HGS_VentanaDibujaImagenCamara(SDL_Texture * imagen, double x, double y, double w, double h);



/**
*   Estructura de una imagen o animacion.
*/
typedef struct HGS_Imagen{

    int maxAnimaciones;
    int * maxImagenes;
    SDL_Texture *** imagenes;

}HGS_Imagen;



static SDL_Texture * HGS_ImagenLee(char * nombre){

    SDL_Surface * imagen = IMG_Load(nombre);
    if (imagen==NULL){
        return NULL;    //Retornamos null porque necesitamos comprobar el error en la funcion HGS_CreaImagenAnimada.
    }

    SDL_Texture * textura= SDL_CreateTextureFromSurface(HGS_VentanaCogerRenderer(),imagen);

    if (textura==NULL){
        printf("La textura se creo incorrectamente. | HGS_ImagenLee\n");
        exit(EXIT_FAILURE);
    }

    SDL_free(imagen);

    return textura;

}

HGS_Imagen * HGS_ImagenCrea(char * nombre){

    HGS_Imagen * nueva= malloc(sizeof(struct HGS_Imagen));

    nueva->maxAnimaciones=1;
    nueva->maxImagenes= malloc(sizeof(int));
    nueva->maxImagenes[0]=1;

    SDL_Texture * imagen= HGS_ImagenLee(nombre);
    if (imagen == NULL){
        printf("HGS_CreaImagen|HGS_ImagenLee: La imagen es NULL");
        exit(EXIT_FAILURE);
    }
    nueva->imagenes= malloc(sizeof(SDL_Texture**));
    nueva->imagenes[0]= malloc(sizeof(SDL_Texture*));
    nueva->imagenes[0][0]= imagen;

    return nueva;

}

HGS_Imagen * HGS_ImagenAnimadaCrea(char * carpeta){

    int animacion=0;
    int fichero=0;
    int * ficheros;
    int riesgo=0;
    char nombre[50]="";

    //Contamos el numero de carpetas que hay.
    do{
        sprintf(nombre,"%s/Animacion%d/Imagen0.bmp",carpeta,animacion);
        SDL_Texture * imagen= HGS_ImagenLee(nombre);
        if (imagen==NULL){
            riesgo=1;
        }
        else{
            animacion++;
            SDL_free(imagen);
        }
    }while (riesgo!=1);
    if (!animacion) {
        printf("Error en HGS_CreaImagenAnimada: No hay ninguna carpeta o no hay imagenes que se hayan podido leer en la primera carpeta.\n");
        exit(EXIT_FAILURE);
    }
    ficheros= malloc(animacion*sizeof(int));

    //Contamos el numero de imagenes que hay en cada carpeta animacion.
    for (int i=0; i<animacion; i++){
        riesgo=0;
        fichero=0;
        do {
            sprintf(nombre,"%s/Animacion%d/Imagen%d.bmp",carpeta,i,fichero);
            SDL_Texture * imagen= HGS_ImagenLee(nombre);
            if (imagen==NULL){
                if (fichero==0){
                    printf("Error en HGS_CreaImagenAnimada: No hay ninguna imagen en la carpeta %s",nombre);
                    exit(EXIT_FAILURE);
                }
                ficheros[i]=fichero;
                fichero=0;
                riesgo=1;
            }
            else{
                fichero++;
                SDL_free(imagen);
            }
        } while (riesgo!=1);
    }

    //Creamos la variable imagen.
    HGS_Imagen * nueva= malloc(sizeof(struct HGS_Imagen));

    nueva->maxAnimaciones= animacion;
    nueva->maxImagenes= ficheros;

    nueva->imagenes= malloc(animacion*sizeof(struct SDL_Texture**));
    for (int i=0; i<animacion; i++){
        nueva->imagenes[i]=malloc(ficheros[i]*sizeof(struct SDL_Texture*));
    }

    for (int i=0; i<animacion; i++){
        for (int j=0; j<ficheros[i]; j++){
            sprintf(nombre,"%s/Animacion%d/Imagen%d.bmp",carpeta,i,j);
            nueva->imagenes[i][j]= HGS_ImagenLee(nombre);
            if (nueva->imagenes[i][j]==NULL){
                printf("Error en HGS_CreaImagenAnimada: Tras contar, error al leer las imagenes.");
                exit(EXIT_FAILURE);
            }
        }
    }

    return nueva;

}

int HGS_ImagenMaxAnimaciones(HGS_Imagen * imagen){

    return imagen->maxAnimaciones;

}

int HGS_ImagenMaxImagenes(HGS_Imagen * imagen, int animacion){

    if (animacion<imagen->maxAnimaciones){
        return imagen->maxImagenes[animacion];
    }
    return imagen->maxAnimaciones-1;

}


void HGS_ImagenDibuja(HGS_Imagen * imagen, double x, double y, double w, double h, double anchorX, double anchorY, int animacion, int numImagen){

    if (animacion<imagen->maxAnimaciones && numImagen<imagen->maxImagenes[animacion]){
        x-= anchorX*w;
        y-= anchorY*h;
        HGS_VentanaDibujaImagen(imagen->imagenes[animacion][numImagen],x,y,w,h);
    }

}

void HGS_ImagenDibujaCamara(HGS_Imagen * imagen, double x, double y, double w, double h, double anchorX, double anchorY, int animacion, int numImagen){

    if (animacion<imagen->maxAnimaciones && numImagen<imagen->maxImagenes[animacion]){
        x-= anchorX*w;
        y-= anchorY*h;
        HGS_VentanaDibujaImagenCamara(imagen->imagenes[animacion][numImagen],x,y,w,h);
    }

}


void HGS_ImagenLibera(HGS_Imagen * imagen){

    for (int i=0; i<imagen->maxAnimaciones; i++){
        for (int j=0; j<imagen->maxImagenes[i]; j++){
            SDL_free(imagen->imagenes[i][j]);
        }
    }
    for (int i=0; i<imagen->maxAnimaciones; i++){
        free(imagen->imagenes[i]);
    }
    free(imagen->imagenes);

    free(imagen->maxImagenes);

}



//HILOS

typedef struct HGS_HiloDibujo{

    SDL_sem * semPermiso;
    SDL_mutex * mutexSalir;
    int salir; //Solo habra un hilo.
    int (*accionDibujo)(void * datos);
    SDL_Thread * hilo;

}HGS_HiloDibujo;

static HGS_HiloDibujo * hiloDibujo= NULL;


static int HGS_ImagenHiloDibujo(void * datos){

    while (1){

        SDL_SemWait(hiloDibujo->semPermiso);
        HGS_BloquearMutex(hiloDibujo->mutexSalir,HGS_ImagenHiloDibujo);
        int salir= hiloDibujo->salir;
        HGS_DesbloquearMutex(hiloDibujo->mutexSalir,HGS_ImagenHiloDibujo);
        if (salir) return 0;
        hiloDibujo->accionDibujo(datos);

    }

    return 0;

}


void HGS_ImagenCreaHiloDibujo(int (*accionDibujo)(void * datos),void * datos){

    if (hiloDibujo==NULL){
        hiloDibujo= malloc(sizeof(struct HGS_HiloDibujo));
        hiloDibujo->accionDibujo= accionDibujo;
        hiloDibujo->mutexSalir= SDL_CreateMutex();
        hiloDibujo->semPermiso= SDL_CreateSemaphore(0);
        hiloDibujo->salir= 0;
        hiloDibujo->hilo= SDL_CreateThread(HGS_ImagenHiloDibujo,NULL,datos);
    }

}

void HGS_ImagenDarPermisoHiloDibujo(){

    SDL_SemPost(hiloDibujo->semPermiso);

}

void HGS_ImagenTerminaHilo(){

    HGS_BloquearMutex(hiloDibujo->mutexSalir,HGS_ImagenHiloDibujo);
    hiloDibujo->salir= 1;
    HGS_DesbloquearMutex(hiloDibujo->mutexSalir,HGS_ImagenHiloDibujo);
    SDL_SemPost(hiloDibujo->semPermiso);

}

void HGS_ImagenEsperarHiloDibujo(){

    SDL_WaitThread(hiloDibujo->hilo,NULL);
    SDL_free(hiloDibujo->mutexSalir);
    SDL_free(hiloDibujo->semPermiso);
    free(hiloDibujo);
    hiloDibujo= NULL;

}

