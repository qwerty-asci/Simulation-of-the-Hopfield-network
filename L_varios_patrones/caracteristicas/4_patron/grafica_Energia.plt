set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Energia_frente_T.png'

set xlabel "Temperatura (K)"
set ylabel "Energía"

set yra[-20:20]
set xra[0:1.1]

plot "T_Energia.dat" u 1:2:3 w yerror t 'Energía','' w l t '',-14.6614 t 'E. Patrón 1',-13.6195 t 'E. Patrón 2',-16.8194 t 'E. Patrón 3',-14.671 t 'E. Patrón 4',0.0 t '' lc rgb '#00000'
