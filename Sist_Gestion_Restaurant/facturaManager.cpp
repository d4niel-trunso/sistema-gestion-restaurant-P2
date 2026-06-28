#include <iostream>
#include <cstdlib>
#include "facturaManager.h"
#include "rlutil.h"
#include "utilidades.h"

using namespace std;

FacturaManager::FacturaManager()
{
    setCantidadOpciones(9);
}

void FacturaManager::mostrarOpciones(){
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    rlutil::cls();

    cout << "-------- MENU DE FACTURACION --------" << endl;
    cout << "                                     " << endl;
    cout << "1. EMITIR NUEVA FACTURA              " << endl;
    cout << "2. LISTAR TODAS LAS FACTURAS         " << endl;
    cout << "3. BUSCAR FACTURA POR ID             " << endl;
    cout << "4. ANULAR FACTURA                    " << endl;
    cout << "5. LISTADO POR FECHA                 " << endl;
    cout << "6. LISTADO POR NUMERO DE MESA        " << endl;
    cout << "7. CONSULTA POR RANGO DE FECHAS      " << endl;
    cout << "8. CONSULTA POR NUMERO DE MESA       " << endl;
    cout << "9. CONSULTA POR MOZO                 " << endl;
    cout << "                                     " << endl;
    cout << "0. VOLVER AL MENU PRINCIPAL          " << endl;
    cout << "                                     " << endl;
    cout << "-------------------------------------" << endl;
}

void FacturaManager::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:
            cout << "=== EMISION DE FACTURA ===" << endl;
            emitirFactura();
            break;
        case 2:
            cout << "=== LISTADO DE FACTURAS ===" << endl;
            listarFacturas();
            break;
        case 3:
            buscarFacturaPorID();
            break;
        case 4:
            anularFactura();
            break;
        case 5:
            listarPorFecha();
            break;
        case 6:
            listarPorMesa();
            break;
        case 7:
            consultarPorRangoFechas();
            break;
        case 8:
            consultarPorMesa();
            break;
        case 9:
            consultarPorMozo();
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
    }
}

void FacturaManager::menuFacturacion(){
    iniciar();
}

