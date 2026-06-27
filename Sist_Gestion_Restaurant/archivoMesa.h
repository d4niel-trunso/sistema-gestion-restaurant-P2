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
    bool guardar(Mesa obj, int pos);
    Mesa leer(int pos);
    int buscar(int numeroMesa);

};
