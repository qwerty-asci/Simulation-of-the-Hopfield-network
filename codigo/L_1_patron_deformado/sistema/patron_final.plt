set terminal png size 1024,720 enhanced font "Helvetica,15"


set view map

set xra[-3:32]
set yra[-3:36]

#unset key

set output 'final_T_0_000000.png'
splot 'final_T_0_000000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_020000.png'
splot 'final_T_0_020000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_100000.png'
splot 'final_T_0_100000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_200000.png'
splot 'final_T_0_200000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_250000.png'
splot 'final_T_0_250000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_300000.png'
splot 'final_T_0_300000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'

set output 'final_T_0_100000.png'
splot 'final_T_0_100000.dat' u 1:2:3 pt 5 ps 3 lc rgb '#00000' t 'Patrón final'
