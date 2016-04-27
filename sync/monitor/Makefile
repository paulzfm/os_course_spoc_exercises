MODEL 	= monitor.pml
SPIN  	= `which spin`

all: pan

pan: $(MODEL)
	$(SPIN) -a $(MODEL)
	$(CC) -o pan pan.c

clean:
	rm -f pan pan.* *.tmp

check:
	./pan

replay:
	$(SPIN) -t -p -l $(MODEL)
