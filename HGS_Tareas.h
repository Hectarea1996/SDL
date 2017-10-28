#ifndef HGS_TAREAS_H_INCLUDED
#define HGS_TAREAS_H_INCLUDED

typedef struct HGS_Tareas HGS_Tareas;

#include <stdlib.h>
#include "HGS_Rejilla.h"


HGS_Tareas * HGS_TareasCrear(int cantidad);

int HGS_TareasCantidad(HGS_Tareas * tareas);

int HGS_TareasInsertar(HGS_Tareas * tareas, HGS_FormaColision * forma, int tipo);

HGS_FormaColision * HGS_TareasSacar(HGS_Tareas * tareas, int * tipo);

void HGS_TareasLibera(HGS_Tareas * tareas);


#endif // HGS_TAREAS_H_INCLUDED
