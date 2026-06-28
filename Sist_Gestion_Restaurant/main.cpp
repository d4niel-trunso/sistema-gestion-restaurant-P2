#include <iostream>
#include "menuManager.h"
#include "utilidades.h"

using namespace std;

int main()
{
    configurarConsola();

    MenuManager miMenu;

    miMenu.mostrarBienvenida();
    miMenu.iniciar();

    return 0;
}
