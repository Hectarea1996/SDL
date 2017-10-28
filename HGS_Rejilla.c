

#include "HGS_Rejilla.h"

#define HGS_TAREAS_TOTAL 50

#define HGS_TAREAS_INSERTAR     0
#define HGS_TAREAS_EXTRAER      1
#define HGS_TAREAS_ACTUALIZAR   2


//FUNCIONES EXTERNAS
extern HGS_FormaColision * HGS_FormaColisionCrea(int HGS_FORMA, HGS_Sprite * sprite, double relX, double relY, double w, double h, int numAncho, int numAlto, void * datos, int grupo);
extern void HGS_FormaColisionCogerRectContenedor(HGS_FormaColision * forma, double * x, double * y, double * w, double * h);
extern HGS_Elemento *** HGS_FormaColisionCogerElementos(HGS_FormaColision * formaColision);
void HGS_FormaColisionCogerCeldas(HGS_FormaColision * forma, int * priX, int * priY, int * ultX, int * ultY);
void HGS_FormaColisionAsignarCeldas(HGS_FormaColision * forma, int priX, int priY, int ultX, int ultY);
void HGS_FormaColisionCogerNumCeldas(HGS_FormaColision * forma, int * numAncho, int * numAlto);
int HGS_FormaColisionCogerGrupo(HGS_FormaColision * forma);
int * HGS_FormaColisionCogerDatos(HGS_FormaColision * forma);

//FUNCIONES DECLARADAS
static SDL_Thread * HGS_RejillaCreaHiloActualizar(HGS_Rejilla * rejilla);
static void HGS_RejillaTerminarHiloActualizar(HGS_Rejilla * rejilla);
static void HGS_RejillaEsperarHiloActualizar(SDL_Thread * hiloRejilla);


typedef struct HGS_Rejilla{

    SDL_mutex * mutexCantidad;      //Mutex para pedir el numero de tareas pendientes.

    SDL_sem * semProductor;
    SDL_sem * semConsumidor;
    HGS_Tareas * tareas;

    SDL_mutex * permisoRejilla;     //Mientras haya algo que actualizar, el mutex se quedara bloqueado.
    HGS_ListaElementos *** rejilla;
    double x,y;
    int numAncho;
    int numAlto;
    double wCelda;
    double hCelda;

    SDL_Thread * hiloRejilla;

    SDL_mutex * mutexSalida;
    int salir;

}HGS_Rejilla;


HGS_Rejilla * HGS_RejillaCrea(double x, double y, double ancho, double alto, double wCelda, double hCelda){

    HGS_Rejilla * rejilla= malloc(sizeof(struct HGS_Rejilla));

    //Mutex.
    rejilla->permisoRejilla= SDL_CreateMutex();
    rejilla->mutexSalida= SDL_CreateMutex();
    rejilla->mutexCantidad= SDL_CreateMutex();

    //Semaforos.
    rejilla->semProductor= SDL_CreateSemaphore(HGS_TAREAS_TOTAL);
    rejilla->semConsumidor= SDL_CreateSemaphore(0);

    //Dimensiones.
    rejilla->x= x;
    rejilla->y= y;
    rejilla->wCelda= wCelda;
    rejilla->hCelda= hCelda;
    rejilla->numAlto= (int) alto/hCelda;
    rejilla->numAncho= (int) ancho/wCelda;
    rejilla->salir= 0;

    //Tareas
    rejilla->tareas= HGS_TareasCrear(HGS_TAREAS_TOTAL);

    //Rejilla.
    rejilla->rejilla= malloc(sizeof(HGS_ListaElementos**)*rejilla->numAlto);
    for (int i=0; i<rejilla->numAlto; i++){
        rejilla->rejilla[i]= malloc(sizeof(HGS_ListaElementos*)*rejilla->numAncho);
        for (int j=0; j<rejilla->numAncho; j++){
            rejilla->rejilla[i][j]= HGS_ListaElementosCrea();
        }
    }

    //Hilo.
    rejilla->hiloRejilla= HGS_RejillaCreaHiloActualizar(rejilla);

    return rejilla;

}

