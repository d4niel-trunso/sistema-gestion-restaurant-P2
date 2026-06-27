#pragma once

#include "persona.h"

class Cliente : public Persona{
private:

    int _idCliente;
    bool _esVip;

public:

    Cliente();

    ///SETTERS
    void setIdCliente(int idCliente);
    void setEsVip(bool esVip);

    /// GETTERS
    int getIdCliente();
    bool getEsVip();
    ///


    void cargar();
    void mostrar();

};
