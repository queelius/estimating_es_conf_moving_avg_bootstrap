set title "Adversary Accuracy Vs Sample Size"
set xlabel "Sample Size"
set xrange[1000:5e7]
set xtics 1e7
#set xtics 20000
set ylabel "Accuracy"
set grid y
set grid x
set key right bottom
#plot [1000:100000] "gov_nsa" u 2:1 index 0 w lines title "trial 1"
plot "gov_nsa" u 2:1 every 2000 index 0 w lines title "trial 1", "" u 2:1 every 2000 index 10 w lines title "trial 2", "" u 2:1 every 2000 index 2 w lines title "trial 3"
call "gif_export.plt" "simple_accuracy_vs_sample_size_multiple_trials.gif"
#call "gif_export.plt" "simple_accuracy_vs_sample_size_small.gif"