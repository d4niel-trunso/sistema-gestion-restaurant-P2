# Plan por fases para completar la funcionalidad faltante

Este plan surge de revisar `AGENTS.md`, `INFORME DE PROYECTO.md` y el estado actual del codigo en `Sist_Gestion_Restaurant/`.

El proyecto compila actualmente con:

```powershell
& 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe' -Wall -fexceptions .\Sist_Gestion_Restaurant\*.cpp -o .\Sist_Gestion_Restaurant\bin\Debug\Sist_Gestion_Restaurant_codex_check.exe
```

La implementacion debe mantener el coding style existente: C++ simple, clases con atributos privados, getters/setters, metodos `cargar()` y `mostrar()`, managers para menus/listados/consultas/informes y archivos de persistencia binaria usando `FILE*`, `fopen`, `fread`, `fwrite`, `fseek`, `ftell` y `fclose`. Evitar refactors grandes si no son necesarios para completar la funcionalidad.

## Estado relevado

- `MenuManager` todavia muestra "En construccion..." para mozos, clientes, mesas y platos, aunque existen `MozoManager`, `ClienteManager`, `MesaManager` y `PlatoManager`.
- Reservas y facturacion estan conectadas al menu principal, pero reservas solo permite alta y listado general.
- Facturacion permite emitir y listar facturas, pero buscar y anular factura siguen "En construccion".
- `detalleFacturaManager.h/.cpp` esta sin desarrollar.
- La emision de facturas no carga detalles de consumo, por lo que no se puede calcular correctamente platos mas vendidos, plato menos vendido ni totales derivados de detalle.
- Los informes pedidos en el informe del proyecto todavia no tienen una pantalla central implementada.
- `Fecha::establecerFechaPorDefecto()` asigna `_mes = 1900` en vez de inicializar `_anio`; conviene corregirlo antes de usar comparaciones por fecha.
- Hay includes con mayusculas que no coinciden con los nombres reales de archivos, por ejemplo en `mesaManager.cpp` y `archivoDetalleFactura.h`. En Windows compila, pero conviene normalizarlos al tocar esos archivos.
- Existen datos generados y binarios (`.dat`, `bin/`, `obj/`) que no deberian versionarse salvo pedido explicito.

## Fase 1: base tecnica y consistencia minima

Objetivo: dejar una base confiable antes de agregar funcionalidad.

Tareas:

- Corregir `Fecha::establecerFechaPorDefecto()` para inicializar `_anio = 1900`.
- Revisar comparaciones de fechas necesarias para consultas e informes. Si hace falta, agregar metodos simples en `Fecha` como comparacion por dia/mes/anio o conversion a numero `AAAAMMDD`, manteniendo el estilo del proyecto.
- Normalizar includes de archivos tocados para que coincidan con los nombres reales en minuscula.
- Revisar que todos los `Archivo` tengan operaciones minimas necesarias: `guardar`, `leer`, `getCantidadRegistros`, y cuando haga falta `guardar(obj, pos)` / `buscar`.
- Mantener baja logica con `bool estado` donde corresponda, no borrado fisico.

Criterio de cierre:

- El proyecto compila con `-Wall -fexceptions`.
- No se introducen cambios masivos de estilo.
- Las clases base siguen separadas entre modelos, managers y archivos.

## Fase 2: integrar menus principales pendientes

Objetivo: que todas las entidades principales sean accesibles desde el menu principal.

Tareas:

- Agregar atributos en `MenuManager` para `MozoManager`, `ClienteManager`, `MesaManager` y `PlatoManager`.
- Reemplazar los `cout << "En construccion..."` de las opciones 1 a 4 por llamadas a menus propios.
- Crear o completar menus en cada manager si no existen, respetando la estructura de `ReservaManager::menuReserva()` y `FacturaManager::menuFacturacion()`.
- Incluir opciones de alta, listados y consultas segun el informe.
- Agregar opcion `0` para volver al menu principal en cada submenu.

Criterio de cierre:

