all: unoptimized
unoptimized: unoptimized.c
	gcc -o $@ $@.c

all: subword_parallel
subword_parallel: subword_parallel.c
	gcc -march=native -o $@ $@.c

all: loop_unroll
loop_unroll: loop_unroll.c
	gcc -march=native -o $@ $@.c

all: blocking
blocking: blocking.c
	gcc -march=native -o $@ $@.c

all: open_parallel
open_parallel: open_parallel.c
	gcc -march=native -o $@ $@.c
