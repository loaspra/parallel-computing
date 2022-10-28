set terminal png
set output 'ej03a.png'
set log x
set log y
set xlabel 'np'
set ylabel 'T (ms)'
set xtics (1,2,4,8,16,32,64,128)
set title 'Cálculo de PI, Tiempo de ejecución vs np'
set key top right 

plot 'ej03_res.txt' using 1:2 w l title "10^2", '' u 1:3 w l title "10^3", '' u 1:4 w l title "10^4",'' u 1:5 w l title "10^5", '' u 1:6 w l title "10^6"


set output 'ej03b.png'
unset log x
unset log y
set ylabel 'Speedup'
set xrange[1:64]
set title 'Cálculo de PI, Speedup vs np'
plot 'ej03_res.txt' u 1:(10/1.3*0.038438/$4) w l title "10^4" ,'' u 1:(100/1.3*0.038438/$5) w l title "10^5" ,'' u 1:(1000/1.3*0.038438/$6) w l title "10^6" , '' u 1:1 w l title "S=p"


set output 'ej03c.png'
set yrange[0:2]
set ylabel 'Eficiencia'
f=0.038438*7*1.3
set title 'Cálculo de PI, Eficiencia vs np'
plot 'ej03_res.txt' u 1:(f/$4/$1) w l title "10^4" ,'' u 1:(10*f/$5/$1) w l title "10^5" ,'' u 1:(100*f/$6/$1) w l title "10^6" , '' u 1:($2/$2) w l title "E=1"

set output 'ej03d.png'
#set log x
set ylabel 'FLOPs'
set xrange[1:64]
unset yrange
set title 'Cálculo de PI, FLOPs vs np'
f=7
plot 'ej03_res.txt' u 1:(f*10000/$4) w l title "10^4" ,'' u 1:(f*100000/$5) w l title "10^5" ,'' u 1:(f*1000000/$6) w l title "10^6", '' u 1:($1*200000) w l title "S=p" 


