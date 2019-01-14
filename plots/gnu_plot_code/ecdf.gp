set title "5th Percentile Sampling Distribution (Empirical CDF's Sample Size = 1200)"
set xlabel "5th Percentile (0.05 Quantile)"
set ylabel "Cumulative Probability"
set key left top
set grid x
set xrange [5000:11000]
set yrange [0:1]
plot "pop_data_cdf" using 1:3 title "Population", \
"sample_data_cdf" using 1:3 title "Empirical"
call "gif_export.plt" "ecdf_1200.gif"