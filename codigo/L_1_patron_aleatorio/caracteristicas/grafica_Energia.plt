set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Energia_frente_T.png'

set xlabel "Temperatura (K)"
set ylabel "Energía"

set yra[-50:15]
set xra[0:1.1]

plot "T_Energia.dat" u 1:2:4 w yerror t 'Energía','' w l t '',-48.2778 t 'Energía patrón' lc rgb "green",0.0 t '' lc rgb '#00000'
