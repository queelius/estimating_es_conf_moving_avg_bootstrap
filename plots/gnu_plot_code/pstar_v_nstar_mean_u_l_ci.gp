set title "p* Versus Mean{N*} With 95% Confidence Interval"
set xlabel "p*"
set ylabel "N*"
set grid y
set grid x

plot [0.15:0.3] "data_pstar_vs_nstar" using 1:2 t "mean N*" w linespoints, "" using 1:3 t "lower 95% CI" w lines, "" using 1:4 t "upper 95% CI" with lines
call "gif_export.plt" "pstar_vs_nstar_mean.gif"