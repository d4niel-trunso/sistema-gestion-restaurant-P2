#pragma once

#include "mozo.h"
class ArchivoMozo
{
private:
    char _nombreArchivo[30];
public:

    ArchivoMozo();
    int getCantidadRegistros();
    bool guardar(Mozo obj);
    Mozo leer(int pos);
};
