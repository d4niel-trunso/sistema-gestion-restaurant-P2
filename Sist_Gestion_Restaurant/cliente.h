#pragma once

#include "persona.h"

class Cliente : public Persona{
private:

    int _idCliente;
    bool _esVip;

public:

    cliente();

    ///SETTERS
    void setIdCliente(int idCliente);
    bool setEsVip(bool esVip);

    /// GETTERS
    int getIdCliente();
    bool getEsVip();
    ///


    void mostrar();

};
