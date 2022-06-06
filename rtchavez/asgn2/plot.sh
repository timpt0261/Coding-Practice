#!/usr/bin/env bash

# Example data is sent to /tmp/output.
cat > /tmp/output <<herestr
sqrt(1 - x^4),0.000000,1.000000,100
2,0.812163891034571
4,0.852988388966857
6,0.862714108378597
8,0.866720323920874
10,0.868814915051592
12,0.870069316562543
14,0.870889853274920
herestr

# Get the title from the output.
title=$(head -n 1 /tmp/output | awk -F, '{ print $1 }')

# Put all but first line of output in data file.
tail -n +2 /tmp/output > /tmp/data

# Plot the data, specifying that commas are used as the delimiter.
gnuplot <<EOF
    set terminal pdf
    set output "example.pdf"
    set datafile separator ","
    set xlabel "x"
    set ylabel "y"
    set title "$title"
    plot "/tmp/data" with linespoints
EOF

#!/usr/bin/env bash
rm /tmp/data.dat
./integrate -c -p -7 -q 7 -n 50 | awk 'NR>=10' | awk -F, 'function abs(x){return ((x < 0.0) ? -x : x
)} { root_pi=1.772453850905516; a=$2; x=(root_pi-a)/root_pi; print($1, "\t", x)}' > /tmp/data.dat
gnuplot <<EOF
set terminal png
set output "sample.png"
set xlabel "n"
set ylabel "relative error"
set style line 5 lt rgb "plum" ps 0.1 pt 6
set title "Relative error of exp(-x^2)"
plot "/tmp/data.dat" with linespoints ls 5 title ""
EOF
rm /tmp/data.dat
./integrate -c -p -7 -q 7 -n 50 | awk 'NR>=10' | awk -F, 'function abs(x){return ((x < 0.0) ? -x : x
)} { root_pi=1.772453850905516; a=$2; x=(root_pi-a); print($1, "\t", x)}' > /tmp/data.dat
gnuplot <<EOF
set terminal png
set output "absolute.png"
set xlabel "n"
set ylabel "absolute error"
set style line 5 lt rgb "plum" ps 0.1 pt 6
set title "Absolute  error of exp(-x^2)"
plot "/tmp/data.dat" with linespoints ls 5 title ""
EOF
