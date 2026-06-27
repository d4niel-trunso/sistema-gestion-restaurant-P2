#pragma once

#include "fecha.h"

class Factura{
private:
    int _idFactura;
    int _numeroMesa;
    int _idMozo;
    Fecha _fechaFactura;
    int _formaPago;
    float _importeTotal;
    float _montoAbonado;
    bool _estado;

public:
    Factura();
    Factura(int idFactura, int numeroMesa, int idMozo, Fecha fechaFactura, int formaPago,
            float importeTotal, float montoAbonado, bool estado);

    ///Getters
    int getIdFactura();
    int getNumeroMesa();
    int getIdMozo();
    Fecha getFechaFactura();
    int getFormaPago();
    float getImporteTotal();
    float getMontoAbonado();
    bool getEstado();

    ///Setters
    void setIdFactura(int idFactura);
    void setNumeroMesa(int numeroMesa);
    void setIdMozo(int IdMozo);
    void setFechaFactura(Fecha fechaFactura);
    void setFormaPago(int formaPago);
    void setImporteTotal(float importeTotal);
    void setMontoAbonado(float montoAbonado);
    void setEstado(bool estado);

    ///
    void mostrar();
};
