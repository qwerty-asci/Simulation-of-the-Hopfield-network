set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Solapamiento_frente_T.png'

set xlabel "Temperatura (K)"
set ylabel "m"

set yra[-2:2]
set xra[0:1.1]

plot "T_solapamiento.dat" u 1:2:4 w yerror t 'Coef. Solapamiento','' w l t '',0.0 t '' lc rgb 'black'
