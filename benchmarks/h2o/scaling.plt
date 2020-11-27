# to update scaling.png: update scaling_x.txt and run `gnuplot scaling.plt`
set terminal png size 800, 600
set output "scaling.png"
set title "H2O Parallel speed-up over single core (on a 12 core / 24 thread machine)"
set yrange [0:12]
set xlabel "Threads"
set k t l
p x w l ls 0 t "perfect scaling", \
'scaling_0.txt' u 1:(407/$2) w lp t "tsize", \
'scaling_1.txt' u 1:(404/$2) w lp t "npts", \
'scaling_2.txt' u 1:(381/$2) w lp t "tsize+npts", \
'scaling_3.txt' u 1:(403/$2) w lp t "tsize+npts/dynamic", \
'scaling_3a.txt' u 1:(403/$2) w lp t "tsize+npts/dynamic+bind", \
'scaling_4.txt' u 1:(372/$2) w lp t "tsize+npts/dynamic+bind+nocopies"
