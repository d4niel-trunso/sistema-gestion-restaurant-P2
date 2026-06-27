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
    bool guardar(Cliente obj, int pos);
    Cliente leer(int pos);
    int buscar(int id);
};
