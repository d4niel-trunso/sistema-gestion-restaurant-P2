#pragma once

class Menu{
private:
    int _cantidadOpciones;

protected:
    void setCantidadOpciones(int cantidad);
    int getCantidadOpciones();

public:
    Menu();
    void iniciar();
    virtual void mostrarOpciones() = 0;
    int seleccionarOpcion();
    virtual void ejecutarOpcion(int opcion) = 0;
};
