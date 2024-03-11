sprite:	sprite.o image.o 
	qld -lm -o sprite sprite.o image.o

sprite.o:	sprite.c image.h
		@echo $(PATH)
		qcc -O -o sprite.o -c sprite.c

libimage.a:	image.o
		qdos-ar -rc libimage.a image.o

image.o:	image.c image.h
		qcc -O -o image.o -c image.c
		qcc -O -S image.c

clean:
	rm -f image.o screen.o libimage.a interrupt.o sprite.o invaders_floppy.img invaders.zip image.s

cleaner:	clean
	rm -f sprite

run:   	sprite
	cp invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_lib
	cp font.lib /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-s 0'"

runfast:   	sprite
	cp invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_lib
	cp font.lib /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=10 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-s 0'"

bm:   	sprite
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp ~/invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-bm'"

dist:	sprite
	rm -f image.o screen.o libimage.a interrupt.o
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cp font.lib /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 -b "LRESPR flp1_sigext_rext:EW flp1_zip,#1;'flp1_invaders_zip sprite invaders_lib font_lib'"
	mv /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_zip invaders.zip
	qltools invaders_floppy.img -fdd invaders -W
	qltools invaders_floppy.img -W BOOT sprite invaders.lib font.lib
	