- Desde el menu principal se puede entrar a mozos, clientes, mesas, platos, reservas y facturas.
- Cada submenu permite navegar sin cerrar la aplicacion.

## Fase 3: completar ABM basico por entidad

Objetivo: que mozos, clientes, mesas y platos puedan cargarse, consultarse y listarse de forma usable.

Tareas por entidad:

- Mozos:
  - Alta de mozo.
  - Listado por apellido.
  - Listado por turno.
  - Consulta por DNI.
  - Consulta por turno.
- Clientes:
  - Alta de cliente.
  - Listado por apellido.
  - Listado filtrado por VIP.
  - Consulta por DNI.
  - Consulta por condicion VIP.
- Mesas:
  - Alta de mesa.
  - Listado por numero de mesa.
  - Listado por ubicacion.
  - Consulta por numero de mesa.
  - Consulta por ubicacion.
- Platos:
  - Alta de plato.
  - Listado por nombre.
  - Listado por categoria.
  - Listado por precio.
  - Consulta por categoria.
  - Consulta por rango de precios.

Correcciones puntuales a revisar en esta fase:

- Validar que los ordenamientos sean ascendentes y consistentes con lo que dice el menu.
- Evitar mostrar registros con `estado == false` cuando se implemente baja logica.
- En `MesaManager`, decidir si "exterior" y "terraza" representan lo mismo y usar una sola etiqueta en pantalla.
- Evitar reservas de memoria innecesarias si el manager no usa el vector.

Criterio de cierre:

- Las salidas de listados y consultas declaradas en el informe funcionan para las cuatro entidades.
- Los registros inactivos no aparecen en listados comunes si ya se agrego baja logica.

## Fase 4: completar reservas

Objetivo: alinear reservas con las salidas declaradas en el informe.

Tareas:

- Implementar busqueda de reserva por ID.
- Implementar cancelacion de reserva con baja logica o cambio de `estadoReserva` a cancelada.
- Agregar listado ordenado por fecha.
- Agregar listado ordenado por estado: pendiente, completada, cancelada.
- Agregar consultas por fecha, por cliente y por estado de reserva.
- Validar que la mesa, el cliente y la fecha ingresada tengan sentido antes de guardar, al menos con chequeos simples.
- Evitar superponer reservas activas de la misma mesa en la misma fecha y hora, si el alcance del proyecto lo permite.

Criterio de cierre:

- Reservas cubre altas, listados, consultas, busqueda y cancelacion.
- El estado de reserva se usa de forma consistente en pantallas e informes.

## Fase 5: desarrollar detalle de factura

Objetivo: conectar facturas con platos consumidos para que la facturacion y los informes de ventas sean reales.

Tareas:

- Completar `DetalleFacturaManager` con metodos para cargar detalle, listar detalles por factura y listar todos si resulta util para pruebas.
- Agregar en `ArchivoDetalleFactura` operaciones de busqueda o guardado por posicion si se necesitan para anulaciones.
- Durante la emision de una factura, permitir cargar uno o mas detalles:
  - pedir ID de plato;
  - validar que el plato exista y este activo;
  - pedir cantidad;
  - tomar el precio unitario desde el plato;
  - calcular subtotal por detalle.
- Calcular `Factura::_importeTotal` a partir de los detalles en lugar de pedirlo manualmente.
- Guardar la factura y luego los detalles asociados, cuidando que no queden detalles huerfanos si falla el guardado de factura.
- Mantener `DetalleFactura::_estado` para permitir anulacion logica si se anula una factura.

Criterio de cierre:

- Una factura nueva queda asociada a sus detalles.
- El total de factura coincide con la suma de cantidad por precio unitario.
- Los detalles pueden leerse desde `detalles.dat`.

## Fase 6: completar facturacion

Objetivo: terminar las operaciones pendientes del menu de facturas y preparar consultas del informe.

Tareas:

- Implementar buscar factura por ID.
- Implementar anular factura:
  - buscar factura;
  - confirmar anulacion;
  - cambiar `estado` de factura a `false`;
  - opcionalmente cambiar `estado` de sus detalles a `false`;
  - guardar en la misma posicion del archivo.
