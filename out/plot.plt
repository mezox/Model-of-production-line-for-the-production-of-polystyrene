set terminal png size 1000,600
set autoscale y
set autoscale x
set key below
set xlabel "Čas (h)"
set ylabel "Počet plných síl"
set title "Vyťaženie síl za jeden mesiac pri počte 14 "
set output 'silo2.png'
plot "silo.txt" using 1:2 title "Plné silá v danom čase" with steps linewidth 3
unset autoscale x
set xrange ["0":"200"]
set xlabel "Číslo objednávky"
set ylabel "Doby spracovania objednávky (hodiny)"
set title "Doby spracovania objednávok za jeden mesiac pri použití 10 síl"
set output 'objednavky3.png'
plot "objednavky.txt" using 1:2 smooth frequency with boxes linewidth 3 title "Doby spracovania"
