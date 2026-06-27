#pragma once

#include "menu.h"

class PlatoManager : public Menu{
public:
    PlatoManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);

    void altaPlato();
    void modificarPlato();
    void bajaPlato();

    void listadoPorNombre();
    void listadoPorCategoria();
    void listadoPorPrecio();

    void consultaPorCategoria();
    void consultaPorRangoDePrecios();
};
