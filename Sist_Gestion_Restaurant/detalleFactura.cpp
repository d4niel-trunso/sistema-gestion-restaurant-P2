#include <iostream>
#include <cstring>
using namespace std;
#include "detalleFactura.h"
#include "inputUtils.h"


DetalleFactura :: DetalleFactura()
{
    _idDetalle = 0;
    _idFactura = 0;
    _idPlato = 0;
    _cantidad = 0;
    _precioUnitario = 0;
    _estado = false;
}
/// SETTERS
void DetalleFactura ::  setIdDetalle(int id)
{
    _idDetalle = id;
}
void DetalleFactura ::  setIdFactura(int id)
{
    _idFactura = id;
}
void DetalleFactura ::  setIdPlato(int id)
{
    _idPlato = id;
}
void DetalleFactura ::  setCantidad(int cantidad)
{
    _cantidad = cantidad;
}
void DetalleFactura ::  setPrecioUnitario(float precio)
{
    _precioUnitario = precio;
}
void DetalleFactura ::  setEstado(bool estado)
{
    _estado = estado;
}

/// GETTERS
int DetalleFactura ::  getIdDetalle()
{
    return _idDetalle;
}
int DetalleFactura ::  getIdFactura()
{
    return _idFactura;
}
int DetalleFactura ::  getIdPlato()
{
    return _idPlato;
}
int DetalleFactura ::  getCantidad()
{
    return _cantidad;
}
float DetalleFactura ::  getPrecioUnitario()
{
    return _precioUnitario;
}
bool DetalleFactura ::  getEstado()
{
    return _estado;
}



///
void DetalleFactura ::  cargar()
{

    int idPlato;
    int cantidad;

    cout << "INGRESAR LA INFORMACION CORRESPONDIENTE.." << endl;
    idPlato = leerEntero("ID PLATO : ");
    cantidad = leerEnteroEnRango("CANTIDAD : ", 1, 1000);


    setIdPlato(idPlato);
    setCantidad(cantidad);
    setEstado(true);

}
void DetalleFactura ::  mostrar()
{

    cout << "-----------------------------------------" << endl;
    cout << "MOSTRANDO DETALLE DE FACTURA.." << endl;
    cout << "ID DETALLE: " << _idDetalle << endl;
    cout << "ID FACTURA: " << _idFactura << endl;
    cout << "ID PLATO: " << _idPlato << endl;
    cout << "CANTIDAD: " << _cantidad << endl;
    cout << "PRECIO UNITARIO: " << _precioUnitario << endl;
    cout << "SUBTOTAL: " << (_cantidad * _precioUnitario) << endl;
}
