## Profile Me 1
Al ejecutar el programa se genera un `segfault` en `main`. El motivo es que
hay una asignación estática de arreglos muy grandes que escapa al stack permitido
por `ulimited`. Ejecutando `ulimited -s unlimited` puedo ejecutar el programa.

Monitoreando la ejecucción con `time` obtengo un tiempo de `1.07s`. Con `gprof`
encuentro que casi el 50% del tiempo se debe a la función `first_assign` y el
50% restante se reparte equitativamente entre las otras dos funciones.

Cuando corro con el flag `O1` y utilizo `gprof` encuentro que el tiempo se
redujo uno 30% y, lo más notorio, es que aumento el tiempo porcentual que se
gasta en `first_assign` (60%) y disminuye el de `second_assign` (17% contra 23%
de `main`).

Finalmente con `O2` y `O3` los tiempos son tan pequeños (0.006 s) que `gprof`
no los puede analizar.

Analizando que pasa a nivel procesador con `perf stat`, encuentro que entre el caso
sin optimizar y el de `O2` disminuye la cantidad de instrucciones un órden de
magnitud (6,000,000 vs 600,000). También disminuyen en un 30% los stalled-cycles
. No sé intepretar el resto de la información.

## Profile Me 2
Usando `gprof` veo que sólo reconoce (como es esperable) las funciones del
programa y no de las librerías que usa. Por lo tanto para análisis de tiempo sólo
voy a usar `time`. Nuevamente me encuentro con que hay nulas diferencias entre
`O2` y `O3`, aunque las diferencias entre los sucesivos niveles de optimización
son menores que en el ejercicio anterior.

Mirando las salidas de `perf stat` encuentro que la cantidad de instrucciones y
los stalled-cycles sólo varían significativamente entre los programas compilados
con `O0` y `O1`.
