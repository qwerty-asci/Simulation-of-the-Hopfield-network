set terminal png size 1024,720 enhanced font "Helvetica,15"


set xlabel "Número de iteraciones"
set ylabel "m"

set yra[-2:2]
set xra[0:1e5]

set output 'Evolucion_0_350000.png'
plot '0_350000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,0.0 t '' lc rgb 'black'
 
set output 'Evolucion_0_360000.png'
plot '0_360000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,0.0 t '' lc rgb 'black'

set output 'Evolucion_0_370000.png'
plot '0_370000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,0.0 t '' lc rgb 'black'

set output 'Evolucion_0_380000.png'
plot '0_380000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,0.0 t '' lc rgb 'black'

set output 'Evolucion_0_390000.png'
plot '0_390000.dat' u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,'' u 1:4 t 'Patrón 3' w l,'' u 1:4 t 'Patrón 4' w l,0.0 t '' lc rgb 'black'
