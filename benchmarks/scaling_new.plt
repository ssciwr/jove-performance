# to update scaling.png: update */scaling_xeon.txt and run `gnuplot scaling_xeon.plt`
set terminal png size 800, 600
set output "scaling_new.png"
set title "Parallel speed-up over single core (new server: 2x26 cores)"
set yrange [0:26]
set xlabel "Threads"
set k t l
p x w l ls 0 t "perfect scaling", \
'h3coh/scaling_xeon_1socket.txt' u 1:(21211/$2) w lp t "H3COH: 1 socket (up to 26 cores used per cpu)", \
'h3coh/scaling_xeon_2sockets.txt' u 1:(21211/$2) w lp t "H3COH: 2 sockets (up to 13 cores used per cpu)"
