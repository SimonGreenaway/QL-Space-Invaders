
clean:
	rm -f image.o screen.o libimage.a interrupt.o sprite.o invaders_floppy.img invaders.zip image.s invaders.mdv

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
	mdvtool create name invaders zip_import invaders.zip write invaders.mdv
	

