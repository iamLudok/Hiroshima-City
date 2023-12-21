#include "graphics.h"
#include "irudi_guztiak.h"
#include "imagen.h"

int JOKOA_jokalariaIrudiaSortu()
{
    int martzianoId = -1;
    martzianoId = irudiaKargatu(JOKOA_PLAYER_IMAGE);
    irudiaMugitu(martzianoId, 950, 429);
    pantailaGarbitu();
    irudiakMarraztu();
    pantailaBerriztu();
    return martzianoId;

}