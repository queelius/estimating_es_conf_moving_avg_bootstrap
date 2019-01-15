set grid x y
set xlabel "theta"
set ylabel "N*"
set title "Quantile Garph: F-1(0 given p* = 0.3)"

#"" every 4::2 using 2:3:3 title "" w labels offset 0,1, "" every 4 using 2:4:4 title "" w labels offset 0,-1.25, "" every 4 using 2:5:5 title "" w labels offset 0,1.25, \

plot "quantiles_with_ci_2" using 2:3 title "mean{quantile(0 given p*=0.3)}" w linespoints lc rgb 'gold', "" using 2:3:4:5 title "" w yerror lc rgb 'gold', \
    "" using 2:4 title "lower 95% CI" w lines, "" using 2:5 title "upper 95% CI" w lines, \
    "" every ::14 using 2:4:4 title "" w labels offset 0,-1, "" every ::14 using 2:5:5 title "" w labels offset 0,-1, \
    "" every 100::0 using 2:4:4 title "" w labels offset -1.75,-0.5, "" every 100::0 using 2:5:5 title "" w labels offset -1.75,0.25, \
    "" every 100::9 using 2:4:4 title "" w labels offset 0,-1, "" every 100::9 using 2:5:5 title "" w labels offset 0,1, \
    "" every 100::5 using 2:4:4 title "" w labels offset 0,-1, "" every 100::5 using 2:5:5 title "" w labels offset 0,1, \
    "pstar=0.3_vs_nstar" using (0.075):2:3:4 title "mean{N* given p*=0.3}" w errorbars lc rgb "grey", \
    "pstar=0.3_vs_nstar" using (0.075):3:3 title "" w labels offset 0,-1, \
    "pstar=0.3_vs_nstar" using (0.075):2:2 title "" w labels offset 4,0, \
    "pstar=0.3_vs_nstar" using (0.075):4:4 title "" w labels offset 0,1
    
#call "gif_export.plt" "quantile_with_mean_overlayed.gif"
call "eps_export.plt" "figure_7.eps"
call "pdf_export.plt" "figure_7.pdf"
