# Validacion Fase 8

## Objetivo

Validar que el sistema de gestion de restaurante se puede demostrar de punta a punta, alineado con las salidas declaradas en `INFORME DE PROYECTO.md`: listados, consultas e informes sobre mozos, clientes, mesas, platos, reservas, facturas y detalles de factura.

Esta fase no agrega funcionalidad nueva. La evidencia principal es este recorrido manual, la compilacion final y la verificacion de que no se versionen archivos generados.

## Compilacion

Desde la raiz del repositorio:

```powershell
& 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe' -Wall -fexceptions .\Sist_Gestion_Restaurant\*.cpp -o .\Sist_Gestion_Restaurant\bin\Debug\Sist_Gestion_Restaurant_codex_check.exe
```

Criterio esperado:

- La compilacion termina sin errores.
- El ejecutable queda generado en `Sist_Gestion_Restaurant/bin/Debug/Sist_Gestion_Restaurant_codex_check.exe`.
- No se deben commitear `.exe`, `.o`, `.dat`, `bin/` ni `obj/`.

## Ejecucion En Carpeta Limpia

La aplicacion crea los archivos `.dat` en el directorio desde donde se ejecuta. Para no mezclar datos de prueba con el proyecto, ejecutar desde una carpeta temporal:

```powershell
New-Item -ItemType Directory -Force -Path E:\tmp\restaurant-demo | Out-Null
Set-Location E:\tmp\restaurant-demo
& E:\workspace\sistema-gestion-restaurant-P2\Sist_Gestion_Restaurant\bin\Debug\Sist_Gestion_Restaurant_codex_check.exe
```

Archivos esperados despues de cargar datos:

- `mozos.dat`
- `clientes.dat`
- `mesa.dat`
- `platos.dat`
- `Reservas.dat`
- `Facturas.dat`
- `detalles.dat`

## Prueba Inicial Sin Datos

Antes de cargar registros, entrar a cada submenu y ejecutar un listado o consulta.

Recorrido minimo:

- Menu principal > `1. MOZOS` > `4. LISTAR POR APELLIDO`.
- Menu principal > `2. CLIENTES` > `4. LISTAR POR APELLIDO`.
- Menu principal > `3. MESAS` > `4. LISTAR POR NUMERO`.
- Menu principal > `4. PLATOS` > `4. LISTAR POR NOMBRE`.
- Menu principal > `5. RESERVAS` > `2. LISTAR TODAS LAS RESERVAS`.
- Menu principal > `6. FACTURAS` > `2. LISTAR TODAS LAS FACTURAS`.
- Menu principal > `7. INFORMES` > ejecutar cada informe con fechas o IDs validos aunque no haya datos.

Resultado esperado:

- Las pantallas muestran mensajes como "NO HAY ...", "No hay ... registrados" o total `$0`.
- La aplicacion no se cierra inesperadamente.
- La opcion `0` vuelve siempre al menu anterior.

## Datos De Demo

Usar valores sin espacios porque las cargas usan `cin >>`.

### Mozos

Menu principal > `1. MOZOS` > `1. ALTA DE MOZO`.

| Campo | Mozo 1 | Mozo 2 |
| --- | --- | --- |
| DNI | 30111222 | 28999888 |
| Nombre | Ana | Bruno |
| Apellido | Gomez | Perez |
| Telefono | 1130001111 | 1130002222 |
| Email | ana@resto.com | bruno@resto.com |
| Turno | 1 | 3 |
| Dia nac. | 10 | 5 |
| Mes nac. | 4 | 9 |
| Anio nac. | 1990 | 1988 |

IDs esperados si la carpeta esta limpia:

- Ana Gomez: `1`.
- Bruno Perez: `2`.

Validar:

- `4. LISTAR POR APELLIDO`: Gomez antes que Perez.
- `5. LISTAR POR TURNO`: Ana en Maniana, Bruno en Noche.
- `6. CONSULTAR POR DNI`: buscar `30111222`.
- `7. CONSULTAR POR TURNO`: buscar turno `3`.

Caso negativo:

- Consultar DNI `99999999`; debe indicar que no se encontro.

### Clientes

Menu principal > `2. CLIENTES` > `1. ALTA DE CLIENTE`.

| Campo | Cliente 1 | Cliente 2 |
| --- | --- | --- |
| DNI | 20111222 | 20999888 |
| Nombre | Carla | Diego |
| Apellido | Alvarez | Suarez |
| Telefono | 1140001111 | 1140002222 |
| VIP | 1 | 0 |

IDs esperados:

- Carla Alvarez: `1`.
- Diego Suarez: `2`.

Validar:

- `4. LISTAR POR APELLIDO`: Alvarez antes que Suarez.
- `5. LISTAR CLIENTES VIP`: solo Carla.
- `6. CONSULTAR POR DNI`: buscar `20111222`.
- `7. CONSULTAR VIP POR DNI`: `20111222` debe mostrar VIP y `20999888` no VIP.

Caso negativo:

- Consultar DNI `88888888`; debe indicar que no se encontro.

### Mesas

Menu principal > `3. MESAS` > `1. ALTA DE MESA`.

| Campo | Mesa 1 | Mesa 2 |
| --- | --- | --- |
| Numero | 10 | 20 |
| Descripcion | Ventana | Terraza |
| Sillas | 4 | 6 |
| Ubicacion | 1 | 2 |

Validar:

- `4. LISTAR POR NUMERO`: mesa 10 antes que mesa 20.
- `5. LISTAR POR UBICACION`: mesa 10 en Interior y mesa 20 en Terraza.
- `6. CONSULTAR POR NUMERO`: buscar `10`.
- `7. CONSULTAR POR UBICACION`: buscar `2`.

Casos negativos:

- Alta repetida de mesa `10`; debe informar que ya existe.
- Consultar mesa `99`; debe indicar que no se encontro.

### Platos

Menu principal > `4. PLATOS` > `1. ALTA DE PLATO`.

| Campo | Plato 1 | Plato 2 | Plato 3 | Plato 4 |
| --- | --- | --- | --- | --- |
| Nombre | Empanadas | Milanesa | Flan | Gaseosa |
| Categoria | 1 | 2 | 3 | 4 |
| Precio | 1200 | 4500 | 1800 | 900 |

IDs esperados:

- Empanadas: `1`.
- Milanesa: `2`.
- Flan: `3`.
- Gaseosa: `4`.

Validar:

- `4. LISTAR POR NOMBRE`: orden alfabetico.
- `5. LISTAR POR CATEGORIA`: un plato en cada categoria.
- `6. LISTAR POR PRECIO`: Gaseosa, Empanadas, Flan, Milanesa.
- `7. CONSULTAR POR CATEGORIA`: buscar categoria `2`.
- `8. CONSULTAR POR RANGO DE PRECIOS`: buscar desde `1000` hasta `2000`, deben aparecer Empanadas y Flan.

Caso negativo:

- Rango desde `8000` hasta `9000`; debe informar que no hay platos en ese rango.

## Reservas

### Reserva Valida

Menu principal > `5. RESERVAS` > `1. NUEVA RESERVA`.

Datos:

- ID Cliente: `1`.
- Numero Mesa: `10`.
- Fecha: `15 7 2026`.
- Hora: `21`.
- Comensales: `4`.

Resultado esperado:

- Se crea la reserva `1`.
- Estado de reserva inicial: pendiente.

### Reserva A Cancelar

Crear otra reserva:

- ID Cliente: `2`.
- Numero Mesa: `20`.
- Fecha: `16 7 2026`.
- Hora: `20`.
- Comensales: `6`.

Luego ejecutar `4. CANCELAR RESERVA` con ID `2`.

Resultado esperado:

- La reserva queda en estado cancelada.
- `6. LISTADO POR ESTADO` muestra primero pendientes y luego canceladas.
- `9. CONSULTA POR ESTADO` con `3` muestra la reserva cancelada.

Casos negativos:

- Crear reserva con cliente `99`; debe informar que no existe cliente activo.
- Crear reserva con mesa `99`; debe informar que no existe mesa activa.
- Crear otra reserva para mesa `10`, fecha `15 7 2026`, hora `21`; debe informar superposicion.
- Buscar reserva `99`; debe indicar que no se encontro.

## Facturas Y Detalles

### Factura Activa

Menu principal > `6. FACTURAS` > `1. EMITIR NUEVA FACTURA`.

Datos:

- Numero mesa: `10`.
- ID Mozo: `1`.
- Fecha: `15 7 2026`.
- Forma de pago: `1`.
- Detalle 1:
  - ID Plato: `1`.
  - Cantidad: `2`.
  - Agregar otro: `1`.
- Detalle 2:
  - ID Plato: `2`.
  - Cantidad: `1`.
  - Agregar otro: `1`.
- Detalle 3:
  - ID Plato: `4`.
  - Cantidad: `3`.
  - Agregar otro: `0`.
- Monto abonado: `10000`.

Importe esperado:

