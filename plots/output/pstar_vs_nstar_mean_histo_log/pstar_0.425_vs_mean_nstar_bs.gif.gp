# histogram gnuplot code
# title: p* = 0.425000, [515926.652452, 551180.063966]

reset
set term gif
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xtic rotate by -45 scale 0
set title "p* = 0.425000, [515926.652452, 551180.063966]"
set xrange [1e2:]
set xrange [:1e7]
set yrange [0:]
set yrange [:50]
set output "pstar_0.425_vs_mean_nstar_bs.gif"
set logscale x
plot "pstar_0.425_vs_mean_nstar_bs.gif.dat" using 2:3 title '' smooth frequency with boxes
set output
