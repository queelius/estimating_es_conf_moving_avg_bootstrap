# save gif files
# usage: call "gif_export.gp" "graph.gif"

set terminal push # save the current terminal settings
set terminal postscript enhanced monochrome dashed eps
set output "$0" # set the output filename to the first option
replot # repeat the most recent plot command
set output # restore output to interactive mode
set terminal pop # restore the terminal