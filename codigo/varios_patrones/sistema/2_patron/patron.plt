set terminal png size 1024,720 enhanced font "Helvetica,15"

set view map

set yra[11:-2]
set xra[-1:10]

#unset key

set output 'final_T_0_000000.png'
splot '0_000000.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Patrón Final'

set output 'final_T_0_020000.png'
splot '0_020000.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Patrón Final'

set output 'final_T_0_100000.png'
splot '0_100000.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Patrón Final'

set output 'final_T_0_200000.png'
splot '0_200000.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Patrón Final'

set output 'final_T_0_260000.png'
splot '0_260000.dat' u 2:($1):3 pt 5 ps 5 lc rgb '#00000' t 'Patrón Final'
