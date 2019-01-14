set title "Histogram Of Encrypted Word Frequencies From Sample (~Zipf)"
set xlabel "Encrypted Word"
set ylabel "Relative Frequency"
set boxwidth 0.75
set grid y
set xtics rotate
set ytics nomirror
set style fill solid
plot "compare_zipf_encrypted_versus_plain.dat" u 0:($2/1200):xtic(1) index 1 title "" w boxes fc rgb "gray"

call "gif_export.plt" "encrypted_words_histo.gif"