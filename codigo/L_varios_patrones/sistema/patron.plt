set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'condicion_incial.png'

set view map

set yra[11:-2]
set xra[-1:10]

#unset key

splot 'condicion_incial.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Condición inicial'
