# histogram gnuplot code
# title: p* = 0.400000, [267951.492537, 288638.272921]

reset
set term gif
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xtic rotate by -45 scale 0
set title "p* = 0.400000, [267951.492537, 288638.272921]"
set output "pstar_0.4_vs_mean_nstar_bs_2.gif"
plot "pstar_0.4_vs_mean_nstar_bs_2.gif.dat" using 2:3 title '' smooth frequency with boxes
set output
