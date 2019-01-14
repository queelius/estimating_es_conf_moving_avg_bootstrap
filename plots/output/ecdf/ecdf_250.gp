set xlabel "5th Percentile (0.05 Quantile)"
set ylabel "n"
set grid x y
plot "pop_data" using 1:(1) title "Population CDF" smooth frequency, \
"ecdf_250.dat" using 1:(1) title "Empirical CDF" smooth frequency
set title "Empirical CDF (Sample Size 250) Versus Population CDF"
call "png_export.plt" "250.png"