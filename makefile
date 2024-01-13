all:Q2.c Counting.c
	gcc -o Counting Counting.c
	gcc -o Q2 Q2.c
	sudo ./Q2
	python3 Histogram.py