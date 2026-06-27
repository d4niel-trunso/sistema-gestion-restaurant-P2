#pragma once

#include "plato.h"

class ArchivoPlato{
private:
    char _nombreArchivo[30];
public:

    ArchivoPlato();
    int getCantidadRegistros();
    bool guardar(Plato obj);
    bool guardar(Plato obj, int pos);
    Plato leer(int pos);
    int buscar(int id);

};
