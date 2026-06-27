#pragma once

#include "menu.h"
#include "mozoManager.h"
#include "clienteManager.h"
#include "mesaManager.h"
#include "platoManager.h"
#include "reservaManager.h"
#include "facturaManager.h"
#include "informeManager.h"

class MenuManager: public Menu{
public:
    MenuManager();
    void mostrarBienvenida();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

private:
    MozoManager _mozoManager;
    ClienteManager _clienteManager;
    MesaManager _mesaManager;
    PlatoManager _platoManager;
    ReservaManager _reservaManager;
    FacturaManager _facturaManager;
    InformeManager _informeManager;
};
