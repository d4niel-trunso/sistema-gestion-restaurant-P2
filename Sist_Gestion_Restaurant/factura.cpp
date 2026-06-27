#include <iostream>
#include "factura.h"

using namespace std;

Factura::Factura()
{
    _estado = true;
    _formaPago = 1; ///Por defecto efectivo
    _importeTotal = 0;
    _montoAbonado = 0;
}

Factura::Factura(int idFactura, int numeroMesa, int idMozo, Fecha fechaFactura, int formaPago,
            float importeTotal, float montoAbonado, bool estado){
    _idFactura = idFactura;
    _numeroMesa = numeroMesa;
    _idMozo = idMozo;
    _fechaFactura = fechaFactura;
    _formaPago = formaPago;
    _importeTotal = importeTotal;
    _montoAbonado = montoAbonado;
    _estado = estado;
}

int Factura::getIdFactura()
{
    return _idFactura;
}

int Factura::getNumeroMesa()
{
    return _numeroMesa;
}

int Factura::getIdMozo()
{
    return _idMozo;
}

Fecha Factura::getFechaFactura()
{
    return _fechaFactura;
}

float Factura::getImporteTotal()
{
    return _importeTotal;
}

float Factura::getMontoAbonado()
{
    return _montoAbonado;
}

bool Factura::getEstado()
{
    return _estado;
}

void Factura::setIdFactura(int idFactura)
{
    _idFactura = idFactura;
}

void Factura::setNumeroMesa(int numeroMesa)
{
    _numeroMesa = numeroMesa;
}

void Factura::setIdMozo(int idMozo)
{
    _idMozo = idMozo;
}

void Factura::setFechaFactura(Fecha fechaFactura)
{
    _fechaFactura = fechaFactura;
}

void Factura::setFormaPago(int formaPago)
{
    _formaPago = formaPago;
}

void Factura::setImporteTotal(float importeTotal)
{
    _importeTotal = importeTotal;
}

void Factura::setMontoAbonado(float montoAbonado)
{
    _montoAbonado = montoAbonado;
}

void Factura::setEstado(bool estado)
{
    _estado = estado;
}

void Factura::mostrar()
{
    if(_estado)
    {
        cout << "==========================================" << endl;
        cout << "Factura Nro: " << _idFactura << endl;
        cout << "Mesa Nro: " << _numeroMesa << endl;
        cout << "Mozo ID: " << _idMozo << endl;
        cout << "Fecha: " << _fechaFactura.toString() << endl;
        cout << "Forma de Pago: ";
        switch(_formaPago)
        {
        case 1:
            cout << "Efectivo" << endl;
            break;
        case 2:
            cout << "Tarjeta" << endl;
            break;
        case 3:
            cout << "Mercado Pago" << endl;
            break;
        default:
            cout << "Desconocido" << endl;
            break;

        }
        cout << "Importe Total: $" << _importeTotal << endl;
        cout << "Monto Abonado: $" << _montoAbonado << endl;
        cout << "Vuelto: $" << (_montoAbonado - _importeTotal) << endl;
        cout << "==========================================" << endl;
    }
}
