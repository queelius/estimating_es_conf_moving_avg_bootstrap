set title "Adversary Accuracy vs Sample Size"
set xlabel "Sample Size"
set ylabel "Accuracy"
set grid y
set grid x
plot 'data1_1_cleaned_plot' using 2:1
call "gif_export.plt" "simple_accuracy_vs_sample_size.gif"