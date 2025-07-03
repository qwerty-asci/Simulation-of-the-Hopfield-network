set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Energia_frente_T_2.png'

set xlabel "Temperatura (K)"
set ylabel "Energía"

set yra[-20:20]
set xra[0:1.1]

plot "T_Energia.dat" u 1:2:3 w yerror t 'Energía','' w l t '',-12.6555 t 'E. Patrón 1',-12.6555 t 'E. Patrón 2',0.0 t '' lc rgb '#00000'
