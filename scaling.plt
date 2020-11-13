# to update scaling.png: update scaling_x.txt and run `gnuplot scaling.plt`
set terminal png
set output "scaling.png"
set title "Parallel speed-up over single core"
set yrange [0:12]
set xlabel "Threads"
set k t l
p x w l ls 0 t "perfect scaling", \
'scaling_0.txt' u 1:(407/$2) w lp t "tsize", \
'scaling_1.txt' u 1:(404/$2) w lp t "npts", \
