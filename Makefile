CC=gcc
OUT=hprpn
LIB=-lm

all:
	${CC} -W -Wall -o build/${OUT} src/hprpn.c src/hpstack.c src/hpmath.c src/hpcommands.c src/hpcolors.c ${LIB}
debug:
	${CC} -o build/${OUT} -g src/hprpn.c src/hpstack.c src/hpmath.c src/hpcommands.c src/hpcolors.c ${LIB}
clean:
	rm build/hprpn
