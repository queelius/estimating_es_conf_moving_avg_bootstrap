set xlabel "5th Percentile (0.05 Quantile)"
set ylabel "n"
set grid x y
plot "pop_data" using 1:(1) title "Population CDF" smooth frequency, \
"output2\\ecdf_396.dat" using 1:(1) title "Empirical CDF" smooth frequency
set title "Empirical CDF -- Sample Size 3960"
call "gif_export.plt" "ecdf_396.gif"