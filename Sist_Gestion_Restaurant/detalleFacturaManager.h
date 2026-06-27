#pragma once

#include "detalleFactura.h"
#include "archivoDetalleFactura.h"
#include "archivoPlato.h"

class DetalleFacturaManager{
private:
    ArchivoDetalleFactura _archivo;
    ArchivoPlato _archivoPlato;

    int generarID(int desplazamiento = 0);
    bool platoActivo(int idPlato, Plato &plato);

public:
    bool cargarDetallesFactura(int idFactura, DetalleFactura *&detalles, int &cantidadDetalles, float &importeTotal);
    bool guardarDetalles(DetalleFactura *detalles, int cantidadDetalles);
    void listarPorFactura(int idFactura);
    void listarTodos();
    void anularDetallesFactura(int idFactura);
};
