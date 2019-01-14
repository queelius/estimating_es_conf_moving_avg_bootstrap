GOOD_ROW(x,y) = (x eq "G") ? y:1/0
BAD_ROW(x,y) = (x eq "B") ? y:1/0

set title "Histogram Of Encrypted Words Accurately Mapped"
set xlabel "Word"
set ylabel "Relative Frequency"
set boxwidth 0.75
set grid y
set xtics rotate
set ytics nomirror
set style fill pattern

plot "figure_3.dat" u ($0):(GOOD_ROW(stringcolumn(3),$2/1200)):xtic(4) t "correct" w boxes, "" u ($0):(BAD_ROW(stringcolumn(3),$2/1200)):xtic(4) t "incorrect" w boxes
#plot "figure_3.dat" u 2:xtic(4) t "correct" w boxes, "" u 2:xtic(4) t "incorrect" w boxes

call "eps_export.plt" "figure_3.eps"
call "pdf_export.plt" "figure_3.pdf"