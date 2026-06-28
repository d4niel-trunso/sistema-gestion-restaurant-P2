# AGENTS.md

## Proyecto

Sistema de gestion de restaurante hecho en C++ para Programacion 2. La aplicacion es de consola y administra mozos, clientes, mesas, platos, reservas, facturas y detalles de factura. El proyecto principal esta en `Sist_Gestion_Restaurant/` y fue creado con Code::Blocks.

## Estructura

- `Sist_Gestion_Restaurant/Sist_Gestion_Restaurant.cbp`: proyecto Code::Blocks. Usa GCC, `-Wall` y `-fexceptions`.
- `Sist_Gestion_Restaurant/main.cpp`: punto de entrada. Instancia `MenuManager` y llama a `iniciar()`.
- `Sist_Gestion_Restaurant/menu.*` y `menuManager.*`: menu principal y navegacion.
- `Sist_Gestion_Restaurant/*Manager.*`: logica de pantallas, cargas, listados, consultas e informes.
- `Sist_Gestion_Restaurant/archivo*.{h,cpp}`, `facturaArchivo.*`, `reservaArchivo.*`: persistencia binaria en archivos `.dat`.
- `Sist_Gestion_Restaurant/*.h` y `*.cpp` con nombres de dominio: modelos del sistema (`Cliente`, `Mozo`, `Mesa`, `Plato`, `Reserva`, `Factura`, `DetalleFactura`, `Fecha`).
- `INFORME DE PROYECTO.md`: descripcion funcional del sistema y salidas esperadas.
- `assets/informe-de-proyecto-diagrama-clases.png`: diagrama de clases usado por el informe Markdown.

## Estado funcional actual

- Mozos, clientes, mesas, platos, reservas, facturas e informes estan conectados al menu principal.
- Las cargas principales usan helpers de entrada para aceptar textos con espacios y validar numeros/fechas.
- La consola se configura al iniciar para usar UTF-8 en Windows y mostrar correctamente `ñ`, acentos y signos de apertura.
- `detalleFacturaManager.*` esta desarrollado y se usa al emitir facturas para cargar platos consumidos y calcular el total.
- Facturacion permite emitir, listar, buscar, anular y consultar facturas por fecha, mesa o mozo.
- Informes implementa recaudacion por dia, recaudacion por periodo, platos mas vendidos, plato menos vendido y cantidad de mesas atendidas por mozo.

## Convenciones de codigo

- Mantener el estilo C++ simple del proyecto: clases con atributos privados, getters/setters y metodos `cargar()` / `mostrar()`.
- Respetar la separacion existente:
  - Los modelos guardan datos y comportamiento basico de carga/muestra.
  - Los `Manager` coordinan menus, validaciones simples, listados, consultas e informes.
  - Las clases `Archivo` encapsulan lectura/escritura de archivos binarios.
- Para persistencia, seguir el patron con `FILE*`, `fopen`, `fread`, `fwrite`, `fseek`, `ftell` y `fclose`, salvo que se decida una refactorizacion general.
- Los IDs se generan actualmente como `getCantidadRegistros() + 1`; si se agrega baja logica por estado, revisar duplicados antes de confiar en ese calculo.
- Usar `bool estado` como baja logica cuando corresponda, en vez de borrar registros fisicamente.
- Para inputs nuevos o modificados, usar `utilidades.*`:
  - `leerCadena` para textos que puedan tener espacios.
  - `leerEntero`, `leerEnteroEnRango`, `leerFloatMinimo` y `leerSiNo` para numeros y opciones.
  - `leerFecha` para fechas, siempre con formato `dia/mes/anio`.
- Guardar los archivos fuente en UTF-8 si se agregan textos con `ñ`, acentos o signos como `¿`.
- Evitar cambios masivos de estilo o refactors amplios si la tarea es puntual.

## Cuidado con nombres e includes

El repositorio tiene archivos en minuscula (`archivoPlato.h`, `plato.h`, `mesaManager.h`, etc.), pero algunos `#include` usan mayusculas (`"ArchivoPlato.h"`, `"Plato.h"`, `"MesaManager.h"`). En Windows esto suele funcionar; en sistemas case-sensitive puede fallar. Al tocar archivos, preferir normalizar el include al nombre real del archivo.

## Build y ejecucion

Forma principal:

1. Abrir `Sist_Gestion_Restaurant/Sist_Gestion_Restaurant.cbp` en Code::Blocks.
2. Compilar target `Debug` o `Release`.
3. Ejecutar el binario generado.

El compilador instalado para este proyecto esta en:

```powershell
C:\Program Files\CodeBlocks\MinGW\bin\g++.exe
```

Version verificada: GCC 14.2.0.

Para validar desde consola:

```powershell
& 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe' -Wall -fexceptions .\Sist_Gestion_Restaurant\*.cpp -o .\Sist_Gestion_Restaurant\bin\Debug\Sist_Gestion_Restaurant_codex_check.exe
```

Si la compilacion falla, revisar primero los errores del modelo/base antes de tocar menus o informes.

## Datos generados

La aplicacion crea archivos `.dat` en el directorio desde donde se ejecuta, por ejemplo:

- `Reservas.dat`
- `Facturas.dat`
- `platos.dat`
- `detalles.dat`

No commitear archivos `.dat`, binarios generados, ni objetos de compilacion salvo pedido explicito.

## Puntos conocidos a revisar antes de extender

- `DetalleFactura::cargar()` existe por consistencia, pero la carga real de detalles de una factura se coordina desde `DetalleFacturaManager::cargarDetallesFactura`.
- Los IDs siguen generandose como `getCantidadRegistros() + 1`; si se reutilizan registros dados de baja, revisar duplicados.
- Los listados con datos asociados resuelven referencias desde archivos binarios en el momento de mostrar. Si se cambian nombres o claves, revisar reservas, facturas, detalles e informes.

## Al modificar el informe

- Mantener `INFORME DE PROYECTO.md` como fuente editable del informe.
- Conservar el enlace relativo al diagrama: `assets/informe-de-proyecto-diagrama-clases.png`.
- Si se cambia el alcance funcional del sistema, actualizar tambien menus/managers o dejar explicitado que es una salida planificada.
