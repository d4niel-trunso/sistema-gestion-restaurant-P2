#pragma once

#include "plato.h"

class ArchivoPlato{
private:
    char _nombreArchivo[30];
public:

    ArchivoPlato();
    int getCantidadRegistros();
    bool guardar(Plato obj);
    Plato leer(int pos);

};
