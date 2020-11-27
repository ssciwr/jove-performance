# to update scaling.png: update */scaling_4.txt and run `gnuplot scaling.plt`
set terminal png size 800, 600
set output "scaling.png"
set title "Parallel speed-up over single core (on a 12 core / 24 thread machine)"
set yrange [0:15]
set xlabel "Threads"
set k t l
p x w l ls 0 t "perfect scaling", \
'h2o/scaling_4.txt' u 1:(372/$2) w lp t "H2O", \
'h3coh/scaling_4.txt' u 1:(16531/$2) w lp t "H3COH"
