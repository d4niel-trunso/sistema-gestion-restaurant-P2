#include <iostream>
#include <vector>
#include <cstring>
#include "informeManager.h"
#include "rlutil.h"

using namespace std;

struct VentaPlato{
    int idPlato;
    int cantidad;
};

InformeManager::InformeManager(){
    setCantidadOpciones(5);
}

void InformeManager::mostrarOpciones(){
    rlutil::setBackgroundColor(rlutil::MAGENTA);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE INFORMES --------" << endl;
    cout << "                                " << endl;
    cout << "1. RECAUDACION POR DIA          " << endl;
    cout << "2. RECAUDACION POR PERIODO      " << endl;
    cout << "3. PLATOS MAS VENDIDOS          " << endl;
    cout << "4. PLATO MENOS VENDIDO          " << endl;
    cout << "5. MESAS ATENDIDAS POR MOZO     " << endl;
    cout << "                                " << endl;
    cout << "0. VOLVER AL MENU PRINCIPAL     " << endl;
    cout << "                                " << endl;
    cout << "--------------------------------" << endl;
}

void InformeManager::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:
            recaudacionPorDia();
            break;
        case 2:
            recaudacionPorPeriodo();
            break;
        case 3:
            platosMasVendidos();
            break;
        case 4:
            platoMenosVendido();
            break;
        case 5:
            mesasAtendidasPorMozo();
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
    }
}

void InformeManager::menuInformes(){
    iniciar();
}

void InformeManager::recaudacionPorDia(){
    int dia, mes, anio;
    float total = 0;

    cout << "Fecha (dia mes anio): ";
    cin >> dia >> mes >> anio;

    Fecha fecha(dia, mes, anio);

    for(int i = 0; i < _archivoFactura.getCantidadRegistros(); i++){
        Factura factura = _archivoFactura.leer(i);
        if(factura.getEstado() && factura.getFechaFactura().toNumero() == fecha.toNumero()){
            total += factura.getImporteTotal();
        }
    }

    cout << "Recaudacion del dia " << fecha.toString() << ": $" << total << endl;
}

void InformeManager::recaudacionPorPeriodo(){
    int diaDesde, mesDesde, anioDesde;
    int diaHasta, mesHasta, anioHasta;
    float total = 0;

    cout << "Fecha desde (dia mes anio): ";
    cin >> diaDesde >> mesDesde >> anioDesde;

    cout << "Fecha hasta (dia mes anio): ";
    cin >> diaHasta >> mesHasta >> anioHasta;

    Fecha desde(diaDesde, mesDesde, anioDesde);
    Fecha hasta(diaHasta, mesHasta, anioHasta);

    if(desde.toNumero() > hasta.toNumero()){
        cout << "El rango de fechas es invalido." << endl;
        return;
    }

    for(int i = 0; i < _archivoFactura.getCantidadRegistros(); i++){
        Factura factura = _archivoFactura.leer(i);
        int fechaFactura = factura.getFechaFactura().toNumero();

        if(factura.getEstado() && fechaFactura >= desde.toNumero() && fechaFactura <= hasta.toNumero()){
            total += factura.getImporteTotal();
        }
    }

    cout << "Recaudacion del periodo: $" << total << endl;
}

void InformeManager::platosMasVendidos(){
    vector<VentaPlato> ventas;
    int mayor = 0;

    for(int i = 0; i < _archivoDetalle.getCantidadRegistros(); i++){
        DetalleFactura detalle = _archivoDetalle.leer(i);

        if(detalle.getEstado() && facturaActiva(detalle.getIdFactura())){
            bool encontro = false;

            for(int j = 0; j < (int)ventas.size(); j++){
                if(ventas[j].idPlato == detalle.getIdPlato()){
                    ventas[j].cantidad += detalle.getCantidad();
                    encontro = true;
                }
            }

            if(!encontro){
                VentaPlato venta;
                venta.idPlato = detalle.getIdPlato();
                venta.cantidad = detalle.getCantidad();
                ventas.push_back(venta);
            }
        }
    }

    for(int i = 0; i < (int)ventas.size(); i++){
        if(ventas[i].cantidad > mayor){
            mayor = ventas[i].cantidad;
        }
    }

    if(mayor == 0){
        cout << "No hay ventas activas para informar." << endl;
        return;
    }

    cout << "Platos mas vendidos:" << endl;
    for(int i = 0; i < (int)ventas.size(); i++){
        if(ventas[i].cantidad == mayor){
            char nombre[50];
            obtenerNombrePlato(ventas[i].idPlato, nombre);
            cout << "ID Plato: " << ventas[i].idPlato << " | Nombre: " << nombre << " | Cantidad: " << ventas[i].cantidad << endl;
        }
    }
}

void InformeManager::platoMenosVendido(){
    vector<VentaPlato> ventas;
    int menor = 0;

    for(int i = 0; i < _archivoDetalle.getCantidadRegistros(); i++){
        DetalleFactura detalle = _archivoDetalle.leer(i);

        if(detalle.getEstado() && facturaActiva(detalle.getIdFactura())){
            bool encontro = false;

            for(int j = 0; j < (int)ventas.size(); j++){
                if(ventas[j].idPlato == detalle.getIdPlato()){
                    ventas[j].cantidad += detalle.getCantidad();
                    encontro = true;
                }
            }

            if(!encontro){
                VentaPlato venta;
                venta.idPlato = detalle.getIdPlato();
                venta.cantidad = detalle.getCantidad();
                ventas.push_back(venta);
            }
        }
    }

    if(ventas.size() == 0){
        cout << "No hay ventas activas para informar." << endl;
        return;
    }

    menor = ventas[0].cantidad;
    for(int i = 1; i < (int)ventas.size(); i++){
        if(ventas[i].cantidad < menor){
            menor = ventas[i].cantidad;
        }
    }

    cout << "Plato menos vendido (solo platos vendidos al menos una vez):" << endl;
    for(int i = 0; i < (int)ventas.size(); i++){
        if(ventas[i].cantidad == menor){
            char nombre[50];
            obtenerNombrePlato(ventas[i].idPlato, nombre);
            cout << "ID Plato: " << ventas[i].idPlato << " | Nombre: " << nombre << " | Cantidad: " << ventas[i].cantidad << endl;
        }
    }
}

void InformeManager::mesasAtendidasPorMozo(){
    int idMozo;
    int cantidadMesas = 0;

    cout << "ID Mozo: ";
    cin >> idMozo;

    if(_archivoMozo.buscar(idMozo) < 0){
        cout << "No existe un mozo con ese ID." << endl;
        return;
    }

    for(int i = 0; i < _archivoFactura.getCantidadRegistros(); i++){
        Factura factura = _archivoFactura.leer(i);
        if(factura.getEstado() && factura.getIdMozo() == idMozo){
            cantidadMesas++;
        }
    }

    cout << "Cantidad de mesas atendidas por el mozo: " << cantidadMesas << endl;
}

bool InformeManager::facturaActiva(int idFactura){
    int pos = _archivoFactura.buscarPosicion(idFactura);

    if(pos < 0){
        return false;
    }

    Factura factura = _archivoFactura.leer(pos);
    return factura.getEstado();
}

bool InformeManager::obtenerNombrePlato(int idPlato, char nombre[50]){
    int pos = _archivoPlato.buscar(idPlato);

    if(pos < 0){
        strcpy(nombre, "No encontrado");
        return false;
    }

    Plato plato = _archivoPlato.leer(pos);
    strcpy(nombre, plato.getNombre());
    return true;
}
