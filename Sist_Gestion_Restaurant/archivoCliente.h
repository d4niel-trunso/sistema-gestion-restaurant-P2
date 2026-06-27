#pragma once

#include "cliente.h"
class ArchivoCliente
{
private:
    char _nombreArchivo[30];
public:

    ArchivoCliente();
    int getCantidadRegistros();
    bool guardar(Cliente obj);
    Cliente leer(int pos);
};
