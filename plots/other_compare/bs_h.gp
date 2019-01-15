set xlabel "5th Percentile (0.05 Quantile)"
set ylabel "n"
set grid x y
set title "Empirical CDF -- Sample Size n"

plot "pop_data" using 2:(1) title "Population CDF" smooth frequency,
      "sample_data_n" using 2:(1) title "Empirical CDF" smooth frequency

call "gif_export.plt" "ecdf_n,gif"
