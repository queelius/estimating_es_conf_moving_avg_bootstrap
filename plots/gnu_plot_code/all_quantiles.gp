set grid x y
set xlabel "theta"
set ylabel "n"
set title "Plots Of Multiple Quantiles"
set key top left
#set logscale y

plot "all_pstars" using 2:3:4:5 index 0 title "p* = 45%" w yerror,\
      "" using 2:3 index 0 title "" w lines, \
      "" using 2:3:4:5 index 1 title "p* = 50%" w yerror,\
      "" using 2:3 index 1 title "" w lines
      #,\
      #"" using 2:($3) index 7 title "p* = 50% "w linespoints,\
      
call "gif_export.plt" "quantile_multiple.gif"
