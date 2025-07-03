set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Energia_frente_T.png'

set xlabel "Temperatura (K)"
set ylabel "Energía"

set yra[-20:20]
set xra[0:1.1]

plot "T_Energia.dat" u 1:2:3 w yerror t 'Energía','' w l t '',-15.0349 t 'E. Patrón 1',-14.4741 t 'E. Patrón 2',-18.1663 t 'E. Patrón 3',-18.6908 t 'E. Patrón 4', -10.4074 t 'E. Patrón 5', -16.7781 t 'E. Patrón 6', -14.1961 t 'E. Patrón 7', 0.0 t '' lc rgb '#00000'
