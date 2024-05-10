COPTS=-Os -fomit-frame-pointer -std=gnu9x -Wall

invaders:	invaders.o utils.o QL-sprites/libsprite.a
	rm -f invaders
	make -C QL-sprites
	qdos-gcc -o invaders invaders.o utils.o -LQL-sprites -lsprite

invaders.o:	invaders.c invaders.h utils.h
		qdos-gcc $(COPTS) -IQL-sprites -o invaders.o -c invaders.c

utils.o:	utils.c invaders.h utils.h
		qdos-gcc $(COPTS) -IQL-sprites -o utils.o -c utils.c

spritePlot.o:	spritePlot.c image.h 
		qdos-gcc $(COPTS) -o spritePlot.o -c spritePlot.c

image.o:	image.c image.h
		qdos-gcc $(COPTS) -o image.o -c image.c
		#qcc -O -S image.c

system_variables.o:	system_variables.c system_variables.h
		qdos-gcc $(COPTS) -o system_variables.o -c system_variables.c

QL-sprites/libsprite.a:
	make -C QL-sprites

clean:
	rm -f screen.o interrupt.o invaders.o libsprite.a spritePlot.o system_variables.o image.o utils.o .bash_history
	make -C QL-sprites clean

cleaner:	clean
	rm -f invaders invaders.img invaders.zip invaders.mdv invaders.hfe

deploy:	invaders logo.scr moon.scr
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_blb
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_blb
	cp ../Space_invaders_logo.scr logo.scr
	cp ../moon.scr moon.scr
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp moon.scr /home/simon/emulators/ql/emulators/sQLux/flp1/moon_scr
	cp invaders /home/simon/emulators/ql/emulators/sQLux/flp1
	cp BOOT_flp1 /home/simon/emulators/ql/emulators/sQLux/flp1/BOOT

run:   	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0.70 --RAMSIZE=896 --SOUND 8 -b "LRUN flp1_BOOT"

test:   invaders
	cp invaders /home/simon/emulators/ql/emulators/sQLux/flp1
	cp test.lib /home/simon/emulators/ql/emulators/sQLux/flp1/test_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1 -b "LRESPR flp1_sigext_rext:EW flp1_invaders,#1;'-t'"

runjm:	deploy
runjm:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JM.ROM --SPEED=10 --SOUND 8 -b "LRUN flp1_BOOT"

runjs:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --ROMDIR ~/emulators/ql/THE_DISTRIBUTION/qos/ROMs --SYSROM JS.ROM --SPEED=0.75 --SOUND 8 -b "LRUN flp1_BOOT"

runfast:	deploy
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=10 --SOUND 8 -b "LRUN flp1_BOOT"

convert:   	deploy 
	cp font.lib /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp invaders.lib /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 --SOUND 8 -b "OPEN #8,con_512x256a0x0_0:CLS #8:INK #8,4:LRESPR flp1_sigext_rext:EW flp1_invaders,#8;'-d flp1_ -c'"
	cp ~/emulators/ql/emulators/sQLux/flp1_c86/*_blb .

bm:   	invaders
	cp invaders /home/simon/emulators/ql/emulators/sQLux/flp1
	cp test.lib /home/simon/emulators/ql/emulators/sQLux/test_lib
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=1.0 -b "LRESPR flp1_sigext_rext:EW flp1_invaders,#1;'-bm'"

dist:	convert
	rm -f image.o screen.o libimage.a interrupt.o
	cp invaders /home/simon/emulators/ql/emulators/sQLux/flp1
	cp invaders_blb /home/simon/emulators/ql/emulators/sQLux/flp1_invaders_lib
	cp font_blb /home/simon/emulators/ql/emulators/sQLux/flp1/font_lib
	cp logo.scr /home/simon/emulators/ql/emulators/sQLux/flp1/logo_scr
	cp LICENSE /home/simon/emulators/ql/emulators/sQLux/flp1/LICENSE
	cd /home/simon/emulators/ql/emulators/sQLux && ./sqlux --SPEED=0 -b "LRESPR flp1_sigext_rext:EW flp1_zip,#1;'flp1_invaders_zip invaders invaders_blb font_blb logo_scr moon_scr LICENSE'"
	mv /home/simon/emulators/ql/emulators/sQLux/flp1/invaders_zip invaders.zip
	qltools invaders.img -fdd invaders -W
	cp BOOT_flp1 BOOT
	cp logo.scr logo_scr
	cp moon.scr moon_scr
	qltools invaders.img -W BOOT invaders invaders_blb font_blb logo_scr moon_scr LICENSE
	cp BOOT_mdv1 BOOT
	cp invaders.zip i.zip
	#zip i.zip -d logo.scr
	mdvtool create name invaders zip_import i.zip import BOOT write invaders.mdv 
	rm -f BOOT i.zip logo_scr moon_scr

git:	cleaner
	git add .
	git commit
	git push

github:	git
	git push
	
