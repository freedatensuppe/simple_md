# Set up PDF output
set terminal pdfcairo enhanced color font 'DejaVu Sans,12' size 10cm,7cm

set output 'energy.pdf'
set xlabel "Step"
set ylabel "E / kcal/mol"

plot "output_energy.dat" u 0:1 w l notitle

set output 'temperature.pdf'
set xlabel "Step"
set ylabel "T / K"

plot "output_energy.dat" u 0:2 w l notitle

