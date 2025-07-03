set terminal png size 1024,720 enhanced font "Helvetica,15"

set output "almacenamiento_400.png"

set yra[0:2]
set xra[0:120]
set xlabel "Número de patrones almacenados"
set ylabel "m"

plot 'resultados.dat' u 1:2:3 w yerr t '', '' u 1:2 w l t 'Coef. Solapamiento', 0.75 lc rgb 'black' t 'Umbral'


