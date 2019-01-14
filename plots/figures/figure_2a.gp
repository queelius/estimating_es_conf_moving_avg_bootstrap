set title "Histogram Of Plain Text Word Frequencies (Zipf)"
set xlabel "Plain Text Word"
set ylabel "Relative Frequency"
set boxwidth 0.75
set grid y
set xtics rotate
set ytics nomirror
set style fill solid border

plot "figure_2a.dat" u 0:($2/400):xtic(1) notitle w boxes fc rgb 'grey'

call "eps_export.plt" "figure_2a.eps"
call "pdf_export.plt" "figure_2a.pdf"