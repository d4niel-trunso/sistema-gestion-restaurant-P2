#pragma once

#include "menu.h"
#include "facturaArchivo.h"
#include "detalleFacturaManager.h"
#include "archivoMesa.h"
#include "archivoMozo.h"

class FacturaManager : public Menu{
private:
    FacturaArchivo _archivo;
    DetalleFacturaManager _detalleManager;
    ArchivoMesa _archivoMesa;
    ArchivoMozo _archivoMozo;
    int generarID();
    bool mesaActiva(int numeroMesa);
    bool mozoActivo(int idMozo);
    void mostrarFacturaConDetalles(Factura factura);

public:
    FacturaManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    void menuFacturacion();
    void emitirFactura();
    void listarFacturas();
    void buscarFacturaPorID();
    void anularFactura();
    void listarPorFecha();
    void listarPorMesa();
    void consultarPorRangoFechas();
    void consultarPorMesa();
    void consultarPorMozo();
};
