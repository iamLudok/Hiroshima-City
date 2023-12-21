#ifndef JOKALARIA_H
#define JOKALARIA_H

typedef enum { JOLASTEN, GALDU, IRABAZI }EGOERA;

typedef struct
{
    POSIZIOA pos;
    int id;    
}JOKO_ELEMENTUA;

EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria)
{
    EGOERA  ret = JOLASTEN;
    POSIZIOA posizio;
    int ebentu = 0;
    posizio = saguarenPosizioa();
    ebentu = ebentuaJasoGertatuBada();

    if ((posizio.x > jokalaria.pos.x) && (posizio.x < jokalaria.pos.x + 32) && (posizio.y > jokalaria.pos.y) && (posizio.y < jokalaria.pos.y + 32) && (ebentu == SAGU_BOTOIA_EZKERRA)) {
        ret = GALDU;
    }

    return ret;
}

POSIZIOA ERREALITATE_FISIKOA_mugimendua(POSIZIOA posizioa)
{

    if (posizioa.x <= 950 && posizioa.x > 480 && posizioa.y == 429)//EZKERRA
    {
        posizioa.x = posizioa.x - 1;
        posizioa.y = posizioa.y;
    }
    if (posizioa.x == 480 && posizioa.y <= 429 && posizioa.y > 300)//GORA
    {
        posizioa.y = posizioa.y - 1;
        posizioa.x = posizioa.x;
    }
    if (posizioa.y == 300 && posizioa.x < 500)//ESKUMA
    {
        posizioa.x = posizioa.x + 1;
        posizioa.y = posizioa.y;
    }
    if (posizioa.x == 500 && posizioa.y <= 300 && posizioa.y > 200)//GORA
    {
        posizioa.y = posizioa.y - 1;
        posizioa.x = posizioa.x;
    }
    if (posizioa.x >= 500 && posizioa.x < 950 && posizioa.y == 200)//ESKUMA
    {
        posizioa.y = posizioa.y;
        posizioa.x = posizioa.x + 1;
    }
    if (posizioa.x == 950 && posizioa.y <= 200 && posizioa.y > -32)//GORA
    {
        posizioa.y = posizioa.y - 1;
        posizioa.x = posizioa.x;
    }


    return posizioa;
}

int JOKOA_jokalariaIrudiaSortu();

#endif