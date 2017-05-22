rem goto finos
goto todos500_5m
goto todos1000
goto test

:test
start /b Pila1 -Datos Datos.txt -malla 1 -CalculoContinuo -nR 9 -nR2 5 -nTh 5  -NDivZ 3  -hc_lateral 10
goto end

:todos1000
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 3600  -Tmax 3600000 -DistanciaAlBorde 0.1 >s1
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 3600  -Tmax 3600000  -DistanciaAlBorde 1   >s2
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 3600  -Tmax 3600000  -DistanciaAlBorde 10   >s3
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 3600000  -DistanciaAlBorde 0.1 >s4
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 3600000  -DistanciaAlBorde 1 >s5
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 3600000  -DistanciaAlBorde 10 >s6
goto end 
 
:todos500_5m
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 1800000 -Dominio_Hmax 5 -DistanciaAlBorde 0.1 >s4b
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 1800000 -Dominio_Hmax 5  -DistanciaAlBorde 1 >s5b
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 3600  -Tmax 1800000 -Dominio_Hmax 5  -DistanciaAlBorde 10 >s6b
goto end 
 

 =15.0

:todos
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 1800 -DistanciaAlBorde 0.1 >s1
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 1800 -DistanciaAlBorde 1   >s2
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 15 -nR2 10 -nTh 12  -NDivZ 30  -dt 1800 -DistanciaAlBorde 10   >s3
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 1800 -DistanciaAlBorde 0.1 >s4
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 1800 -DistanciaAlBorde 1 >s5
ping 127.0.0.1 -n 11 > nul
start /b Pila2t -Datos DatosViernes7Abril.txt  -CalculoContinuo -nR 20 -nR2 15 -nTh 15  -NDivZ 40  -dt 1800 -DistanciaAlBorde 10 >s6
goto end 
 

:end
