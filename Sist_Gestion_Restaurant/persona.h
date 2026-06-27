#pragma once

class Persona{
private:
    char _dni[15];
    char _nombre[30];
    char _apellido[30];
    char _telefono[20];
    bool _estado;

public:
    Persona();

    /// SETTERS
    void setDni(char* dni);
    void setNombre(char* nombre);
    void setApellido(char* apellido);
    void setTelefono(char* telefono);
    void setEstado(bool estado);

    /// GETTERS
    char* getDni();
    char* getNombre();
    char* getApellido();
    char* getTelefono();
    bool getEstado();

    ///
    void cargar();
    void mostrar();
};