- Empanadas: `2 * 1200 = 2400`.
- Milanesa: `1 * 4500 = 4500`.
- Gaseosa: `3 * 900 = 2700`.
- Total: `$9600`.
- Vuelto: `$400`.

### Factura A Anular

Crear segunda factura:

- Numero mesa: `20`.
- ID Mozo: `2`.
- Fecha: `16 7 2026`.
- Forma de pago: `2`.
- Detalle 1:
  - ID Plato: `3`.
  - Cantidad: `5`.
  - Agregar otro: `0`.
- Monto abonado: `9000`.

Importe esperado:

- Flan: `5 * 1800 = 9000`.
- Total: `$9000`.

Luego ejecutar `4. ANULAR FACTURA` con ID `2` y confirmar con `1`.

Resultado esperado:

- La factura `2` queda anulada.
- Sus detalles dejan de listarse como activos.
- Buscar factura `2` debe informar que esta anulada.

Validar tambien:

- `2. LISTAR TODAS LAS FACTURAS`: debe mostrar solo la factura activa.
- `3. BUSCAR FACTURA POR ID`: buscar `1`.
- `5. LISTADO POR FECHA`: ordenado por fecha.
- `6. LISTADO POR NUMERO DE MESA`: ordenado por mesa.
- `7. CONSULTA POR RANGO DE FECHAS`: desde `15 7 2026` hasta `16 7 2026`, debe mostrar solo factura activa.
- `8. CONSULTA POR NUMERO DE MESA`: buscar `10`.
- `9. CONSULTA POR MOZO`: buscar `1`.

Casos negativos:

- Buscar factura `99`; debe indicar que no se encontro.
- Anular factura `99`; debe indicar que no se encontro.
- Consulta por rango invertido, desde `20 7 2026` hasta `15 7 2026`; debe informar rango invalido.
- Emitir factura con mesa `99`; debe informar que no existe mesa activa.
- Emitir factura con mozo `99`; debe informar que no existe mozo activo.
- En detalle de factura ingresar plato `99`; debe informar que no existe plato activo y permitir continuar.
- Cerrar detalle sin agregar ningun plato; debe informar que no se puede guardar una factura sin detalles.
- Ingresar monto abonado menor al total; debe rechazar la factura.

## Informes

Menu principal > `7. INFORMES`.

Con el dataset anterior y la factura `2` anulada, los resultados esperados son:

| Informe | Entrada | Resultado esperado |
| --- | --- | --- |
| Recaudacion por dia | `15 7 2026` | `$9600` |
| Recaudacion por dia | `16 7 2026` | `$0`, porque la factura de ese dia fue anulada |
| Recaudacion por periodo | desde `15 7 2026` hasta `16 7 2026` | `$9600` |
| Platos mas vendidos | sin entrada extra | Gaseosa, ID `4`, cantidad `3` |
| Plato menos vendido | sin entrada extra | Milanesa, ID `2`, cantidad `1` |
| Mesas atendidas por mozo | ID Mozo `1` | `1` |
| Mesas atendidas por mozo | ID Mozo `2` | `0`, porque su factura fue anulada |

Nota: el informe de plato menos vendido considera solo platos vendidos al menos una vez. No debe considerar platos con cero ventas.

Casos negativos:

- Recaudacion por periodo con fecha desde mayor que fecha hasta; debe informar rango invalido.
- Mesas atendidas por mozo con ID `99`; debe indicar que no existe un mozo con ese ID.
- Ejecutar rankings sin facturas activas en una carpeta limpia; debe informar que no hay ventas activas para informar.

## Checklist Final

Antes de cerrar la fase:

- [ ] Compilar con el comando documentado.
- [ ] Ejecutar la demo desde una carpeta temporal limpia.
- [ ] Cargar el dataset minimo completo.
- [ ] Validar listados y consultas de mozos, clientes, mesas y platos.
- [ ] Validar reserva activa, reserva cancelada y casos negativos.
- [ ] Validar factura activa, factura anulada y casos negativos.
- [ ] Validar los cinco informes del informe del proyecto.
- [ ] Confirmar que los importes esperados coinciden con la salida.
- [ ] Ejecutar `git status --short`.
- [ ] Verificar que no queden `.dat`, `.exe`, `.o`, `bin/` u `obj/` agregados al commit.

## Comando De Control De Artefactos

Para revisar archivos generados antes de commitear:

```powershell
Get-ChildItem -Recurse -Force -Include *.dat,*.exe,*.o -Path . | Select-Object FullName,Length
```

Si alguno aparece como archivo nuevo en `git status --short`, no debe agregarse al commit salvo pedido explicito.
