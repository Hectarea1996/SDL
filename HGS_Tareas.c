
#include "HGS_Tareas.h"


typedef struct HGS_Tareas{

    int maxCantidad;
    int cantidad;
    int sigHueco;
    int sigExtraer;
    int * tipo;
    HGS_FormaColision ** forma;

}HGS_Tareas;


HGS_Tareas * HGS_TareasCrear(int cantidad){

    HGS_Tareas * nuevo= malloc(sizeof(struct HGS_Tareas));

    nuevo->forma= malloc(sizeof(struct HGS_FormaColision*)*cantidad);
    nuevo->tipo= malloc(sizeof(int)*cantidad);
    nuevo->sigExtraer= 0;
    nuevo->sigHueco= 0;
    nuevo->cantidad= 0;
    nuevo->maxCantidad= cantidad;

    return nuevo;

}

int HGS_TareasCantidad(HGS_Tareas * tareas){

    return tareas->cantidad;

}

int HGS_TareasInsertar(HGS_Tareas * tareas, HGS_FormaColision * forma, int tipo){

    if (tareas->cantidad==tareas->maxCantidad){
        return -1;
    }

    tareas->forma[tareas->sigHueco]= forma;
    tareas->tipo[tareas->sigHueco]= tipo;
    tareas->sigHueco= (tareas->sigHueco+1)%tareas->maxCantidad;
    tareas->cantidad++;

    return 0;

}

HGS_FormaColision * HGS_TareasSacar(HGS_Tareas * tareas, int * tipo){

    if (tareas->cantidad==tareas->maxCantidad){
        return NULL;
    }

    HGS_FormaColision * dev= tareas->forma[tareas->sigExtraer];
    *tipo= tareas->tipo[tareas->sigExtraer];
    tareas->sigExtraer= (tareas->sigExtraer+1)%tareas->maxCantidad;
    tareas->cantidad--;

    return dev;

}

void HGS_TareasLibera(HGS_Tareas * tareas){

    free(tareas->tipo);
    free(tareas->forma);
    free(tareas);

}
