# to update scaling.png: update */scaling_hgs.txt and run `gnuplot scaling.plt`
set terminal png size 800, 600
set output "scaling_hgs.png"
set title "Parallel speed-up over single core (2 x 26-core/56-thread Xeon Gold 6230R)"
set xrange [0:104]
set yrange [0:60]
set xlabel "Threads"
set k t l
p x w l ls 0 lw 2 t "perfect scaling", \
52 w l ls 0 t "52x speed-up", \
'h2o/scaling_hgs.txt' u 1:(1021/$2) w lp t "H2O (best of 20 runs)", \
'h3coh/scaling_hgs.txt' u 1:(38324/$2) w lp t "H3COH", \
'c14h10/scaling_hgs.txt' u 1:(15449864/$2) w lp t "C14H10", \
'porphyrin/scaling_hgs.txt' u 1:(28076236/$2) w lp t "porphyrin", \