void HGS_RejillaLibera(HGS_Rejilla * rejilla){

    //Hilo.
    HGS_RejillaTerminarHiloActualizar(rejilla);
    HGS_RejillaEsperarHiloActualizar(rejilla->hiloRejilla);

    //Mutex.
    SDL_free(rejilla->permisoRejilla);
    SDL_free(rejilla->mutexSalida);
    SDL_free(rejilla->mutexCantidad);

    //Semaforos.
    SDL_free(rejilla->semProductor);
    SDL_free(rejilla->semConsumidor);

    //Tareas.
    HGS_TareasLibera(rejilla->tareas);

    //Rejilla.
    for (int i=0; i<rejilla->numAlto; i++){
        for (int j=0; j<rejilla->numAncho; j++){
            HGS_ListaElementosLibera(rejilla->rejilla[i][j]);
        }
        free(rejilla->rejilla[i]);
    }
    free(rejilla->rejilla);

}

HGS_FormaColision * HGS_RejillaCreaFormaColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, int HGS_FORMA, double relX, double relY, double w, double h){

    //Calculamos el numero de elementos de la forma de colision.
    int celdasExtraX,celdasExtraY;
    int numCeldasX,numCeldasY;
    numCeldasX=(int) w/rejilla->wCelda;
    numCeldasY=(int) h/rejilla->hCelda;
    if (((double)numCeldasX)*rejilla->wCelda==w) celdasExtraX= 1;
    else celdasExtraX= 2;
    if (((double)numCeldasY)*rejilla->hCelda==h) celdasExtraY= 1;
    else celdasExtraY= 2;
    numCeldasX+= celdasExtraX;
    numCeldasY+= celdasExtraY;

    //Creamos la formaColision.
    HGS_FormaColision * forma= HGS_FormaColisionCrea(HGS_FORMA,sprite,relX,relY,w,h,numCeldasX,numCeldasY,datos,grupo);

    return forma;

}

HGS_FormaColision * HGS_RejillaCreaRectanguloColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY, double w, double h){

    return HGS_RejillaCreaFormaColision(rejilla,sprite,datos,grupo,HGS_FORMA_RECTANGULO,relX,relY,w,h);

}

HGS_FormaColision * HGS_RejillaCreaCirculoColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY, double r){

    return HGS_RejillaCreaFormaColision(rejilla,sprite,datos,grupo,HGS_FORMA_CIRCULO,relX-r,relY-r,r*2,r*2);

}

HGS_FormaColision * HGS_RejillaCreaPuntoColision(HGS_Rejilla * rejilla, HGS_Sprite * sprite, void * datos, int grupo, double relX, double relY){

    return HGS_RejillaCreaFormaColision(rejilla,sprite,datos,grupo,HGS_FORMA_PUNTO,relX,relY,0,0);

}

void HGS_RejillaTareaInsertaFormaColision(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    double xRect,yRect,wRect,hRect;
    HGS_FormaColisionCogerRectContenedor(forma,&xRect,&yRect,&wRect,&hRect);

    //Ajustar la formaColision a la posicion de la rejilla.
    xRect-= rejilla->x;
    yRect-= rejilla->y;

    //Calculamos las celdas.
    int xCelda= (int) xRect/rejilla->wCelda;
    int ultCeldaX= (int) (xRect+wRect)/rejilla->wCelda;
    int yCelda= (int) yRect/rejilla->hCelda;
    int ultCeldaY= (int) (yRect+hRect)/rejilla->hCelda;

    //Cogemos los elementosRejilla.
    HGS_Elemento *** elementos= HGS_FormaColisionCogerElementos(forma);

    int itCeldaY=yCelda;
    int i=0;
    while (itCeldaY<=ultCeldaY){
        int itCeldaX=xCelda;
        int j=0;
        while (itCeldaX<=ultCeldaX){
            if (itCeldaX>=0 && itCeldaY>=0 && itCeldaX<rejilla->numAlto && itCeldaY<rejilla->numAlto)
                HGS_ListaElementosInsertaElemento(rejilla->rejilla[itCeldaY][itCeldaX],elementos[i][j]);
            itCeldaX++;
            j++;
        }
        itCeldaY++;
        i++;
    }

    //Actualizamos las variables.
    HGS_FormaColisionAsignarCeldas(forma,xCelda,yCelda,ultCeldaX,ultCeldaY);

}

void HGS_RejillaTareaExtraeFormaColision(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    //Cogemos los elementosRejilla.
    HGS_Elemento *** elementos= HGS_FormaColisionCogerElementos(forma);

    //Sacamos el RectColision de la rejilla.
    int yCelda,xCelda,ultCeldaX,ultCeldaY;
    HGS_FormaColisionCogerCeldas(forma,&xCelda,&yCelda,&ultCeldaX,&ultCeldaY);

    int itCeldaY=yCelda;
    int i=0;
    while (itCeldaY<=ultCeldaY){
        int itCeldaX=xCelda;
        int j=0;
        while (itCeldaX<=ultCeldaX){
            if (itCeldaX>=0 && itCeldaY>=0 && itCeldaX<rejilla->numAlto && itCeldaY<rejilla->numAlto)
                HGS_ListaElementosExtraeElemento(rejilla->rejilla[itCeldaY][itCeldaX],elementos[i][j]);
            itCeldaX++;
            j++;
        }
        itCeldaY++;
        i++;
    }

}

