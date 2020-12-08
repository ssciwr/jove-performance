# to update scaling.png: update */scaling_xeon.txt and run `gnuplot scaling_xeon.plt`
set terminal png size 800, 600
set output "scaling_xeon.png"
set title "Parallel speed-up over single core (on a 60 core / 120 thread machine)"
set yrange [0:64]
set xlabel "Threads"
set k t l
p x w l ls 0 t "perfect scaling", \
'h2o/scaling_xeon.txt' u 1:(1024/$2) w lp t "H2O", \
'h3coh/scaling_xeon.txt' u 1:(45748/$2) w lp t "H3COH"
