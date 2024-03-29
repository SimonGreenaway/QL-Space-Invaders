#include "image.h"

#include <stdio.h>

void benchmark()
{
	library lib;
        unsigned int s;

        init();
        loadLibrary(&lib,"/home/simon/test5.lib","/home/simon/test5.csh",1);
        initBG();

        for(s=0;s<3;s++)
        {
                const int n=10;

                unsigned long t,c=0,pass;
                sprite sprite[8];

                for(c=0;c<8;c++)
                {
                        sprite[c].image[0]=&lib.images[s];
                        sprite[c].currentImage=0;
                        sprite[c].x=c;
                        sprite[c].y=c*sprite[c].image[0]->y;
                        sprite[c].draw=1;
                }

                for(pass=0;pass<2;pass++)
                {
                        for(c=0;c<8;c++) sprite[c].mask=pass;

                        t=*FRAMES+n*50;

                        while(t>*FRAMES)
                        {
                                unsigned int i,y=0,x=0;

                                BGtoScratch();

                                for(i=0;i<8;i++)
                                {
                                        if(y+lib.images[s].y>=256)
                                        {
                                                y=0;
                                                x+=lib.images[s].x*2+16;
                                        }

                                        x++;

                                        spritePlot(&sprite[i]);

                                        y+=lib.images[s].y;

                                        c++;
                                }

                                showScratch(0,256);
                        }

                        showScratch(0,256);

                        printf("%c %d x %d -> %d\n",pass==1?'M':' ',lib.images[s].x*4,lib.images[s].y,c);
                        initBG();
                }
        }
}

