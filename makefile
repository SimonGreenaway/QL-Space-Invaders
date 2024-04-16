sprite:	sprite.o image.o  spritePlot.o
	qld -lm -o sprite sprite.o image.o  spritePlot.o

sprite.o:	sprite.c image.h 
		@echo $(PATH)
		qcc -O -o sprite.o -c sprite.c

spritePlot.o:	spritePlot.c image.h 
		qcc -O -o spritePlot.o -c spritePlot.c

libimage.a:	image.o
		qdos-ar -rc libimage.a image.o

image.o:	image.c image.h
		qcc -O -o image.o -c image.c
		#qcc -O -S image.c

clean:
	rm -f image.o screen.o libimage.a interrupt.o sprite.o invaders.img invaders.zip image.s invaders.mdv inv

cleaner:	clean
	rm -f sprite

deploy:	sprite logo.scr moon.scr
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_blb
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_blb
	cp ../Space_invaders_logo.scr logo.scr
	cp ../moon.scr moon.scr
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp moon.scr /home/simon/emulators/ql/emulators/sQLux/flp1/moon_scr
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1

run:   	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.39 --RAMSIZE=300 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runjm:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JM.ROM --SPEED=0.75 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runjs:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JS.ROM --SPEED=0.75 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

runfast:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --RAMSIZE=512 --SPEED=10 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_'"

convert:   	deploy 
	cp font.lib /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_sprite,#8;'-d flp1_ -c'"
	cp ~/emulators/ql/emulators/sQLux/flp1_c86/*_blb .

bm:   	sprite
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp test.lib /home/simon/emulators/ql/emulators/sQLux/test_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_sprite,#1;'-bm'"

dist:	convert
	rm -f image.o screen.o libimage.a interrupt.o
	cp sprite /home/simon/emulators/ql/emulators/sQLux/flp1
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp LICENSE /home/simon/emulators/ql/emulators/sQLux/flp1/LICENSE
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 -b "LRESPR flp1_sigext_rext:EW flp1_zip,#1;'flp1_invaders_zip sprite invaders_blb font_blb logo_scr moon_scr LICENSE'"
	mv /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_zip invaders.zip
	qltools invaders.img -fdd invaders -W
	cp BOOT_flp1 BOOT
	cp logo.scr logo_scr
	qltools invaders.img -W BOOT sprite invaders_blb font_blb logo_scr LICENSE
	cp BOOT_mdv1 BOOT
	cp invaders.zip i.zip
	#zip i.zip -d logo.scr
	mdvtool create name invaders zip_import i.zip import BOOT write invaders.mdv 
	rm -f BOOT i.zip logo_scr

git:	cleaner
	git add .
	git commit

github:	git
	git push
	
