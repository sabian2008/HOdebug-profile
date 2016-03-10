## Floating point exception
Con la tecnología SSE puedo obtener en tiempo de ejecución, cuando se produce
un floating point exception y actuar consecuentemente. Es necesario
informar al compilador que se quieren atrapar las excepciones de punto flotante.

Para resolverlo se puede linkear a las funciones que implementan esa tecnología
las cuales dependen a su vez de `math` (Standard C). Por lo tanto hay que linkear
primero a `fpe_x87_sse` y luego a la librería `math`.

## Sigsegv
Cuando compilo y ejecuto el programa obtengo un segfault. Sin embargo no se
genera ningún core ya que `ulimit` está seteado a 0. Al ejecutar `ulimit -s unlimited`
el programa se ejecuta pero demora muchísimo. La demora se debe a que las
operaciones del programa son costosas computacionalmente. La diferencia entre el
segfault y la corrida normal se debe a que, en la primera, el usuario no tiene
acceso a más que 8MB del stack, mientras que en el segundo caso corre sin
restricciones.

Si se cierra la terminal y se abre una nueva, el stack size se reinicia.

Setear `ulimit` es un hack más que un bugfix, ya que en condiciones normales
(sin setear `ulimit`) el programa no funciona.

## Valgrind (unfinished)
Al ejecutar test_oob4.c con `valgrind --leak-check=full --track-origins=yes`
obtengo que hay bloques de memoria que no se liberan al finalizar el programa
(memory leak). El problema es que la función `mysub` usa `malloc` pero nunca
usa `free`.

Luego de dejar corriendo `source1.c` durante un buen rato, el programa seguía
sin terminar y el consumo de memoria aumentaba cada vez más.

## Funny
Cuando lo ejecuto sin ningún flag, obtengo sólo un segfault. Cuando compilo con
`-DDEBUG` el programa logra imprimir antes de "segfaultear", ya que hay secciones
en el código encerradas por bloques `ifdef` que dependen de este flag.

Si cambio DIM a un número menor, el programa corre hasta el final y
devuelve `a=0`. El problema está en que el DIM original excede la dimensión de
`int`, por lo que el loop genera un comportamiento errático.
