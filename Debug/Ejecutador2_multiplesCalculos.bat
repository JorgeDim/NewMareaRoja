rem goto finos
goto todos
goto test

start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 3 -nR2 3 -nTh 3  -NDivZ 3  -hc_lateral 10 > salida
goto end


:test
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 9 -nR2 5 -nTh 5  -NDivZ 3  -hc_lateral 10
goto end

:todos
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -DistanciaAlBorde 0.1 >s1
ping 127.0.0.1 -n 6 > nul
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -DistanciaAlBorde 0.5 >s2
ping 127.0.0.1 -n 6 > nul
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -DistanciaAlBorde 1 >s3
ping 127.0.0.1 -n 6 > nul
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -DistanciaAlBorde 0.1 >s4
ping 127.0.0.1 -n 6 > nul
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -DistanciaAlBorde 0.5 >s5
ping 127.0.0.1 -n 6 > nul
start /b Pila2t -Datos Datos.txt -malla 1 -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -DistanciaAlBorde 1 >s6
goto end 

:finos
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 15  -nTh 15  -NDivZ 40  -hc_lateral 1
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 15  -nTh 15  -NDivZ 40  -hc_lateral 0.01
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 15 -nR2 15  -nTh 15  -NDivZ 40  -hc_lateral 0.0001
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 20 -nR2 20  -nTh 20  -NDivZ 60  -hc_lateral 1
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 25 -nR2 25  -nTh 25  -NDivZ 70  -hc_lateral 0.01
SLEEP 2
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 30 -nR2 30  -nTh 30  -NDivZ 90  -hc_lateral 0.0001
 

:end
