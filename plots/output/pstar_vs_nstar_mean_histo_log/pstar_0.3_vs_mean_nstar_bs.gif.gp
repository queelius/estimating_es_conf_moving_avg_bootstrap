# histogram gnuplot code
# title: p* = 0.300000, [18172.921109, 20042.750533]

reset
set term gif
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xtic rotate by -45 scale 0
set title "p* = 0.300000, [18172.921109, 20042.750533]"
set xrange [1e2:]
set xrange [:1e7]
set yrange [0:]
set yrange [:50]
set output "pstar_0.3_vs_mean_nstar_bs.gif"
set logscale x
plot "pstar_0.3_vs_mean_nstar_bs.gif.dat" using 2:3 title '' smooth frequency with boxes
set output
