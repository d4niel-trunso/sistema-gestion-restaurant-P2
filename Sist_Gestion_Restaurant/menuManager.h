#pragma once

#include "menu.h"
#include "reservaManager.h"
#include "facturaManager.h"

class MenuManager: public Menu{
public:
    MenuManager();
    void mostrarBienvenida();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

private:
    ReservaManager _reservaManager;
    FacturaManager _facturaManager;
};
