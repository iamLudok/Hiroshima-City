#define _CRT_SECURE_NO_WARNINGS

#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include "gure_funtzioak.h"
#include "irabazi_eta_galdu_pantailak.h"
#include "irudi_guztiak.h"
#include "jokalaria.h"
#include "menuko_funtzioak.h"
#include "kanta_guztiak.h"
#include <stdio.h>
#include "OurTypes.h"
#include <time.h>
#include <windows.h>

char* soundFiles[] = { ".\\sound\\error.wav", ".\\sound\\coin.wav", ".\\sound\\construction.wav", ".\\sound\\buy.wav" }; //Soinu efektuak definitzen dira

int main(int argc, char* str[])
{
    int ebentu = 0, irten = 0, i = 0, sartuda = 0, bizitza = 0, garuna = 0, Etxea1ClickKopurua = 0, BankuaClickKopurua = 0, HospitaleaClickKopurua = 0, MerkatuaClickKopurua = 0, hobetutakoak = 0;
    int etxeaktope = 0, etxekop = 1, osasunTotala = 50, hezkuntzaTotala = 0, errekolektoreKontadorea = 1;
    int sorpresa = 0;
    int sartuDa = 0, HezkuntzaOngi1 = 0, behinSartu = 0, lapurra = 0;
    float biderkatzaileBerria = 0, biderkatzailea = 1, urrea = 0, diruTotala = 500, minus = 0;
    int aurrekoAholkua = 0, UdaletxeaClickKopurua = 0;
    POSIZIOA pos;
    EGOERA  egoera = JOLASTEN;
    POSIZIOA aux;
    JOKO_ELEMENTUA jokalaria;
    clock_t hasiera, diferentzia, hasiera2, diferentzia2;
    hasiera = clock(); //Erlojuaren hasierako denbora gordetzen du hasiera aldagaian
    hasiera2 = clock(); //Erlojuaren hasierako denbora gordetzen du hasiera2 aldagaian
    

    audioInit(); //Musika hasteko funtzioari deia
    for (i = 0; i < SOINU_KOP; i++) //Musika ez baldin bada kargatzen, errorea pantailaratzen du
    {
        if ((gureGauzak.idSounds[i] = loadSound(soundFiles[i])) == -1)
        {
            fprintf(stderr, "Unable to load sound %s\n", SDL_GetError());
            return 0;
        }
    }
    if (!loadTheMusic(KANTA4)) //Hasieran musika kargatzeko
    {
        fprintf(stderr, "Unable to load music %s\n", SDL_GetError());
        return 0;
    }

    hasieratu(); //Menua hasieratzeko funtzioari deia
    jokoahasieratu(); //Jokoaren hasierako pantailari deia
    while (!irten)
    {
        Sleep(10); //Programa lasaiago joateko, funtzioen artean denbora tarte bat itxaroten du
        ebentu = ebentuaJasoGertatuBada();

        if (osasunTotala <= 15 && behinSartu == 0) //Bizitza 15edo baxuagoa baldin bada funtzioan sartzen da
        {
            aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak3); //Aurreko aholkua kendu egiten du

            gureGauzak.idAholkuak3 = irudiaKargatu(BIZTANLEAK_HILTZEN); //Bizlanleak hiltzen irudia kargatu egiten da

            irudiaMugitu(gureGauzak.idAholkuak3, 0, 0); //Aholkuaren argazkiari posizioa jartzen zaio

            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

            osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
            ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
            hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

            pantailaBerriztu(); //Pantaila berriztu egiten da

            behinSartu = 1; //Aldagai honen bidez, funtzio honetara behin soilik sartzen da
        }
        if (osasunTotala > 15 && behinSartu == 1) //Bizitza 12 baino haundiagoa denean, aholkuak botoia textu gabe jartzen da
        {
            behinSartu = 0; //Aldagai honen bidez funtzioan bakarrik behin sartzen da

            aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

            gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK); //Aholkuak textu gabe kargatu egiten da

            irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

            pantailaBerriztu(); //Pantaila berriztu egiten da

            sartuDa = 1; //Funtzio honetan sartzen denean, sartuDa aldagaiari 1 balioa ematen dio
        }
        if (sartuDa == 0) //sartuDa aldagaia 0 baldin bada, funtzio barnean sartzen da
        {
            aurrekoAholkua = aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

            gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK); //Aholkuak textu gabe kargatu egiten da

            irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

            pantailaBerriztu();

            sartuDa = 1;
        }

        //Generadorea jartzeko ___________________________________________________________________
        diferentzia = clock() - hasiera; //Denbora tarte bat neurtzeko, diferentzia aldagaiari ordua - hasierako ordua egin behar zaio
        if (diferentzia >= 5000) //5 segunduro funtzioan sartzen da
        {
            if (errekolektoreKontadorea == 1) //ErrekolektoreKontadorea 1 baldin bada, funtzio barnean sartzen da
            {
                playSound(gureGauzak.idSounds[1]); //1. soinu efektua entzuten da

                irudiaKendu(gureGauzak.idErrekolektoreGrisa); //Irudi grisa kendu egiten da
                errekolektoreKontadorea = 0; //ErrekolketoreKontadorea-ri 0 balioa jarri behar zaio
            }

            urrea = urrea + ((biderkatzailea + biderkatzaileBerria) * 100); // Urrea aldagaia gehitzen doa, hasiera 100-etik hasiz
            hasiera = clock(); //Momentu honetako denbora hasiera aldagaian jartzen da
        }

        //Bizitza jaizten joateko__________________________________________________________________
        diferentzia2 = clock() - hasiera2; //Denbora tarte bat neurtzeko, diferentzia aldagaiari ordua - hasierako ordua egin behar zaio
        if (diferentzia2 >= 3000) //3 segunduro funtzioan sartzen da
        {
            pantailaGarbitu(); //Pantaila garbitu egiten da
            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu
            osasunTotala = osasuna(osasunTotala, -1); //Osasun totalari balio bat kentrzen dio
            osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
            ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
            hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du
            pantailaBerriztu(); //Pantaila berriztu egiten da
            hasiera2 = clock(); //Momentu honetako denbora hasiera2 aldagaian jartzen da
            if (osasunTotala == 0) //Bizitza totala 0 baldin bada, funtzioan sartzen da
            { 
                gameOver(); //Jokoa galdetzen duzuneko pantaila jartzen duen funtzioari dei egiten diuo
            }
        }

        //ERAIKINAK KODEA__________________________________________________________________________________________________________________
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            if (hobetutakoak < 5) {

                pos = saguarenPosizioa();
                if ((pos.x > 442) && (pos.x < 442 + 72) && (pos.y > 18) && (pos.y < 18 + 168)) //Etxearen prezioa agertzen da
                {
                    sartuda = 1; 
                    konpontzekoEtxeaZeinDenBegiratu(diruTotala, osasunTotala, hezkuntzaTotala, ETXEAREN_PREZIOA, Etxea1ClickKopurua);
                }
                if ((pos.x > 950) && (pos.x < 950 + 147) && (pos.y > 354) && (pos.y < 354 + 107)) //Bankuaren prezioa agertzen da
                {
                    sartuda = 2;
                    konpontzekoEtxeaZeinDenBegiratu(diruTotala, osasunTotala, hezkuntzaTotala, BANKUAREN_PREZIOA, BankuaClickKopurua);
                }
                if ((pos.x > 790) && (pos.x < 790 + 160) && (pos.y > 67) && (pos.y < 67 + 127)) //Hospitalaren prezioa agertzen da
                {
                    sartuda = 3;
                    konpontzekoEtxeaZeinDenBegiratu(diruTotala, osasunTotala, hezkuntzaTotala, HOSPITALAREN_PREZIOA, HospitaleaClickKopurua);
                }
                if ((pos.x > 550) && (pos.x < 550 + 150) && (pos.y > 238) && (pos.y < 238 + 80)) //Merkatuaren prezioa agertzen da
                {
                    sartuda = 4;
                    konpontzekoEtxeaZeinDenBegiratu(diruTotala, osasunTotala, hezkuntzaTotala, MERKATUAREN_PREZIOA, MerkatuaClickKopurua);
                }
                if ((pos.x > 750) && (pos.x < 750 + 170) && (pos.y > 234) && (pos.y < 234 + 81)) //Udaletxearen prezioa agertzen da
                {
                    sartuda = 5;
                    konpontzekoEtxeaZeinDenBegiratu(diruTotala, osasunTotala, hezkuntzaTotala, UDALETXEAREN_PREZIOA, UdaletxeaClickKopurua);
                }
            }
        }
        if (sartuda == 1)
        {
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                if ((pos.x > 22) && (pos.x < 22 + 330) && (pos.y > 559) && (pos.y < 559 + 74) && (Etxea1ClickKopurua == 0))
                {
                    pantailaGarbitu();
                    textuaGaitu();

                    minus = diruTotala - 1000;

                    if (minus >= 0)
                    {
                        playSound(gureGauzak.idSounds[2]); //2. soinu efektua entzuten da

                        irudiaKendu(gureGauzak.idEtxea1Apurtuta);

                        gureGauzak.idEtxea1Konponduta = irudiaKargatu(ETXEA1_KONPONDUTA);

                        irudiaMugitu(gureGauzak.idEtxea1Konponduta, 442, 18);

                        diruTotala = ekonomia(diruTotala, -1000);
                        osasunTotala = osasuna(osasunTotala, 30);
                        hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                        Etxea1ClickKopurua = 1;
                        hobetutakoak++;

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK); //Aholkuak textu gabe kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }
                    else {
                        playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak1); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak1 = irudiaKargatu(DIRURIK_EZ); //Aholkuak dirurik ez tectuarekin kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak1, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu();

                        pantailaBerriztu();
                    }

                    irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                    ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                    osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                    hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                    pantailaBerriztu();
                }
            }
        }
        if (sartuda == 2)
        {
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                if ((pos.x > 22) && (pos.x < 22 + 330) && (pos.y > 559) && (pos.y < 559 + 74) && (BankuaClickKopurua == 0))
                {
                    textuaGaitu();
                    pantailaGarbitu();

                    minus = diruTotala - 3000;

                    if (minus >= 0)
                    {
                        playSound(gureGauzak.idSounds[2]); //2. soinu efektua entzuten da

                        irudiaKendu(gureGauzak.idBankuaApurtuta); //Bankua apurtuta irudia kentzen du

                        gureGauzak.idBankuaKonponduta = irudiaKargatu(BANKUA_KONPONDUTA);

                        irudiaMugitu(gureGauzak.idBankuaKonponduta, 950, 354);

                        biderkatzailea = biderkatzailea + biderkatzaileBerria;
                        biderkatzaileBerria = 1.5;

                        diruTotala = ekonomia(diruTotala, -3000);
                        osasunTotala = osasuna(osasunTotala, 0);
                        hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                        jokalaria.id = JOKOA_jokalariaIrudiaSortu();
                        jokalaria.pos.x = 950; //Lapurraren hasierako X
                        jokalaria.pos.y = 429; //Lapurraren hasierako Y

                        gureGauzak.idLapurra = irudiaKargatu(LAPURRA_TESTUA);

                        irudiaMugitu(gureGauzak.idLapurra, 550, 340);

                        do {
                            Sleep(2);
                            pantailaGarbitu();
                            irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
                            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu
                            ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                            osasunBarraPantailaratu(osasunTotala); //Bizitza totala pantailaratzen du
                            hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du
                            pantailaBerriztu();
                            ebentu = ebentuaJasoGertatuBada();
                            aux = ERREALITATE_FISIKOA_mugimendua(jokalaria.pos);
                            jokalaria.pos.x = aux.x;
                            jokalaria.pos.y = aux.y;
                            
                            egoera = JOKOA_egoera(jokalaria);
                            //____________________________________________________________________________
                            if ((ebentu == TECLA_l) && (lapurra == 0))
                            {
                                lapurra = 1;
                            }
                            if ((ebentu == TECLA_a) && (lapurra == 1))
                            {
                                lapurra = 2;
                            }
                            if ((ebentu == TECLA_p) && (lapurra == 2))
                            {
                                lapurra = 3;
                            }
                            if ((ebentu == TECLA_u) && (lapurra == 3))
                            {
                                lapurra = 4;
                            }
                            if ((ebentu == TECLA_r) && (lapurra == 4))
                            {
                                egoera = GALDU; //Jokalaria harrapatu egiten du egoera aldagaiari GALDU balioa emanez
                            }
                            //LAPURRA HARRAPATZEKO BESTE MODU BAT "LAPUR" JARRIZ
                            //____________________________________________________________________________

                        } while (egoera == JOLASTEN && (aux.y != -32));
                        irudiaKendu(jokalaria.id);
                        if (aux.x != 950 && aux.y != -32)
                        {
                            diruTotala = diruTotala + 1000;
                            osasunTotala = osasunTotala + 10;
                        }

                        irudiaKendu(gureGauzak.idLapurra);

                        BankuaClickKopurua = 1;
                        hobetutakoak++;

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK);

                        irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }
                    else {
                        playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak1); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak1 = irudiaKargatu(DIRURIK_EZ); //Aholkuak dirurik ez tectuarekin kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak1, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }

                    irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                    ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                    osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                    hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                    pantailaBerriztu();
                }
            }

        }
        if (sartuda == 3)
        {
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                if ((pos.x > 22) && (pos.x < 22 + 330) && (pos.y > 559) && (pos.y < 559 + 74) && (HospitaleaClickKopurua == 0))
                {
                    textuaGaitu();
                    pantailaGarbitu();

                    minus = diruTotala - 2000;

                    if (minus >= 0)
                    {
                        if (hezkuntzaTotala >= 30)
                        {
                            playSound(gureGauzak.idSounds[2]); //2. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHospitaleaApurtuta);

                            gureGauzak.idHospitaleaKonponduta = irudiaKargatu(HOSPITALEA_KONPONDUTA);

                            irudiaMugitu(gureGauzak.idHospitaleaKonponduta, 790, 67);

                            diruTotala = ekonomia(diruTotala, -2000);
                            osasunTotala = osasuna(osasunTotala, 50);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            HospitaleaClickKopurua = 1;
                            hobetutakoak++;

                            aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

                            gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK); //Aholkuak textu gabe kargatu egiten da

                            irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                            pantailaBerriztu();
                        }
                        else
                        {         
                            playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                            aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak4); //Aurreko aholkua kendu egiten du

                            gureGauzak.idAholkuak4 = irudiaKargatu(HEZKUNTZA_MAILA_BAXUA);

                            irudiaMugitu(gureGauzak.idAholkuak4, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                            pantailaBerriztu();
                        }
                    }
                    else {
                        playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak1); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak1 = irudiaKargatu(DIRURIK_EZ); //Aholkuak dirurik ez tectuarekin kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak1, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }

                    irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                    ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                    osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                    hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                    pantailaBerriztu();
                }
            }

        }
        if (sartuda == 4)
        {
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                if ((pos.x > 22) && (pos.x < 22 + 330) && (pos.y > 559) && (pos.y < 559 + 74) && (MerkatuaClickKopurua == 0))
                {
                    textuaGaitu();
                    pantailaGarbitu();

                    minus = diruTotala - 500;

                    if (minus >= 0)
                    {
                        playSound(gureGauzak.idSounds[2]); //2. soinu efektua entzuten da

                        irudiaKendu(gureGauzak.idMerkatuaApurtuta);

                        gureGauzak.idMerkatuaKonponduta = irudiaKargatu(MERKATUA_KONPONDUTA);

                        irudiaMugitu(gureGauzak.idMerkatuaKonponduta, 550, 238);

                        biderkatzailea = biderkatzailea + biderkatzaileBerria;
                        biderkatzaileBerria = 0.25;

                        diruTotala = ekonomia(diruTotala, -500);
                        osasunTotala = osasuna(osasunTotala, 0);
                        hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                        MerkatuaClickKopurua = 1;
                        hobetutakoak++;

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak2); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak2 = irudiaKargatu(AHOLKUAK_HUTZIK); //Aholkuak textu gabe kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak2, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }
                    else
                    {
                        playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak1); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak1 = irudiaKargatu(DIRURIK_EZ); //Aholkuak dirurik ez tectuarekin kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak1, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }

                    irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                    ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                    osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                    hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                    pantailaBerriztu();
                }
            }
        }
        if (sartuda == 5)
        {
            if (ebentu == SAGU_BOTOIA_EZKERRA)
            {
                if ((pos.x > 22) && (pos.x < 22 + 330) && (pos.y > 559) && (pos.y < 559 + 74))
                {
                    textuaGaitu();
                    pantailaGarbitu();

                    minus = diruTotala - 10000;

                    if (minus >= 0)
                    {
                        if (hezkuntzaTotala >= 100)
                        {
                            playSound(gureGauzak.idSounds[2]); //2. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idUdaletxeaApurtuta);
                            win();
                        }
                        else
                        {
                            if (HezkuntzaOngi1) 
                            {
                                aurrekoAholkua = aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak4); //Aurreko aholkua kendu egiten du

                                gureGauzak.idAholkuak4 = irudiaKargatu(HEZKUNTZA_MAILA_BAXUA);

                                irudiaMugitu(gureGauzak.idAholkuak4, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                                irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                                pantailaBerriztu();
                            }
                        }
                    }
                    else 
                    {
                        playSound(gureGauzak.idSounds[0]); //0. soinu efektua entzuten da

                        aurrekoAholkua=aurrekoAholkuaKendu(aurrekoAholkua, gureGauzak.idAholkuak1); //Aurreko aholkua kendu egiten du

                        gureGauzak.idAholkuak1 = irudiaKargatu(DIRURIK_EZ); //Aholkuak dirurik ez tectuarekin kargatu egiten da

                        irudiaMugitu(gureGauzak.idAholkuak1, 0, 0); //Aholkuen argazkiari posizioa jartzen zaio

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        pantailaBerriztu();
                    }

                    irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                    ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                    osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                    hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                    pantailaBerriztu();
                }
            }
        }
        if (hobetutakoak == 5)
        {
            gureGauzak.idHobekuntzaGuztiakDituzu = irudiaKargatu(HOBEKUNTZA_GUZTIAK_DITUZU);

            irudiaMugitu(gureGauzak.idHobekuntzaGuztiakDituzu, 28, 652);

            irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

            ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
            osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
            hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

            pantailaBerriztu();

            hobetutakoak++;
        }
        //DENDA____________________________________________________________________________________________________________________________________
        if (ebentu == SAGU_BOTOIA_EZKERRA && etxeaktope == 0)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 393) && (pos.x < 393 + 323) && (pos.y > 561) && (pos.y < 561 + 73))
            {
                if (etxekop <= 7)
                {
                    switch (etxekop) {
                    case 1:
                        minus = diruTotala - 200;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            gureGauzak.idEtxea2Konponduta = irudiaKargatu(ETXEA2_KONPONDUTA);
                            gureGauzak.idHEskola = irudiaKargatu(ESKOLA_PREZIOA);

                            irudiaMugitu(gureGauzak.idEtxea2Konponduta, 510, 350);
                            irudiaMugitu(gureGauzak.idHEskola, 394, 650);

                            diruTotala = ekonomia(diruTotala, -200);
                            osasunTotala = osasuna(osasunTotala, 10);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 2:
                        minus = diruTotala - 400;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHEskola);

                            gureGauzak.idEskolaKonponduta = irudiaKargatu(ESKOLA_KONPONDUTA);
                            gureGauzak.idHEtxea = irudiaKargatu(ETXEA3_PREZIOA);

                            irudiaMugitu(gureGauzak.idEskolaKonponduta, 600, 50);
                            irudiaMugitu(gureGauzak.idHEtxea, 394, 650);

                            diruTotala = ekonomia(diruTotala, -400);
                            osasunTotala = osasuna(osasunTotala, 0);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 30);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 3:
                        minus = diruTotala - 800;
                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHEtxea);

                            gureGauzak.idEtxea3Konponduta = irudiaKargatu(ETXEA3_KONPONDUTA);
                            gureGauzak.idHKebab = irudiaKargatu(KEBAB_PREZIOA);

                            irudiaMugitu(gureGauzak.idEtxea3Konponduta, 730, 365);
                            irudiaMugitu(gureGauzak.idHKebab, 394, 650);

                            diruTotala = ekonomia(diruTotala, -800);
                            osasunTotala = osasuna(osasunTotala, 20);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 4:
                        minus = diruTotala - 1500;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHKebab);

                            gureGauzak.idKebab = irudiaKargatu(KEBAB_KONPONDUTA);
                            gureGauzak.idHUni = irudiaKargatu(UNIBERTSITATEA_PREZIOA);

                            irudiaMugitu(gureGauzak.idKebab, 320, 385);
                            irudiaMugitu(gureGauzak.idHUni, 394, 650);

                            biderkatzailea = biderkatzailea + biderkatzaileBerria;
                            biderkatzaileBerria = 0.25;

                            diruTotala = ekonomia(diruTotala, -1500);
                            osasunTotala = osasuna(osasunTotala, 0);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 5:
                        minus = diruTotala - 2700;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHUni);

                            gureGauzak.idUnibertsitateaKonponduta = irudiaKargatu(UNIBERTSITATEA_KONPONDUTA);
                            gureGauzak.idHKiroldegi = irudiaKargatu(KIROLDEGIA_PREZIOA);

                            irudiaMugitu(gureGauzak.idUnibertsitateaKonponduta, 355, 238);
                            irudiaMugitu(gureGauzak.idHKiroldegi, 394, 650);

                            diruTotala = ekonomia(diruTotala, -2700);
                            osasunTotala = osasuna(osasunTotala, 0);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 70);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 6:
                        minus = diruTotala - 3300;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHKiroldegi);

                            gureGauzak.idKiroldegia = irudiaKargatu(KIROLDEGIA_KONPONDUTA);
                            gureGauzak.idHZentral = irudiaKargatu(ZENTRAL_ELEKTRIKOA_PREZIOA);

                            irudiaMugitu(gureGauzak.idKiroldegia, 1000, 212);
                            irudiaMugitu(gureGauzak.idHZentral, 394, 650);

                            diruTotala = ekonomia(diruTotala, -3300);
                            osasunTotala = osasuna(osasunTotala, 30);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu();
                        break;
                    case 7:
                        minus = diruTotala - 4500;

                        if (minus >= 0)
                        {
                            playSound(gureGauzak.idSounds[3]); //3. soinu efektua entzuten da

                            irudiaKendu(gureGauzak.idHZentral);

                            gureGauzak.idZentrala = irudiaKargatu(ZENTRAL_ELEKTRIKOA_KONPONDUTA);
                            gureGauzak.idGuztiakdauzkazu = irudiaKargatu(ERAIKIN_GUZTIAK_DITUZU);

                            irudiaMugitu(gureGauzak.idZentrala, 1020, 50);
                            irudiaMugitu(gureGauzak.idGuztiakdauzkazu, 394, 650);

                            biderkatzailea = biderkatzailea + biderkatzaileBerria;
                            biderkatzaileBerria = 1;

                            diruTotala = ekonomia(diruTotala, -4500);
                            osasunTotala = osasuna(osasunTotala, 50);
                            hezkuntzaTotala = hezkuntza(hezkuntzaTotala, 0);

                            etxekop++;
                        }

                        irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                        ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen du
                        osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                        hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                        pantailaBerriztu(); //Pantaila berriztu egiten da
                        break;
                    }
                }
                else
                {
                    etxeaktope = 1;
                }
            }
        }
        //Errekolektorea
        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();
            if ((pos.x > 1000) && (pos.x < 1000 + 321) && (pos.y > 580) && (pos.y < 580 + 95))
            {
                textuaGaitu(); //Textua gaitu egiten da
                pantailaGarbitu();

                if (errekolektoreKontadorea == 0)
                {
                    gureGauzak.idErrekolektoreGrisa = irudiaKargatu(ERREKOLEKTOREA);
                    irudiaMugitu(gureGauzak.idErrekolektoreGrisa, 997, 579);
                }


                irudiakMarraztu(); //Aurretik kargatutako irudiak marrazten ditu

                diruTotala = generadorea(diruTotala, urrea);
                ekonomiaBarraPantailaratu(diruTotala); //Ekonomia totala pantailaratzen da
                urrea = 0;
                osasunBarraPantailaratu(osasunTotala); //Osasun totala pantailaratzen du
                hezkuntzaBarraPantailaratu(hezkuntzaTotala); //Hezkuntza totala pantailaratzen du

                errekolektoreKontadorea = 1;

                pantailaBerriztu(); //Pantaila berriztu egiten da
            }
        }
        //____________________________________________________________________________
        if ((ebentu == TECLA_l) && (sorpresa == 0)) //L tekla sakatzean, sorpresa aldagaia 0 bardin bada if barrura sartzen da
        {
            sorpresa = 1; //Sorpresa aldagaia = 1 egiten du
        }
        if ((ebentu == TECLA_u) && (sorpresa == 1)) //U tekla sakatzean, sorpresa aldagaia 1 bardin bada if barrura sartzen da
        {
            sorpresa = 2; //Sorpresa aldagaia = 2 egiten du
        }
        if ((ebentu == TECLA_d) && (sorpresa == 2)) //D tekla sakatzean, sorpresa aldagaia 2 bardin bada if barrura sartzen da
        {
            sorpresa = 3; //Sorpresa aldagaia = 3 egiten du
        }
        if ((ebentu == TECLA_o) && (sorpresa == 3)) //O tekla sakatzean, sorpresa aldagaia 3 bardin bada if barrura sartzen da
        {
            sorpresa = 4; //Sorpresa aldagaia = 4 egiten du
        }
        if ((ebentu == TECLA_k) && (sorpresa == 4)) //K tekla sakatzean, sorpresa aldagaia 4 bardin bada if barrura sartzen da
        {
            diruTotala = 29900; //Diru totala-ri 29900-ko balioa ematen dio
        }
        //____________________________________________________________________________

        if (ebentu == TECLA_ESCAPE) irten = 1; //ESCAPE botoia sakatuz gero, while-tik irtetzen da

        else if (ebentu == TECLA_RETURN) toggleMusic(); //ESPACIO botoia sakatuz gero, musika pausatu egiten da
    }
    audioTerminate(); //Musika bukatu egiten da
    sgItxi(); //Main-a itxi egiten da
    return 0;
}