#include <iostream>
#include <cstdlib>
#include "facturaManager.h"
#include "rlutil.h"

using namespace std;

void FacturaManager::menuFacturacion(){
    int opcion;

    do{
        rlutil::setBackgroundColor(rlutil::CYAN);
        rlutil::setColor(rlutil::BLACK);
        rlutil::cls();

        cout << "-------- MENU DE FACTURACION --------" << endl;
        cout << "                                     " << endl;
        cout << "1. EMITIR NUEVA FACTURA              " << endl;
        cout << "2. LISTAR TODAS LAS FACTURAS         " << endl;
        cout << "3. BUSCAR FACTURA POR ID             " << endl;
        cout << "4. ANULAR FACTURA                    " << endl;
        cout << "                                     " << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL          " << endl;
        cout << "                                     " << endl;
        cout << "-------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::cls();

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
                cout << "En construccion: buscar factura..." << endl;
                break;
            case 4:
                cout << "En construccion: anular factura..." << endl;
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion incorrecta!!!" << endl;
                break;
        }

        if (opcion != 0){
            cout << endl;
            system("pause");
        }

    }while(opcion != 0);
}

void FacturaManager::listarFacturas(){
    int cantidad = _archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay facturas registradas en el sistema." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++)
    {
        Factura reg = _archivo.leer(i);
        reg.mostrar();
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
    int dia, mes, anio;
    int formaPago;
    float importeTotal;
    float montoAbonado;
    bool estado;

    cout << "Ingrese factura:" << endl;

    idFactura = generarID();

    cout << "ID Factura: " << idFactura << endl;

    cout << "Numero Mesa: ";
    cin >> numeroMesa;

    cout << "ID Mozo: ";
    cin >> idMozo;

    cout << "Fecha de la Factura: ";
    cin >> dia;
    cin >> mes;
    cin >> anio;

    Fecha f(dia, mes, anio);

    cout << "Forma de Pago (1-Efectivo, 2-Tarjeta, 3-App): ";
    cin >> formaPago;

    cout << "Importe total: $";
    cin >> importeTotal;

    cout << "Monto abonado: $";
    cin >> montoAbonado;

    estado = true;

    Factura factura(idFactura, numeroMesa, idMozo, f, formaPago, importeTotal, montoAbonado, estado);

    if(_archivo.guardar(factura)){
        cout << "Factura generada y guardada exitosamente!" << endl;
    }else{
        cout << "Error al intentar acceder al archivo facturas.dat." << endl;
    }
}
