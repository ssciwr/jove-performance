# to update benchmark.png: update benchmark.txt and run `gnuplot benchmark.plt`
set terminal png
set output "benchmark.png"
set title "Speed-up over baseline"
set yrange [0:6]
set xlabel "Commit number"
p 'benchmark.txt' u 1:(1900/$2) w lp t "speed-up"

