# histogram gnuplot code
# title: p* = 0.375000, mu = 144748.134328 +- 5871.481876

reset
set term gif
set auto x
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xtic rotate by -45 scale 0
set title "p* = 0.375000, mu = 144748.134328 +- 5871.481876"
set xrange [1e2:]
set xrange [:1e7]
set yrange [0:]
set yrange [:50]
set output "0.375000.gif"
set logscale x
plot "0.375000.gif.dat" using 2:3 title '' smooth frequency with boxes
set output
