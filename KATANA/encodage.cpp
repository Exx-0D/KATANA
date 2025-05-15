#include "encodage.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>

void encodage()
{
    // Configuration de la console en UTF-8
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);
}
