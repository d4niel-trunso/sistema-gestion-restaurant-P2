#include <iostream>
#include "detalleFacturaManager.h"

using namespace std;

int DetalleFacturaManager::generarID(int desplazamiento){
    return _archivo.getCantidadRegistros() + 1 + desplazamiento;
}

bool DetalleFacturaManager::platoActivo(int idPlato, Plato &plato){
    int pos = _archivoPlato.buscar(idPlato);

    if(pos < 0){
        return false;
    }

    plato = _archivoPlato.leer(pos);
    return plato.getEstado();
}

bool DetalleFacturaManager::cargarDetallesFactura(int idFactura, vector<DetalleFactura> &detalles, float &importeTotal){
    int continuar = 1;
    int idPlato;
    int cantidad;
    Plato plato;

    detalles.clear();
    importeTotal = 0;

    while(continuar == 1){
        cout << "ID Plato: ";
        cin >> idPlato;

        if(!platoActivo(idPlato, plato)){
            cout << "No existe un plato activo con ese ID." << endl;
        }else{
            cout << "Cantidad: ";
            cin >> cantidad;

            if(cantidad <= 0){
                cout << "La cantidad debe ser mayor a 0." << endl;
            }else{
                DetalleFactura detalle;
                detalle.setIdDetalle(generarID(detalles.size()));
                detalle.setIdFactura(idFactura);
                detalle.setIdPlato(idPlato);
                detalle.setCantidad(cantidad);
                detalle.setPrecioUnitario(plato.getPrecio());
                detalle.setEstado(true);

                detalles.push_back(detalle);
                importeTotal += cantidad * plato.getPrecio();

                cout << "Detalle agregado. Subtotal: $" << cantidad * plato.getPrecio() << endl;
            }
        }

        cout << "Agregar otro plato? (1-SI / 0-NO): ";
        cin >> continuar;
    }

    return detalles.size() > 0;
}

bool DetalleFacturaManager::guardarDetalles(vector<DetalleFactura> detalles){
    for(int i = 0; i < (int)detalles.size(); i++){
        if(!_archivo.guardar(detalles[i])){
            return false;
        }
    }

    return true;
}

void DetalleFacturaManager::listarPorFactura(int idFactura){
    int cantidad = _archivo.getCantidadRegistros();
    bool encontro = false;

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado() && detalle.getIdFactura() == idFactura){
            detalle.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay detalles activos para esa factura." << endl;
    }
}

void DetalleFacturaManager::listarTodos(){
    int cantidad = _archivo.getCantidadRegistros();

    if(cantidad == 0){
        cout << "No hay detalles registrados." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado()){
            detalle.mostrar();
        }
    }
}

void DetalleFacturaManager::anularDetallesFactura(int idFactura){
    int cantidad = _archivo.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado() && detalle.getIdFactura() == idFactura){
            detalle.setEstado(false);
            _archivo.guardar(detalle, i);
        }
    }
}
