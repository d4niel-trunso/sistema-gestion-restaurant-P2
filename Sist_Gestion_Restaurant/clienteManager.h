#pragma once

#include "menu.h"

class ClienteManager : public Menu{
public:
    ClienteManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

    void altaCliente();
    void modificarCliente();
    void bajaCliente();

    void listadoPorApellido();
    void listadoPorVips();

    void consultaPorDni();
    void consultaPorVip();
};
