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
    bool guardar(Mozo obj, int pos);
    Mozo leer(int pos);
    int buscar(int id);
};
