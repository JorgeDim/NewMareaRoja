goto test
goto Dt100

:test
Pila2t  -Datos MallaCilindrica.txt  -CalculoContinuo -TipoCalculo 2  > salida1
exit

:MallaRefinada
Pila2t  -Datos MallaCilindrica.txt  -nR 20  -NDivZ 30  -CalculoContinuo -TipoCalculo 2  > salida1
exit

:Dt100
Pila2t  -Datos MallaCilindrica.txt  -nR 20  -NDivZ 30  -CalculoContinuo -dt 100 -TipoCalculo 2  > salida1
exit

:end