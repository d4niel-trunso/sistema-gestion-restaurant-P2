#pragma once

#include "mesa.h"

class ArchivoMesa
{
private:
    char _nombreArchivo[30];

public:

    ArchivoMesa();
    int getCantidadRegistros();
    bool guardar(Mesa obj);
    Mesa leer(int pos);

};
