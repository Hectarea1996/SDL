#include "HGS_Wrapper.h"
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_thread.h>

#define VEL 400


HGS_Sprite * spriteHeroe;
HGS_Sprite * mapa;
HGS_Sprite * spriteFondo;

int HGS_HiloDibuja(void * datos){

    HGS_SpriteDibuja(spriteFondo);

    HGS_SpriteDibujaCamara(mapa);

    HGS_SpriteDibujaCamara(spriteHeroe);

    HGS_VentanaActualiza();

    return 0;

}



int main(int argc, char *argv[]){

    HGS_VentanaCrea("Prueba",300,300,1);

    HGS_CamaraAsignarLimites(0,1000,0,1000);

    HGS_ESInicializar();

    HGS_Imagen * heroe= HGS_ImagenCrea("Imagenes/Bobble.bmp");
    HGS_Imagen * fondo= HGS_ImagenAnimadaCrea("Imagenes/Paisaje");
    HGS_Imagen * imagenMapa= HGS_ImagenCrea("Imagenes/ImagenPrueba.png");

    spriteHeroe= HGS_SpriteCrea(50,50,50,50,heroe,NULL);
    mapa= HGS_SpriteCrea(300,300,400,400,imagenMapa,NULL);
    spriteFondo= HGS_SpriteCrea(0,0,1366,768,fondo,NULL);
    HGS_SpriteAsignarAnchor(spriteFondo,0,0);

    HGS_CamaraSeguirSprite(spriteHeroe);

    HGS_ImagenCreaHiloDibujo(HGS_HiloDibuja,NULL);

    while (!HGS_ESTecladoTeclaPulsada(SDLK_ESCAPE,NULL)){

        HGS_ESCapturarEventos();

        if (HGS_ESTecladoTeclaEstado(SDLK_a,NULL)) HGS_SpriteMover(spriteHeroe,-VEL,0);
        if (HGS_ESTecladoTeclaEstado(SDLK_w,NULL)) HGS_SpriteMover(spriteHeroe,0,-VEL);
        if (HGS_ESTecladoTeclaEstado(SDLK_s,NULL)) HGS_SpriteMover(spriteHeroe,0,VEL);
        if (HGS_ESTecladoTeclaEstado(SDLK_d,NULL)) HGS_SpriteMover(spriteHeroe,VEL,0);

        HGS_SpriteSiguienteImagenBucle(spriteFondo,10);

        int rueda= HGS_ESRatonRueda();

        if (rueda!=0)
            printf("%d\n",rueda);

        HGS_ImagenDarPermisoHiloDibujo();

        HGS_ControlFrames();

    }

    HGS_ImagenTerminaHilo();
    HGS_ImagenEsperarHiloDibujo();

    return 0;
}
