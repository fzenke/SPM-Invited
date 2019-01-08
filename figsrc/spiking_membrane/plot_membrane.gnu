#!/usr/bin/gnuplot

set border 3 
set xtics out nomirror 
set ytics out nomirror 


unset key

# set xtics (0,0.1,0.2)
set xrange [0:0.8]


#  color scheme
# line styles
set style line 1 lc rgb '#7FC97F' # pale green
set style line 2 lc rgb '#BEAED4' # pale purple
set style line 3 lc rgb '#FDC086' # pale orange
set style line 4 lc rgb '#FFFF99' # pale yellow
set style line 5 lc rgb '#386CB0' # blue
set style line 6 lc rgb '#F0027F' # magenta
set style line 7 lc rgb '#BF5B17' # brown
set style line 8 lc rgb '#666666' # grey

# palette
set palette maxcolors 8
set palette defined ( 0 '#7FC97F',\
    	    	      1 '#BEAED4',\
		      2 '#FDC086',\
		      3 '#FFFF99',\
		      4 '#386CB0',\
		      5 '#F0027F',\
		      6 '#BF5B17',\
			  7 '#666666' )


set term pdfcairo size 2.6,2.0
set out 'plot_membrane.pdf'




set lmargin screen 0.2
set multiplot 


# plot 1
set tmargin screen 0.95
set bmargin screen 0.9

set yrange [0:1]
unset ytics
unset xtics
set border 0
plot 'output.0.ras' using 1:2 with points pt 7 ps 0.5



# plot 2
set tmargin screen 0.85
set bmargin screen 0.5

set border 2
unset xtics
set ytics out nomirror
set ytics ("0" -60e-3, "1" -50e-3)
set yrange [-60e-3:-50e-3]
set ylabel 'U (a.u.)'
plot 'out.0.mem' using 1:2 with lines lw 2 title '',\
	 -50e-3 with lines dt 2 lc -1

unset ylabel



# plot 3
set tmargin screen 0.40
set bmargin screen 0.25
set border 1
set xtics out nomirror
set xtics (0, 0.4, 0.8)
set yrange [-0.5:3]
unset ytics
set xlabel 'Time (ms)'
unset colorbox
plot 'input.0.ras' using 1:2:2 with points pt 7 ps 0.5 lc "#505050" #palette

unset multiplot
