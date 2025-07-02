set terminal png size 1024,720 enhanced font "Helvetica,15"
set output 'Evolucion_estb.png'


set yra[-2.5:2.5]
set xra[0:400000]

set ylabel "m"
set xlabel "nº de iteraciones"

plot '0_000000.dat' u 1:2 w l t 'T<1.00·10^-^2 K','0_100000.dat' u 1:2 w l t 'T=0.10 K','0_200000.dat' u 1:2 w l t 'T=0.20 K','0_300000.dat' u 1:2 w l t 'T=0.30 K','0_900000.dat' u 1:2 w l t 'T=0.90 K' lc rgb '#fe1313'
