sprite:	sprite.o image.o interrupt.o
	qld -lm -o sprite sprite.o interrupt.o image.o

sprite.o:	sprite.c image.h
		@echo $(PATH)
		qcc -O -o sprite.o -c sprite.c

libimage.a:	image.o
		qdos-ar -rc libimage.a image.o

image.o:	image.c image.h
		qcc -O -o image.o -c image.c
		qcc -O -S image.c

interrupt.o:	interrupt.s
		as68 -o interrupt.o interrupt.s

clean:
	rm -f image.o screen.o libimage.a sprite interrupt.0

run:   	sprite
	cp sprite sprites.lib /home/simon/emulators/ql/emulators/sQLux/flp1
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1"

runfast:   	sprite
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1"

bm:   	sprite
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-bm'"
