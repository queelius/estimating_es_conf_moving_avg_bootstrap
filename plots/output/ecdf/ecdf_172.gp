set xlabel "5th Percentile (0.05 Quantile)"
set ylabel "n"
set grid x y
plot "pop_data" using 1:(1) title "Population CDF" smooth frequency, \
"output2\\ecdf_172.dat" using 1:(1) title "Empirical CDF" smooth frequency
set title "Empirical CDF -- Sample Size 344"
call "gif_export.plt" "ecdf_172.gif"