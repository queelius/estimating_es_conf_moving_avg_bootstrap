set title "Histogram Of Word Frequencies (Zipf)"
set xlabel "Word"
set ylabel "Relative Frequency"
set boxwidth 0.75
set grid y
set xtics rotate
set ytics nomirror
set style fill transparent pattern 0.5 border

plot "figure_2a.dat" u 0:($2/400):xtic(1) title "Plain Text Words" w boxes, "figure_2b.dat" u 0:($2/1200) index 1 title "Encrypted Words" w boxes

call "eps_export.plt" "plainwordshisto.eps"