void HGS_RejillaTareaActualizaFormaColision(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    //Comprobamos si hay que actualizar de verdad.
    double xRect,yRect,wRect,hRect;
    HGS_FormaColisionCogerRectContenedor(forma,&xRect,&yRect,&wRect,&hRect);

    //Calculamos las nuevas celdas.
    int nuevaCeldaX= (int) xRect/rejilla->wCelda;
    int nuevaUltCeldaX= (int) (xRect+wRect)/rejilla->wCelda;
    int nuevaCeldaY= (int) yRect/rejilla->hCelda;
    int nuevaUltCeldaY= (int) (yRect+hRect)/rejilla->hCelda;

    //Cogemos la antiguas.
    int xCelda,yCelda,ultCeldaX,ultCeldaY;
    HGS_FormaColisionCogerCeldas(forma,&xCelda,&yCelda,&ultCeldaX,&ultCeldaY);

    //Si son iguales no hace falta actualizar.
    if (xCelda==nuevaCeldaX && yCelda==nuevaCeldaY && ultCeldaX==nuevaUltCeldaX && ultCeldaY==nuevaUltCeldaY) return;

    HGS_RejillaTareaExtraeFormaColision(rejilla,forma);
    HGS_RejillaTareaInsertaFormaColision(rejilla,forma);

}

static void HGS_RejillaInsertarTarea(HGS_Rejilla * rejilla, HGS_FormaColision * forma, int HGS_TAREA){

    //Pedimos producir.
    SDL_SemWait(rejilla->semProductor);
    //Insertamos la forma en las tareas.
    HGS_TareasInsertar(rejilla->tareas,forma,HGS_TAREA);
    //Si no habian elementos, bloqueamos el mutex.
    HGS_BloquearMutex(rejilla->mutexCantidad,HGS_RejillaInsertarTarea);
    if (HGS_TareasCantidad(rejilla->tareas)==1)
        HGS_BloquearMutex(rejilla->permisoRejilla,HGS_RejillaFormaColisionActualizar);
    HGS_DesbloquearMutex(rejilla->mutexCantidad,HGS_RejillaInsertarTarea);
    //Le dejamos al consumidor trabajar.
    SDL_SemPost(rejilla->semConsumidor);

}

void HGS_RejillaFormaColisionInsertar(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    HGS_RejillaInsertarTarea(rejilla,forma,HGS_TAREAS_INSERTAR);

}

void HGS_RejillaFormaColisionExtraer(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    HGS_RejillaInsertarTarea(rejilla,forma,HGS_TAREAS_EXTRAER);

}

void HGS_RejillaFormaColisionActualizar(HGS_Rejilla * rejilla, HGS_FormaColision * forma){

    HGS_RejillaInsertarTarea(rejilla,forma,HGS_TAREAS_ACTUALIZAR);

}




static int HGS_RejillaActualizarRejilla(void * datos){

    HGS_Rejilla * rejilla= (HGS_Rejilla*) datos;

    while (1){
        //Pedimos permiso para cosumir.
        SDL_SemWait(rejilla->semConsumidor);
        //Si salir==1, salimos.
        HGS_BloquearMutex(rejilla->mutexSalida,HGS_RejillaActualizarRejilla);
        int salir= rejilla->salir;
        HGS_DesbloquearMutex(rejilla->mutexSalida,HGS_RejillaActualizarRejilla);
        if(salir) return 0;
        //Cogemos una tarea
        int tipoTarea;
        HGS_FormaColision * forma= HGS_TareasSacar(rejilla->tareas,&tipoTarea);
        //Ejecutamos la tarea.
        switch(tipoTarea){
            case HGS_TAREAS_INSERTAR:
                HGS_RejillaTareaInsertaFormaColision(rejilla,forma);
                break;
            case HGS_TAREAS_EXTRAER:
                HGS_RejillaTareaExtraeFormaColision(rejilla,forma);
                break;
            case HGS_TAREAS_ACTUALIZAR:
                HGS_RejillaTareaActualizaFormaColision(rejilla,forma);
                break;
        }
        //Si era el ultimo en ser actualizado, desbloqueamos el mutex.
        HGS_BloquearMutex(rejilla->mutexCantidad,HGS_RejillaActualizarRejilla);
        if (HGS_TareasCantidad(rejilla->tareas)==0)
            HGS_DesbloquearMutex(rejilla->permisoRejilla,RejillaActualizarNivel);
        HGS_DesbloquearMutex(rejilla->mutexCantidad,HGS_RejillaActualizarRejilla);
        //Dejamos producir.
        SDL_SemPost(rejilla->semProductor);
    }

    return 0;

}

