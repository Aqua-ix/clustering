unset key
set xlabel "Attr. 1"
set ylabel "Attr. 2"
set xrange [-3:3]
set yrange [-3:3]
set size ratio -1
set output "overlap.pdf"
plot "test_1000_2.txt"
