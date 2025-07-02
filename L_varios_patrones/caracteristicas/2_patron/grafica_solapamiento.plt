set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Solapamiento_frente_T.png'

set xlabel "Temperatura (K)"
set ylabel "m"

set yra[-2:2]
set xra[0:1.1]

plot "T_solapamiento.dat" u 1:2:3 w yerr t '','' u 1:2 w l t 'Patrón 1', "T_solapamiento.dat" u 1:4:5 w yerr  t '','' u 1:4 w l t 'Patrón 2',0.0 t '' lc rgb '#00000'
