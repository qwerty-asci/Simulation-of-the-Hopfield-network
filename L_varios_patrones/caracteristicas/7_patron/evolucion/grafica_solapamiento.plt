set terminal png size 1024,720 enhanced font "Helvetica,15"


set xlabel "Número de iteraciones"
set ylabel "m"

set yra[-2:2]
set xra[0:1e5]

set output 'Evolucion_0_430000.png'
plot '0_430000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,'' u 1:5 t 'Patrón 5' w l,'' u 1:6 t 'Patrón 6' w l,'' u 1:7 t 'Patrón 7' w l,0.0 t '' lc rgb 'black'
 
set output 'Evolucion_0_440000.png'
plot '0_440000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,'' u 1:5 t 'Patrón 5' w l,'' u 1:6 t 'Patrón 6' w l,'' u 1:7 t 'Patrón 7' w l,0.0 t '' lc rgb 'black'

set output 'Evolucion_0_450000.png'
plot '0_450000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,'' u 1:5 t 'Patrón 5' w l,'' u 1:6 t 'Patrón 6' w l,'' u 1:7 t 'Patrón 7' w l,0.0 t '' lc rgb 'black'

