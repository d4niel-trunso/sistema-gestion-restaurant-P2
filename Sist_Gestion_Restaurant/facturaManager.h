#pragma once

#include "menu.h"
#include "facturaArchivo.h"

class FacturaManager : public Menu{
private:
    FacturaArchivo _archivo;
    int generarID();

public:
    FacturaManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    void menuFacturacion();
    void emitirFactura();
    void listarFacturas();
};
