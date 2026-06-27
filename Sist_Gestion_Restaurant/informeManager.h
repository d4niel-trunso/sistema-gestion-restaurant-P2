#pragma once

#include "menu.h"
#include "facturaArchivo.h"
#include "archivoDetalleFactura.h"
#include "archivoPlato.h"
#include "archivoMozo.h"

class InformeManager : public Menu{
private:
    FacturaArchivo _archivoFactura;
    ArchivoDetalleFactura _archivoDetalle;
    ArchivoPlato _archivoPlato;
    ArchivoMozo _archivoMozo;

    bool facturaActiva(int idFactura);
    bool obtenerNombrePlato(int idPlato, char nombre[50]);

public:
    InformeManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    void menuInformes();
    void recaudacionPorDia();
    void recaudacionPorPeriodo();
    void platosMasVendidos();
    void platoMenosVendido();
    void mesasAtendidasPorMozo();
};
