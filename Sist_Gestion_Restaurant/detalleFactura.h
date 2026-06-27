#pragma once

class DetalleFactura
{
private:
    int _idDetalle;
    int _idFactura;
    int _idPlato;
    int _cantidad;
    float _precioUnitario;
    bool _estado;

public:

    DetalleFactura();

    /// SETTERS
    void setIdDetalle(int id);
    void setIdFactura(int id);
    void setIdPlato(int id);
    void setCantidad(int cantidad);
    void setPrecioUnitario(float precio);
    void setEstado(bool estado);

    /// GETTERS
    int getIdDetalle();
    int getIdFactura();
    int getIdPlato();
    int getCantidad();
    float getPrecioUnitario();
    bool getEstado();


    ///
    void cargar();
    void mostrar();
};

