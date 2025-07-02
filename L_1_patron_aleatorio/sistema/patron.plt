set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'condicion_incial.png'

set view map

set xra[-3:32]
set yra[-3:35]

#unset key

splot 'condicion_incial.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Condición inicial'
