#include "imagen.h"
#include "graphics.h"
#include "text.h"
#include "OurTypes.h"
#include "irudi_guztiak.h"

void gameOver()
{
    pantailaGarbitu();
    textuaDesgaitu();
    gureGauzak.idGameOver = irudiaKargatu(GAME_OVER);
    irudiaMugitu(gureGauzak.idGameOver, 0, 0);
    pantailaBerriztu();
}
void win()
{
    pantailaGarbitu();
    textuaDesgaitu();
    gureGauzak.idIrabazi = irudiaKargatu(IRABAZI_PANTAILA);
    irudiaMugitu(gureGauzak.idIrabazi, 0, 0);
    pantailaBerriztu();
}