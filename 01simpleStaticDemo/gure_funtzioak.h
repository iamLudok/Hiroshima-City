#ifndef GURE_FUNTZIOAK_H
#define GURE_FUNTZIOAK_H

void osasunBarraPantailaratu(int osasunTotala);
int osasuna(int hasierakoBizitza, int gehitutakoBizitza);
void ekonomiaBarraPantailaratu(float diruTotala);
float generadorea(float hasierakoDirua, float irabazitakoa);
float ekonomia(float hasierakoDirua, float zergak);
void hezkuntzaBarraPantailaratu(int hezkuntzaTotala);
int hezkuntza(int hasierakoHezkuntza, int gehitutakoHezkuntza);
int aurrekoAholkuaKendu(int aurrekoAholkua, int aholkuarenIzena);
int aurrekoIrudiaKendu(int aurrekoArgazkia, int argazkiarenIzena);
void konpontzekoEtxeaZeinDenBegiratu(float diruTotala, int osasunTotala, int hezkuntzaTotala, char* irudiarenPrezioa, int ClickKopurua);

#endif