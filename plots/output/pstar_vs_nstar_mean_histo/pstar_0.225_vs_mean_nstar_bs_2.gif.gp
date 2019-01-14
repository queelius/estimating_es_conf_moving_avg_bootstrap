# histogram gnuplot code
# title: p* = 0.225000, [2348.614072, 2666.631130]

reset
set term gif
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xtic rotate by -45 scale 0
set title "p* = 0.225000, [2348.614072, 2666.631130]"
set output "pstar_0.225_vs_mean_nstar_bs_2.gif"
plot "pstar_0.225_vs_mean_nstar_bs_2.gif.dat" using 2:3 title '' smooth frequency with boxes
set output
