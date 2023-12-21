#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "graphics.h"
#include "text.h"
#include "imagen.h"
#include "OurTypes.h"
#include "irudi_guztiak.h"
#include <stdio.h>

void osasunBarraPantailaratu(int osasunTotala)
{
    char str[128];
    int aholkuIrudiaDago = 1;

    sprintf(str, "%d", osasunTotala);
    textuaIdatzi(148, 34, str);
}
int osasuna(int hasierakoBizitza, int gehitutakoBizitza)
{

    int bizitzaTotala;

    bizitzaTotala = hasierakoBizitza + gehitutakoBizitza;

    return bizitzaTotala;
}
void ekonomiaBarraPantailaratu(float diruTotala) {
    char str[128];

    sprintf(str, "%.0f", diruTotala);
    textuaIdatzi(148, 88, str);
}
float generadorea(float hasierakoDirua, float irabazitakoa)
{

    float diruTotala;

    diruTotala = hasierakoDirua + irabazitakoa;

    return diruTotala;
}
float ekonomia(float hasierakoDirua, float zergak)
{

    float diruTotala;

    diruTotala = hasierakoDirua + zergak;


    return diruTotala;
}
void hezkuntzaBarraPantailaratu(int hezkuntzaTotala)
{

    char str[128];

    sprintf(str, "%d", hezkuntzaTotala);
    textuaIdatzi(148, 146, str);
}
int hezkuntza(int hasierakoHezkuntza, int gehitutakoHezkuntza)
{

    int hezkuntzaTotala;

    hezkuntzaTotala = hasierakoHezkuntza + gehitutakoHezkuntza;


    return hezkuntzaTotala;
}
int aurrekoAholkuaKendu(int aurrekoAholkua, int aholkuarenIzena)
{

    if (aurrekoAholkua != 0)
    {
        irudiaKendu(aurrekoAholkua);
    }

    aurrekoAholkua = aholkuarenIzena;

    return aurrekoAholkua;
}
int aurrekoIrudiaKendu(int aurrekoArgazkia, int argazkiarenIzena)
{
    if (aurrekoArgazkia != 0)
    {
        irudiaKendu(aurrekoArgazkia);
    }

    aurrekoArgazkia = argazkiarenIzena;

    return aurrekoArgazkia;
}
void konpontzekoEtxeaZeinDenBegiratu(float diruTotala, int osasunTotala, int hezkuntzaTotala, char* irudiarenPrezioa, int ClickKopurua)
{

    int aurrekoArgazkia = 0, irudia = 0;

    if (ClickKopurua == 1) {
        gureGauzak.idMax = irudiaKargatu(EDIFIZIOA_HOBETUTA_DAGO);

        irudiaMugitu(gureGauzak.idMax, 28, 652);

        aurrekoArgazkia=aurrekoIrudiaKendu(aurrekoArgazkia, gureGauzak.idMax);
    }
    else {
        irudia = irudiaKargatu(irudiarenPrezioa);

        irudiaMugitu(irudia, 28, 652);

        aurrekoArgazkia=aurrekoIrudiaKendu(aurrekoArgazkia, irudia);
    }

    irudiakMarraztu();

    ekonomiaBarraPantailaratu(diruTotala);
    osasunBarraPantailaratu(osasunTotala);
    hezkuntzaBarraPantailaratu(hezkuntzaTotala);

    pantailaBerriztu();
}