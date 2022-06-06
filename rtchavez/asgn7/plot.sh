#!/bin/bash

make clean && make

rm -f /tmp/insert.dat
rm -f /tmp/batcher.dat
rm -f /tmp/heap.dat
rm -f /tmp/quick.dat

for x in {10..1000}
do

    insert_y=$(./sorting -i -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    batcher_y=$(./sorting -b -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    heap_y=$(./sorting -h -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    quick_y=$(./sorting -q -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)

    printf "%s %d\n" "$x" "$insert_y" >> /tmp/insert.dat
    printf "%s %d\n" "$x" "$batcher_y" >> /tmp/batcher.dat
    printf "%s %d\n" "$x" "$heap_y" >> /tmp/heap.dat
    printf "%s %d\n" "$x" "$quick_y" >> /tmp/quick.dat
done
#small arrays of moves
gnuplot << END
    set terminal pdf
    set output "small.pdf"
    set key outside top right
    set title "Moves for Small Arrays"
    set xlabel "Elements"
    set ylabel "Moves"
    set log x
    set log y
    plot "/tmp/insert.dat" with lines title 'Insertion Algorthims',  "/tmp/batcher.dat" with lines title 'Batcher Algorthim', "/tmp/heap.dat" with lines title 'Heap Algorthim', "/tmp/quick.dat" with lines title 'Quick Algorthim'
END

rm -f /tmp/insert.dat
rm -f /tmp/batcher.dat
rm -f /tmp/heap.dat
rm -f /tmp/quick.dat

for x in {10..10000}
do

    insert_y=$(./sorting -i -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    batcher_y=$(./sorting -b -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    heap_y=$(./sorting -h -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)
    quick_y=$(./sorting -q -n $x -p 0 |cut -d":" -f 3 |cut -d"," -f 1)

    printf "%s %d\n" "$x" "$insert_y" >> /tmp/insert.dat
    printf "%s %d\n" "$x" "$batcher_y" >> /tmp/batcher.dat
    printf "%s %d\n" "$x" "$heap_y" >> /tmp/heap.dat
    printf "%s %d\n" "$x" "$quick_y" >> /tmp/quick.dat
done
#large arrays of moves
gnuplot << END
    set terminal pdf
    set output "large.pdf"
    set key outside top right
    set title "Moves for Large Arrays"
    set xlabel "Elements"
    set ylabel "Moves"
    set log x
    set log y
    plot "/tmp/insert.dat" with lines title 'Insertion Algorthims',  "/tmp/batcher.dat" with lines title 'Batcher Algorthim', "/tmp/heap.dat" with lines title 'Heap Algorthim', "/tmp/quick.dat" with lines title 'Quick Algorthim'
END

rm -f /tmp/insert.dat
rm -f /tmp/batcher.dat
rm -f /tmp/heap.dat
rm -f /tmp/quick.dat

for x in {10..1000}
do

    insert_y=$(./sorting -i -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    batcher_y=$(./sorting -b -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    heap_y=$(./sorting -h -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    quick_y=$(./sorting -q -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)

    printf "%s %d\n" "$x" "$insert_y" >> /tmp/insert.dat
    printf "%s %d\n" "$x" "$batcher_y" >> /tmp/batcher.dat
    printf "%s %d\n" "$x" "$heap_y" >> /tmp/heap.dat
    printf "%s %d\n" "$x" "$quick_y" >> /tmp/quick.dat
done

gnuplot << END
    set terminal pdf
    set output "small_compares.pdf"
    set key outside top right
    set title "Compares for Small Arrays"
    set xlabel "Elements"
    set ylabel "Compares"
    set log x
    set log y
    plot "/tmp/insert.dat" with lines title 'Insertion Algorthims',  "/tmp/batcher.dat" with lines title 'Batcher Algorthim', "/tmp/heap.dat" with lines title 'Heap Algorthim', "/tmp/quick.dat" with lines title 'Quick Algorthim'
END

rm -f /tmp/insert.dat
rm -f /tmp/batcher.dat
rm -f /tmp/heap.dat
rm -f /tmp/quick.dat

for x in {10..10000}
do

    insert_y=$(./sorting -i -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    batcher_y=$(./sorting -b -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    heap_y=$(./sorting -h -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)
    quick_y=$(./sorting -q -n $x -p 0 |cut -d":" -f 4 |cut -d"," -f 1)

    printf "%s %d\n" "$x" "$insert_y" >> /tmp/insert.dat
    printf "%s %d\n" "$x" "$batcher_y" >> /tmp/batcher.dat
    printf "%s %d\n" "$x" "$heap_y" >> /tmp/heap.dat
    printf "%s %d\n" "$x" "$quick_y" >> /tmp/quick.dat
done

gnuplot << END
    set terminal pdf
    set output "large_compares.pdf"
    set key outside top right
    set title "Compares for Large Arrays"
    set xlabel "Elements"
    set ylabel "Compares"
    set log x
    set log y
    plot "/tmp/insert.dat" with lines title 'Insertion Algorthims',  "/tmp/batcher.dat" with lines title 'Batcher Algorthim', "/tmp/heap.dat" with lines title 'Heap Algorthim', "/tmp/quick.dat" with lines title 'Quick Algorthim'
END
