#pragma once

#include "facturaArchivo.h"

class FacturaManager{
private:
    FacturaArchivo _archivo;
    int generarID();

public:
    void menuFacturacion();
    void emitirFactura();
    void listarFacturas();
};
