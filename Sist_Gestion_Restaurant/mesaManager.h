#pragma once

#include "menu.h"

class MesaManager : public Menu{
public:
    MesaManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

    void altaMesa();
    void modificarMesa();
    void bajaMesa();

    void listadoPorNumeroMesa();
    void listadoPorUbicacion();

    void consultaPorNumeroMesa();
    void consultaPorUbicacion();

};
