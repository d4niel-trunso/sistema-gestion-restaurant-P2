#pragma once

#include "menu.h"
#include "mozo.h"

class MozoManager : public Menu {

public:
    MozoManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

    void altaMozo();
    void modificarMozo();
    void bajaMozo();

    void listarPorApellido();
    void listarPorTurno();

    void consultarPorDni();
    void consultaPorTurno();

};
