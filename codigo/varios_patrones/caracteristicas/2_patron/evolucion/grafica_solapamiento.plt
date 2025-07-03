set terminal png size 1024,720 enhanced font "Helvetica,15"


set xlabel "Número de iteraciones"
set ylabel "m"

set yra[-2:2]
set xra[0:1e5]

set output 'Evolucion_0_250000.png'
plot "0_250000.dat" u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,0.0 t '' lc rgb '#0000'
 
set output 'Evolucion_0_260000.png'
plot "0_260000.dat" u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_270000.png'
plot "0_270000.dat" u 1:2 t 'Patrón 1' w l,'' u 1:3 t 'Patrón 2' w l,0.0 t '' lc rgb '#0000'
