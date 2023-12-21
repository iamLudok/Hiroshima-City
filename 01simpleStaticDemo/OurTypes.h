#ifndef OURTYPES_H
#define OURTYPES_H

#include "ebentoak.h"

#define SOINU_KOP 4

typedef struct S_GURE_GAUZAK
{
    int idSounds[SOINU_KOP];
    int idAtzekoPlanoa, idAholkuak1, idAholkuak2, idAholkuak3, idMax, idLapurra, idAholkuak4, idIrabazi, idKantak, idIrten, idHiroshima, idBotoiak, idEzarpenak, idBolumena, idGida, idUrrea, idGameOver, idEtxea1Apurtuta, idEtxea1Konponduta, idErrekolektoreGrisa, idEtxea2Konponduta, idEtxea3Konponduta, idBankuaApurtuta, idBankuaKonponduta, idHospitaleaApurtuta, idHospitaleaKonponduta, idMerkatuaApurtuta, idMerkatuaKonponduta, idDendaBotoia, idUdaletxeaApurtuta, idUnibertsitateaKonponduta, idEskolaKonponduta, idHEtxea, idHZentral, idHUni, idHEskola, idZentrala, idKiroldegia, idKebab, idHKebab, idHKiroldegi, idGuztiakdauzkazu, idNoMoney, idPEtxea, idPMerkatua, idPHospitala, idPBankua, idPUdaletxea, idHobekuntzaGuztiakDituzu, idTutoriala12, idTutoriala34, idTutoriala5, idTutoriala6;

}GURE_GAUZAK;
GURE_GAUZAK gureGauzak;

#endif