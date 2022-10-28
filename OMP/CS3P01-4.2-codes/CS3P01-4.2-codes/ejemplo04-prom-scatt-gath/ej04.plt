set terminal png
set output 'ej04.png'
set log x
set log y
set xlabel 'np'
set ylabel 'T (ms)'
set xtics (2,4,8,16,32)
set title 'Cálculo de Promedio, Tiempo de ejecución vs np'
set key top right 


plot 'ej04_res3.txt' using 1:2 w l title "Tcomm", '' u 1:3 w l title "Tcomp", '' u 1:($2+$3) title "Ttot"
#plot 'ej04_res2.txt' using 1:5 w l title "Tcomm", '' u 1:6 w l title "Tcomp", '' u 1:($5+$6) title "Ttot"

