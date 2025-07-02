set terminal png size 1024,720 enhanced font "Helvetica,15"


set xlabel "Número de iteraciones"
set ylabel "m"

set yra[-2:2]
set xra[0:1e7]

 
set output 'Evolucion_0_000000.png'
plot "0_000000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_020000.png'
plot "0_020000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_100000.png'
plot "0_100000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_200000.png'
plot "0_200000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_250000.png'
plot "0_250000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_0_300000.png'
plot "0_300000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'

set output 'Evolucion_1_000000.png'
plot "1_000000.dat" u 1:2 t 'Coef. Solapamiento' w l,0.0 t '' lc rgb '#0000'
