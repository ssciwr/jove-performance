# to update benchmark.png: update */benchmark.txt and run `gnuplot benchmark.plt`
set terminal png size 800, 600
set output "benchmark.png"
set title "Serial speed-up over baseline"
set yrange [0:8]
set xlabel "Commit number"
p 'h2o/benchmark.txt' u 1:(1900/$2) w lp t "H2O speed-up", \
'h3coh/benchmark.txt' u 1:(138468/$2) w lp t "H3COH speed-up", \