void HGS_RejillaFormaColisionActua(HGS_FormaColision * forma, int (*accion)(int grupoSrc, void * datosSrc, int grupoDst,void * datosDst)){

    int numAncho,numAlto;
    int fin= 0;
    HGS_FormaColisionCogerNumCeldas(forma,&numAncho,&numAlto);
    int grupoSrc= HGS_FormaColisionCogerGrupo(forma);
    void * datosSrc= HGS_FormaColisionCogerDatos(forma);
    HGS_Elemento *** elementos= HGS_FormaColisionCogerElementos(forma);

    //Primera pasada.
    for (int i=0; i<numAlto-1; i++){
        for (int j=0; j<numAncho-1; j++){
            HGS_Elemento * it=elementos[i][j];
            while((it=HGS_ListaElementosAnteriorElemento(it))!=NULL){
                int marca= HGS_ListaElementosCogerMarca(it);
                if (marca==3){
                    fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                    if (fin) return;
                }
            }
            it=elementos[i][j];
            while((it=HGS_ListaElementosSiguienteElemento(it))!=NULL){
                int marca= HGS_ListaElementosCogerMarca(it);
                if (marca==3){
                    fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                    if (fin) return;
                }
            }
        }
    }

    //Segunda pasada.
    for (int i=0; i<numAlto-1; i++){
        HGS_Elemento * it=elementos[i][numAncho-1];
        while((it=HGS_ListaElementosAnteriorElemento(it))!=NULL){
            int marca= HGS_ListaElementosCogerMarca(it);
            if (marca==2){
                fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                if (fin) return;
            }
        }
        it=elementos[i][numAncho-1];
        while((it=HGS_ListaElementosSiguienteElemento(it))!=NULL){
            int marca= HGS_ListaElementosCogerMarca(it);
            if (marca==2){
                fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                if (fin) return;
            }
        }
    }

    //Tercera pasada.
    for (int j=0; j<numAncho-1; j++){
        HGS_Elemento * it=elementos[numAlto-1][j];
        while((it=HGS_ListaElementosAnteriorElemento(it))!=NULL){
            int marca= HGS_ListaElementosCogerMarca(it);
            if (marca==1){
                fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                if (fin) return;
            }
        }
        it=elementos[numAlto-1][j];
        while((it=HGS_ListaElementosSiguienteElemento(it))!=NULL){
            int marca= HGS_ListaElementosCogerMarca(it);
            if (marca==1){
                fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
                if (fin) return;
            }
        }
    }

    //Ultima pasada.
    HGS_Elemento * it=elementos[numAlto-1][numAncho-1];
    while((it=HGS_ListaElementosAnteriorElemento(it))!=NULL){
        fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
        if (fin) return;
    }
    it=elementos[numAlto-1][numAncho-1];
    while((it=HGS_ListaElementosSiguienteElemento(it))!=NULL){
        fin= accion(grupoSrc,datosSrc,HGS_ListaElementosCogerGrupo(it),HGS_ListaElementosCogerDatos(it));
        if (fin) return;
    }


}


//HILOS

static SDL_Thread * HGS_RejillaCreaHiloActualizar(HGS_Rejilla * rejilla){

    SDL_Thread * hiloRejilla= SDL_CreateThread(HGS_RejillaActualizarRejilla,NULL,(void*)rejilla);
    return hiloRejilla;

}


static void HGS_RejillaTerminarHiloActualizar(HGS_Rejilla * rejilla){

    HGS_BloquearMutex(rejilla->mutexSalida,HGS_RejillaTerminarHiloActualizar);
    rejilla->salir= 1;
    HGS_DesbloquearMutex(rejilla->mutexSalida,HGS_RejillaTerminarHiloActualizar);
    SDL_SemPost(rejilla->semConsumidor);

}

static void HGS_RejillaEsperarHiloActualizar(SDL_Thread * hiloRejilla){

    SDL_WaitThread(hiloRejilla,NULL);

}

