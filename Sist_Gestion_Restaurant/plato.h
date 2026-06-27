#pragma once

class Plato{
private:
    int _idPlato;
    char _nombre[50];
    int _categoria;
    float _precio;
    bool _estado;

public:

    Plato();

    /// SETTERS
    void setIdPlato(int id);
    void setNombre(char* nombre);
    void setCategoria(int categoria);
    void setPrecio(float precio);
    void setEstado(bool estado);

    /// GETTERS
    int getIdPlato();
    char* getNombre();
    int getCategoria();
    float getPrecio();
    bool getEstado();

    ///
    void cargar();
    void mostrar();
};
