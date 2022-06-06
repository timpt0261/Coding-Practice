#!/bin/bash

make clean && make all

rm -f /tmp/output.dat

#makes .dat file for plotting Collatz Sequence Lengths
for x in {10..10000}; do
    echo -n "$x "  >> /tmp/length.dat
    ./collatz -n $x | wc -l >> /tmp/length.dat

done

gnuplot <<END
    set terminal pdf
    set output "length.pdf"
    set title "Collatz Sequence Lengths"
    set xrange [0:10000]
    set yrange [0:300]
    set xlabel "n"
    set ylabel "length"
    set xtics 1000
    set ytics 50
    plot "/tmp/length.dat" with dots title ""
END

# makes .dat file that plots Max Collatz Sequence
for x in {2..10000}; do
    echo -n "$x "  >> /tmp/value.dat
    ./collatz -n $x | sort -r -g | head -n 1 >> /tmp/value.dat
done

gnuplot <<END
    set terminal pdf
    set output "max.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set xrange [0: 10000]
    set yrange [0: 100000]
    set xtics 1000
    set ytics 20000
    plot "/tmp/value.dat" with dots title ""
END

#makes .dat file that plots Collatz Sequence Length Histogram
for x in {2..10000}; do
    ./collatz -n $x | wc -l >> /tmp/histogram.dat
done

cat /tmp/histogram.dat |sort -r -g | uniq -c -d | sed 's/^\s*//' >> /tmp/histogram.dat

gnuplot <<END
    set terminal pdf
    set output "histogram.pdf"
    set title "Collatz Sequence Length Histogram"
    set xlabel "length"
    set ylabel "frequency"
    set xrange [0: 225]
    set yrange [0: 200]
    set xtics 25
    set ytics 20
    plot "/tmp/histogram.dat" using 2:1 with boxes title ""

END