- Agregar listados ordenados por fecha y por numero de mesa.
- Agregar consultas por rango de fechas, numero de mesa y mozo.
- Revisar que los listados comunes no sumen ni muestren facturas anuladas salvo que se indique explicitamente.
- Si se mantiene `montoAbonado`, validar que sea mayor o igual al total o mostrar vuelto/saldo de forma clara.

Criterio de cierre:

- Facturas cubre emision, listado, busqueda, anulacion y consultas declaradas en el informe.
- Las facturas anuladas no afectan la recaudacion ni rankings de platos.

## Fase 7: implementar informes

Objetivo: completar los informes pedidos por `INFORME DE PROYECTO.md`.

Tareas:

- Crear una pantalla de informes, preferentemente conectada desde el menu principal o desde facturacion, segun se decida para la navegacion.
- Implementar recaudacion por dia:
  - pedir fecha;
  - sumar `importeTotal` de facturas activas de esa fecha.
- Implementar recaudacion por periodo:
  - pedir fecha desde y fecha hasta;
  - sumar facturas activas dentro del rango.
- Implementar platos mas vendidos:
  - recorrer detalles activos;
  - acumular cantidad por `idPlato`;
  - mostrar plato(s) con mayor cantidad vendida.
- Implementar plato menos vendido:
  - usar la misma acumulacion;
  - definir si se consideran platos con cero ventas o solo platos vendidos al menos una vez;
  - dejar esa decision clara en el texto del menu o informe.
- Implementar cantidad de mesas atendidas por mozo:
  - pedir ID de mozo o permitir listar todos;
  - recorrer facturas activas;
  - contar mesas atendidas por mozo, idealmente evitando duplicados por factura si corresponde.

Criterio de cierre:

- Los cinco informes del documento funcionan con datos reales de `Facturas.dat`, `detalles.dat` y `platos.dat`.
- Los informes ignoran facturas/detalles anulados.

## Fase 8: validacion funcional y datos de prueba

Objetivo: asegurar que la aplicacion se puede demostrar de punta a punta.

Tareas:

- Preparar una secuencia manual de prueba:
  - cargar mozos;
  - cargar clientes;
  - cargar mesas;
  - cargar platos;
  - crear reservas;
  - emitir facturas con detalles;
  - anular una factura;
  - ejecutar listados, consultas e informes.
- Probar casos sin datos para que cada pantalla muestre mensajes claros en vez de fallar.
- Probar IDs inexistentes en consultas y anulaciones.
- Probar rangos de fecha y rango de precios.
- Compilar desde consola con el comando documentado en `AGENTS.md`.
- Evitar commitear `.dat`, `.exe`, `.o` y otros binarios generados.

Criterio de cierre:

- El sistema compila y permite una demo completa alineada con el informe.
- Las salidas principales son entendibles para una presentacion academica.

## Orden recomendado de implementacion

1. Corregir base tecnica minima: `Fecha`, includes tocados y helpers de archivos.
2. Integrar menus de mozos, clientes, mesas y platos.
3. Completar y probar ABM/listados/consultas simples.
4. Completar reservas.
5. Implementar detalle de factura.
6. Completar facturacion.
7. Implementar informes.
8. Ejecutar validacion manual integral y compilacion final.

## Notas de estilo para todo el desarrollo

- Mantener el estilo C++ actual del proyecto.
- No reemplazar la persistencia binaria por streams, bases de datos u otro mecanismo salvo que se acuerde una refactorizacion general.
- No introducir frameworks ni dependencias externas.
- Preferir cambios chicos, compilables y verificables por fase.
- Al tocar un archivo con includes en mayusculas, normalizarlos al nombre real del archivo.
- Mantener `INFORME DE PROYECTO.md` como fuente del alcance funcional. Si se cambia el alcance, actualizar tambien el informe o dejar explicitado que la salida queda planificada.
