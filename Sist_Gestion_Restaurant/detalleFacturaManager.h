#pragma once

#include <vector>
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
    bool cargarDetallesFactura(int idFactura, std::vector<DetalleFactura> &detalles, float &importeTotal);
    bool guardarDetalles(std::vector<DetalleFactura> detalles);
    void listarPorFactura(int idFactura);
    void listarTodos();
    void anularDetallesFactura(int idFactura);
};
