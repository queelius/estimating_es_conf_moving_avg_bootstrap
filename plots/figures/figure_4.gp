set title "Adversary Accuracy Vs Sample Size"
set xlabel "Sample Size"
set xrange[1000:5e7]
set xtics 1e7
#set xtics 20000
set ylabel "Accuracy"
set grid y
set grid x
set key right bottom
plot "gov_nsa" u 2:1 every 40000 index 0 w points title "trial 1", "" u 2:1 every 40000 index 10 w points title "trial 2", "" u 2:1 every 40000 index 2 w points title "trial 3"

call "eps_export.plt" "figure_4.eps"
call "pdf_export.plt" "figure_4.pdf"