void FacturaManager::listarFacturas(){
    int cantidad = _archivo.getCantidadRegistros();
    bool encontro = false;

    if (cantidad == 0) {
        cout << "No hay facturas registradas en el sistema." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++)
    {
        Factura reg = _archivo.leer(i);
        if(reg.getEstado()){
            mostrarFacturaConDetalles(reg);
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay facturas activas para mostrar." << endl;
    }
}

int FacturaManager::generarID()
{
    return _archivo.getCantidadRegistros() + 1;
}

void FacturaManager::emitirFactura(){
    int idFactura;
    int numeroMesa;
    int idMozo;
    int formaPago;
    float importeTotal;
    float montoAbonado;
    bool estado;
    DetalleFactura *detalles = nullptr;
    int cantidadDetalles = 0;

    cout << "Ingrese factura:" << endl;

    idFactura = generarID();

    cout << "ID Factura: " << idFactura << endl;

    numeroMesa = leerEntero("Numero Mesa: ");

    if(!mesaActiva(numeroMesa)){
        cout << "No existe una mesa activa con ese numero." << endl;
        return;
    }

    idMozo = leerEntero("ID Mozo: ");

    if(!mozoActivo(idMozo)){
        cout << "No existe un mozo activo con ese ID." << endl;
        return;
    }

    Fecha f = leerFecha("Fecha de la Factura");

    formaPago = leerEnteroEnRango("Forma de Pago (1-Efectivo, 2-Tarjeta, 3-App): ", 1, 3);

    cout << "Ingrese los detalles de consumo:" << endl;

    if(!_detalleManager.cargarDetallesFactura(idFactura, detalles, cantidadDetalles, importeTotal)){
        cout << "No se puede guardar una factura sin detalles." << endl;
        delete[] detalles;
        return;
    }

    cout << "Importe total calculado: $" << importeTotal << endl;
    montoAbonado = leerFloatMinimo("Monto abonado: $", 0);

    if(montoAbonado < importeTotal){
        cout << "El monto abonado no puede ser menor al importe total." << endl;
        delete[] detalles;
        return;
    }

    estado = true;

    Factura factura(idFactura, numeroMesa, idMozo, f, formaPago, importeTotal, montoAbonado, estado);

    if(_archivo.guardar(factura)){
        if(_detalleManager.guardarDetalles(detalles, cantidadDetalles)){
            cout << "Factura generada y guardada exitosamente!" << endl;
        }else{
            cout << "La factura fue guardada, pero ocurrio un error al guardar sus detalles." << endl;
        }
    }else{
        cout << "Error al intentar acceder al archivo facturas.dat." << endl;
    }

    delete[] detalles;
}

void FacturaManager::buscarFacturaPorID(){
    int idFactura;

    idFactura = leerEntero("ID Factura: ");

    int pos = _archivo.buscarPosicion(idFactura);

    if(pos < 0){
        cout << "No se encontro una factura con ese ID." << endl;
        return;
    }

    Factura factura = _archivo.leer(pos);

    if(!factura.getEstado()){
        cout << "La factura esta anulada." << endl;
        return;
    }

    mostrarFacturaConDetalles(factura);
}

void FacturaManager::anularFactura(){
    int idFactura;
    int confirmar;

    idFactura = leerEntero("ID Factura a anular: ");

    int pos = _archivo.buscarPosicion(idFactura);

    if(pos < 0){
        cout << "No se encontro una factura con ese ID." << endl;
        return;
    }

    Factura factura = _archivo.leer(pos);

    if(!factura.getEstado()){
        cout << "La factura ya estaba anulada." << endl;
        return;
    }

    mostrarFacturaConDetalles(factura);

    confirmar = leerEnteroEnRango("Confirma anulacion? (1-SI / 0-NO): ", 0, 1);

    if(confirmar != 1){
        cout << "Anulacion cancelada." << endl;
        return;
    }

    factura.setEstado(false);

    if(_archivo.guardar(factura, pos)){
        _detalleManager.anularDetallesFactura(idFactura);
        cout << "Factura anulada correctamente." << endl;
    }else{
        cout << "No se pudo actualizar la factura." << endl;
    }
}

void FacturaManager::listarPorFecha(){
    int cantidad = _archivo.getCantidadRegistros();
    int cantidadFacturas = 0;
    Factura *facturas = new Factura[cantidad];

    for(int i = 0; i < cantidad; i++){
        Factura factura = _archivo.leer(i);
        if(factura.getEstado()){
            facturas[cantidadFacturas] = factura;
            cantidadFacturas++;
        }
    }

    ordenarFacturasPorFecha(facturas, cantidadFacturas);

    if(cantidadFacturas == 0){
        cout << "No hay facturas activas para mostrar." << endl;
        delete[] facturas;
        return;
    }

    for(int i = 0; i < cantidadFacturas; i++){
        mostrarFacturaConDetalles(facturas[i]);
    }

    delete[] facturas;
}

void FacturaManager::listarPorMesa(){
    int cantidad = _archivo.getCantidadRegistros();
    int cantidadFacturas = 0;
    Factura *facturas = new Factura[cantidad];

    for(int i = 0; i < cantidad; i++){
        Factura factura = _archivo.leer(i);
        if(factura.getEstado()){
            facturas[cantidadFacturas] = factura;
            cantidadFacturas++;
        }
    }

    ordenarFacturasPorMesa(facturas, cantidadFacturas);

    if(cantidadFacturas == 0){
        cout << "No hay facturas activas para mostrar." << endl;
        delete[] facturas;
        return;
    }

    for(int i = 0; i < cantidadFacturas; i++){
        mostrarFacturaConDetalles(facturas[i]);
    }

    delete[] facturas;
}

void FacturaManager::consultarPorRangoFechas(){
    bool encontro = false;

    Fecha desde = leerFecha("Fecha desde");
    Fecha hasta = leerFecha("Fecha hasta");

    if(desde.toNumero() > hasta.toNumero()){
        cout << "El rango de fechas es invalido." << endl;
        return;
    }

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Factura factura = _archivo.leer(i);
        int fecha = factura.getFechaFactura().toNumero();
        if(factura.getEstado() && fecha >= desde.toNumero() && fecha <= hasta.toNumero()){
            mostrarFacturaConDetalles(factura);
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay facturas activas en ese rango." << endl;
    }
}

void FacturaManager::consultarPorMesa(){
    int numeroMesa;
    bool encontro = false;

    numeroMesa = leerEntero("Numero de mesa: ");

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Factura factura = _archivo.leer(i);
        if(factura.getEstado() && factura.getNumeroMesa() == numeroMesa){
            mostrarFacturaConDetalles(factura);
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay facturas activas para esa mesa." << endl;
    }
}

void FacturaManager::consultarPorMozo(){
    int idMozo;
    bool encontro = false;

    idMozo = leerEntero("ID Mozo: ");

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Factura factura = _archivo.leer(i);
        if(factura.getEstado() && factura.getIdMozo() == idMozo){
            mostrarFacturaConDetalles(factura);
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay facturas activas para ese mozo." << endl;
    }
}

bool FacturaManager::mesaActiva(int numeroMesa){
    int pos = _archivoMesa.buscar(numeroMesa);

    if(pos < 0){
        return false;
    }

    Mesa mesa = _archivoMesa.leer(pos);
    return mesa.getEstado();
}

bool FacturaManager::mozoActivo(int idMozo){
    int pos = _archivoMozo.buscar(idMozo);

    if(pos < 0){
        return false;
    }

    Mozo mozo = _archivoMozo.leer(pos);
    return mozo.getEstado();
}

void FacturaManager::mostrarFacturaConDetalles(Factura factura){
    factura.mostrar();

    int posMozo = _archivoMozo.buscar(factura.getIdMozo());
    cout << "Mozo: ";
    if(posMozo >= 0){
        Mozo mozo = _archivoMozo.leer(posMozo);
        cout << mozo.getApellido() << ", " << mozo.getNombre()
             << " (ID " << factura.getIdMozo() << ")";
    }else{
        cout << "No encontrado (ID " << factura.getIdMozo() << ")";
    }
    cout << endl;

    int posMesa = _archivoMesa.buscar(factura.getNumeroMesa());
    cout << "Mesa: " << factura.getNumeroMesa();
    if(posMesa >= 0){
        Mesa mesa = _archivoMesa.leer(posMesa);
        cout << " - " << mesa.getDescripcion() << " - ";
        switch(mesa.getUbicacion()){
            case 1: cout << "Interior"; break;
            case 2: cout << "Terraza"; break;
            default: cout << "Ubicacion desconocida"; break;
        }
    }
    cout << endl;

    cout << "Detalle de consumo:" << endl;
    _detalleManager.listarPorFactura(factura.getIdFactura());
}
