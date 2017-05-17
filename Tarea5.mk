GRAFICAS1 = histograma_1.pdf histograma_2.pdf canal_ionico_1.pdf canal_ionico_2.pdf 
GRAFICAS2 = histograma_3.pdf verosimilitud.pdf best_fit.pdf 

Resultados_hw5.pdf : Resultados_hw5.tex $(GRAFICAS1) $(GRAFICAS2)
	pdflatex $<

$(GRAFICAS1) : plots_canal_ionico.py caminata1.txt caminata2.txt
	python $<

caminata1.txt : canal_ionico.x Canal_ionico.txt Canal_ionico1.txt
	./$<

caminata2.txt : canal_ionico.x Canal_ionico.txt Canal_ionico1.txt
	./$<

canal_ionico.x : canal_ionico.c
	cc $< -lm -o $@

$(GRAFICAS2) : circuitoRC.py CircuitoRC.txt
	python $<
