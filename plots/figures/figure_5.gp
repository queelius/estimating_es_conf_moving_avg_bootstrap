set title "Adversary Accuracy Vs Sample Size -- Closer Inspection"
set xlabel "Sample Size"
set xtics 20000
set ylabel "Accuracy"
set grid y
set grid x
set key right bottom
plot [1000:100000] "gov_nsa" u 2:1 index 0 w lines title "trial 1"

call "eps_export.plt" "figure_5.eps"
call "pdf_export.plt" "figure_5.pdf"
