
#include "HGS_Control.h"

typedef struct HGS_Control{

    double multFrame;
    double framesPerSecond;

}HGS_Control;


static HGS_Control control;


double HGS_ControlCogerFPS(){

    return control.framesPerSecond;

}

void HGS_ControlFrames(){

    static long ciclosAnt= 0;
    static long ciclosAct= 0;
    static int ciclos= 500000;

    ciclosAct= SDL_GetTicks();

    if (ciclosAct!=ciclosAnt){
        control.framesPerSecond= (1000.0/(double)(ciclosAct-ciclosAnt))*(double)ciclos;
        control.multFrame= 1.0/control.framesPerSecond;
        //printf("MultFrame: %g\t\tFPS: %g\n",control.multFrame,control.framesPerSecond);
        ciclosAnt= ciclosAct;
        ciclos=1;
    }
    else ciclos++;

}


double * HGS_ControlCogerMultFrames(){

    return &control.multFrame;

}
