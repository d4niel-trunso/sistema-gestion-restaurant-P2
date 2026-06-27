#pragma once

#include "detalleFactura.h"

class ArchivoDetalleFactura{
private:
    char _nombreArchivo[30];
public:

    ArchivoDetalleFactura();

    int getCantidadRegistros();
    bool guardar(DetalleFactura obj);
    bool guardar(DetalleFactura obj, int pos);
    DetalleFactura leer(int pos);
    int buscar(int idDetalle);

};
