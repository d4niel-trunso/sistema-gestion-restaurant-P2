#pragma once

class Mesa
{
private:
    int _numeroMesa;
    char _descripcion[50];
    int _cantidadSillas;
    int _ubicacion;
    bool _estado;
public:

    Mesa();

    /// SETTERS
    void setNumeroMesa(int numero);
    void setDescripcion(char* descripcion);
    void setCantidadSillas(int cantidad);
    void setUbicacion(int ubicacion);
    void setEstado(bool estado);

    /// GETTERS
    int getNumeroMesa();
    char* getDescripcion();
    int getCantidadSillas();
    int getUbicacion();
    bool getEstado();

    ///
    void cargar();
    void mostrar();

};
