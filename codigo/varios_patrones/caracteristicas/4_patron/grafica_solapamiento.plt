set terminal png size 1024,720 enhanced font "Helvetica,15"


set xlabel "Temperatura (K)"
set ylabel "m"

set yra[-2:2]
set xra[0:1.1]

set output 'Solapamiento_frente_T.png'
plot "T_solapamiento.dat" u 1:2:3 w yerr t '','' u 1:2 w l t 'Patrón 1', "T_solapamiento.dat" u 1:4:5 w yerr t '','' u 1:4 w l t 'Patrón 2', "T_solapamiento.dat" u 1:6:7 w yerr t '','' u 1:6 w l t 'Patrón 3',"T_solapamiento.dat" u 1:8:9 w yerr t '','' u 1:8 w l t 'Patrón 4',0.0 t '' lc rgb '#00000'

set output 'Solapamiento_frente_T_err.png'
plot "T_solapamiento.dat" u 1:2 w l t 'Patrón 1', "T_solapamiento.dat" u 1:4 w l t 'Patrón 2', "T_solapamiento.dat" u 1:6 w l t 'Patrón 3',"T_solapamiento.dat" u 1:8 w l t 'Patrón 4',0.0 t '' lc rgb '#00000'


set output 'Solapamiento_frente_T_1_2.png'
plot "T_solapamiento.dat" u 1:2:3 w yerr t '','' u 1:2 w l t 'Patrón 1', "T_solapamiento.dat" u 1:4:5 w yerr t '','' u 1:4 w l t 'Patrón 2', 0.0 t '' lc rgb '#00000'

set output 'Solapamiento_frente_T_1_2_err.png'
plot "T_solapamiento.dat" u 1:2 w l t 'Patrón 1', "T_solapamiento.dat"  u 1:4 w l t 'Patrón 2', 0.0 t '' lc rgb '#00000'

set output 'Solapamiento_frente_T_3_4.png'
plot "T_solapamiento.dat" u 1:6:7 w yerr t '','' u 1:6 w l t 'Patrón 3',"T_solapamiento.dat" u 1:8:9 w yerr t '','' u 1:8 w l t 'Patrón 4',0.0 t '' lc rgb '#00000'

set output 'Solapamiento_frente_T_3_4_err.png'
plot "T_solapamiento.dat" u 1:6 w l t 'Patrón 3',"T_solapamiento.dat" u 1:8 w l t 'Patrón 4',0.0 t '' lc rgb '#00000'
