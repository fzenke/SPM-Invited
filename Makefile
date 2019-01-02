all: bare_jrnl.pdf

%.pdf: %.tex
	pdflatex $<
