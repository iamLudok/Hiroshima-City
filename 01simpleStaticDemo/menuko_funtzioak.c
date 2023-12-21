#include "graphics.h"
#include "text.h"
#include "OurTypes.h"
#include "irudi_guztiak.h"
#include "imagen.h"
#include "soinua.h"
#include "gure_funtzioak.h"
#include "kanta_guztiak.h"
#include <stdio.h>

int jokoahasieratu(void)
{
    int bizitza = 50, garuna = 0;
    float dirua = 500;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    textuaGaitu();
    pantailaGarbitu();

    gureGauzak.idAtzekoPlanoa = irudiaKargatu(ATZEALDEA);
    gureGauzak.idEtxea1Apurtuta = irudiaKargatu(ETXEA1_APURTUTA);
    gureGauzak.idBankuaApurtuta = irudiaKargatu(BANKUA_APURTUTA);
    gureGauzak.idHospitaleaApurtuta = irudiaKargatu(HOSPITALEA_APURTUTA);
    gureGauzak.idMerkatuaApurtuta = irudiaKargatu(MERKATUA_APURTUTA);
    gureGauzak.idUdaletxeaApurtuta = irudiaKargatu(UDALETXEA_APURTUTA);
    gureGauzak.idErrekolektoreGrisa = irudiaKargatu(ERREKOLEKTOREA);

    irudiaMugitu(gureGauzak.idAtzekoPlanoa, 0, 0);
    irudiaMugitu(gureGauzak.idEtxea1Apurtuta, 442, 18);
    irudiaMugitu(gureGauzak.idBankuaApurtuta, 950, 354);
    irudiaMugitu(gureGauzak.idHospitaleaApurtuta, 790, 67);
    irudiaMugitu(gureGauzak.idMerkatuaApurtuta, 550, 238);
    irudiaMugitu(gureGauzak.idUdaletxeaApurtuta, 750, 234);
    irudiaMugitu(gureGauzak.idErrekolektoreGrisa, 997, 579);

    irudiakMarraztu();

    osasunBarraPantailaratu(bizitza);
    ekonomiaBarraPantailaratu(dirua);
    hezkuntzaBarraPantailaratu(garuna);

    pantailaBerriztu();

    return 0;
}
int hasieratu(void)
{
    int ebentu = 0, irten = 0;
    POSIZIOA pos;
    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    textuaGaitu();
    gureGauzak.idHiroshima = irudiaKargatu(MENUA);
    irudiaMugitu(gureGauzak.idHiroshima, 0, 0);
    irudiakMarraztu();
    pantailaBerriztu();

    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 520) && (pos.x < 520 + 266) && (pos.y > 231) && (pos.y < 231 + 73))
            {
                sgItxi1();
                return 0; //jolastu                
            }
            if ((pos.x > 520) && (pos.x < 520 + 266) && (pos.y > 336) && (pos.y < 336 + 73))
            {
                sgItxi1();
                Ezarpenak(); //Ezarpenak
                irten = -1;
            }
            if ((pos.x > 520) && (pos.x < 520 + 266) && (pos.y > 564) && (pos.y < 564 + 73))
            {
                sgItxi();    //Itxi
            }
            if ((pos.x > 520) && (pos.x < 520 + 266) && (pos.y > 453) && (pos.y < 453 + 73))
            {
                sgItxi1();
                Guida(); //gida
                irten = -1;
            }
        }
    }

    return 0;
}
int Ezarpenak(void)
{
    int ebentu = 0, irten = 0, x = 2;
    POSIZIOA pos;


    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    pantailaGarbitu();

    gureGauzak.idIrten = irudiaKargatu(EZARPENAK);
    irudiaMugitu(gureGauzak.idIrten, 0, 0);
    irudiakMarraztu();
    pantailaBerriztu();
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 26) && (pos.y < 26 + 66))
            {
                sgItxi1();
                hasieratu();   // atzera
                irten = -1;
            }
            if ((pos.x > 472) && (pos.x < 472 + 396) && (pos.y > 456) && (pos.y < 456 + 118))
            {
                sgItxi1();
                musika1();    //AUKERATU MUSIKA
                irten = -1;
            }
            if ((pos.x > 472) && (pos.x < 472 + 396) && (pos.y > 144) && (pos.y < 144 + 118))
            {
                toggleMusic(); //ON OFF
            }
            if ((pos.x > 472) && (pos.x < 472 + 396) && (pos.y > 300) && (pos.y < 300 + 118))
            {
                sgItxi1();
                Kredituak();      //GIDA
                irten = -1;
            }

        }
    }
    return 0;
}
int Kredituak(void)
{
    int ebentu = 0, irten = 0;
    POSIZIOA pos;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    gureGauzak.idGida = irudiaKargatu(KREDITUAK);
    irudiaMugitu(gureGauzak.idGida, 1, 1);
    irudiakMarraztu();
    pantailaBerriztu();
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 26) && (pos.y < 26 + 66))
            {
                sgItxi1();
                hasieratu();   // atzera
                irten = -1;
            }
        }
    }
    return 0;
}
int Guida(void)
{
    int ebentu = 0, irten = 0, pantalla = 0;
    POSIZIOA pos;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    
    gureGauzak.idTutoriala12 = irudiaKargatu(TUTORIALA12);
    irudiaMugitu(gureGauzak.idTutoriala12, 0, 0);
    irudiakMarraztu();
    pantailaBerriztu();
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 26) && (pos.y < 26 + 66))
            {
                sgItxi1();
                hasieratu();
                irten = -1;
            }
            switch (pantalla)
            {
            case(0):
                gureGauzak.idTutoriala34 = irudiaKargatu(TUTORIALA34);
                irudiaKendu(gureGauzak.idTutoriala12);
                irudiaMugitu(gureGauzak.idTutoriala34, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
                pantalla++;
                break;
            case(1):
                gureGauzak.idTutoriala5 = irudiaKargatu(TUTORIALA5);
                irudiaKendu(gureGauzak.idTutoriala34);
                irudiaMugitu(gureGauzak.idTutoriala5, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
                pantalla++;
                break;
            case(2):
                gureGauzak.idTutoriala6 = irudiaKargatu(TUTORIALA6);
                irudiaKendu(gureGauzak.idTutoriala5);
                irudiaMugitu(gureGauzak.idTutoriala6, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
                pantalla++;
                break;
            }
            /*if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 631) && (pos.y < 631 + 66))
            {
                gureGauzak.idTutoriala34 = irudiaKargatu(TUTORIALA34);
                irudiaKendu(gureGauzak.idTutoriala12);
                irudiaMugitu(gureGauzak.idTutoriala34, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
                
            }
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 631) && (pos.y < 631 + 66) )
            {
                gureGauzak.idTutoriala5 = irudiaKargatu(TUTORIALA5);
                irudiaKendu(gureGauzak.idTutoriala34);
                irudiaMugitu(gureGauzak.idTutoriala5, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
            }
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 631) && (pos.y < 631 + 66))
            {
                gureGauzak.idTutoriala6 = irudiaKargatu(TUTORIALA6);
                irudiaKendu(gureGauzak.idTutoriala5);
                irudiaMugitu(gureGauzak.idTutoriala6, 0, 0);
                irudiakMarraztu();
                pantailaBerriztu();
            }*/
        }
    }
    return 0;
}
int musika1(void) // FALTA ALGUNA COSITA
{
    int ebentu = 0, irten = 0;
    POSIZIOA pos;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    gureGauzak.idIrten = irudiaKargatu(MUSIKA_AUKERATU);
    irudiaMugitu(gureGauzak.idIrten, 0, 0);
    irudiakMarraztu();
    pantailaBerriztu();
    while (!irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 1246) && (pos.x < 1246 + 66) && (pos.y > 26) && (pos.y < 26 + 66))
            {
                sgItxi1();
                Ezarpenak();   // atzera
                irten = -1;
            }
            audioInit();
            if ((pos.x > 357) && (pos.x < 357 + 176) && (pos.y > 259) && (pos.y < 259 + 124))
            {
                if (!loadTheMusic(KANTA4))
                {
                    fprintf(stderr, "Unable to load music %s\n", SDL_GetError());
                    //return 0;
                }
            }
            if ((pos.x > 356) && (pos.x < 356 + 176) && (pos.y > 511) && (pos.y < 511 + 124))
            {
                if (!loadTheMusic(KANTA3))
                {
                    fprintf(stderr, "Unable to load music %s\n", SDL_GetError());
                    //return 0;
                }
            }
            if ((pos.x > 737) && (pos.x < 737 + 176) && (pos.y > 259) && (pos.y < 259 + 124))
            {
                if (!loadTheMusic(KANTA2))
                {
                    fprintf(stderr, "Unable to load music %s\n", SDL_GetError());
                    //return 0;
                }
            }
            if ((pos.x > 737) && (pos.x < 737 + 176) && (pos.y > 511) && (pos.y < 511 + 124))
            {
                if (!loadTheMusic(KANTA1))
                {
                    fprintf(stderr, "Unable to load music %s\n", SDL_GetError());
                    //return 0;
                }
            }
        }
    }
    return 0;
}