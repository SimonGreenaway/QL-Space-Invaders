sprite:	sprite.o image.o 
	qld -lm -o sprite sprite.o image.o 

sprite.o:	sprite.c image.h 
		@echo $(PATH)
		qcc -O -o sprite.o -c sprite.c

libimage.a:	image.o
		qdos-ar -rc libimage.a image.o

image.o:	image.c image.h
		qcc -O -o image.o -c image.c
		#qcc -O -S image.c

clean:
	rm -f image.o screen.o libimage.a interrupt.o sprite.o invaders.img invaders.zip image.s invaders.mdv inv

cleaner:	clean
	rm -f sprite

deploy:	sprite
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_lib
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp ../Space_invaders_logo.scr logo.scr
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1

run:   	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.75 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runjm:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JM.ROM --SPEED=0.75 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runjs:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JS.ROM --SPEED=0.75 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runfast:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --RAMSIZE 131072 --SPEED=10 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

convert:   	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_ -c'"
	cp ~/emulators/ql/emulators/sQLux/flp1_c86/*_blb .

bm:   	sprite
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp ~/invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-bm'"

dist:	convert
	rm -f image.o screen.o libimage.a interrupt.o
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp LICENSE /home/simon/emulators/ql/emulators/sQLux/flp1/LICENSE
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 -b "LRESPR flp1_sigext_rext:EW flp1_zip,#1;'flp1_invaders_zip sprite invaders_blb font_blb logo_scr LICENSE'"
	mv /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_zip invaders.zip
	qltools invaders.img -fdd invaders -W
	cp BOOT_flp1 BOOT
	qltools invaders.img -W BOOT sprite invaders_blb font_blb logo_scr LICENSE
	cp BOOT_mdv1 BOOT
	mdvtool create name invaders zip_import invaders.zip import BOOT font_blb invaders_blb write invaders.mdv
	rm -f BOOT

git:	cleaner
	git add .
	git commit

github:	git
	git push
	
