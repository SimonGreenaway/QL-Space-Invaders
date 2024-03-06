#include <qdos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <qdos.h>

#include "image.h"

struct library lib;

int sprite=0,perSecond=10000;

#define SPRITES (11*5)

struct sprite sprites[SPRITES];
struct sprite player,ufo,player_bullet;

int do_something()
{
	int i,bounce,z;

    	int key=keyrow(1);

	if(key)
	{

		if((key==2)&&(player.x>0)) player.x-=2;
		else if((key==16)&&(player.x<256-player.image[0]->x)) player.x+=2;
		else if((key==64)&&(player_bullet.y<0))
		{
			player_bullet.y=255-15;
			player_bullet.x=player.x+4;
		}
		//else printf ("Pressed: %c Code: ; %d\n", key, key);
	}

	BGtoScratch();

	if(player_bullet.y>-1)
	{
		player_bullet.y-=8;

		if(player_bullet.y==0)
		{
			player_bullet.currentImage++;
			player_bullet.x-=3;
			spritePlot(&player_bullet);
			player_bullet.currentImage--;
		}
		else if(player_bullet.y>-1) spritePlot(&player_bullet);
	}

	spritePlot(&player);


	bounce=0;

	for(i=0;i<SPRITES;i++)
	{
		if((sprites[i].x<=0)||(sprites[i].x+16>=255))
		{
			bounce=1; break;
		}
	}

	if(bounce)
	{
		for(i=0;i<SPRITES;i++)
		{
			struct sprite *s=&sprites[i];

			s->dx=-s->dx;
			s->y+=8;

			// Game over?
			if(s->y+s->image[s->currentImage]->y>=255)  return 1;
		}
	}

	for(i=0;i<SPRITES;i++)
	{
		sprites[i].x+=sprites[i].dx;
		//sprites[i].y+=sprites[i].dy;

		sprites[i].currentImage=1-sprites[i].currentImage;
		spritePlot(&sprites[i]);
	}

	if(ufo.x==-1)
	{
		unsigned int r=rand();

		if((r&31)==0)
		{
			ufo.x=(r&256)?0:255-ufo.image[0]->x;
			ufo.dx=(ufo.x==0)?4:-4;
		}
	}
	else
	{
		ufo.x+=ufo.dx;

		spritePlot(&ufo);

		if((ufo.x<=0)||(ufo.x+ufo.image[0]->x>=255)) ufo.x=-1;
	}

	showScratch(0,256);

	return 0;
}

void timeLoop(unsigned char perSecond,unsigned int delay,int (*do_something)())
{
	while(1)
	{
		unsigned long t=mt_rclck(),c=0,d=0;

		while(mt_rclck()==t)
		{
			if((c++%delay)==0)
			{
				if((*do_something)()) return;	
				d++;
			}
		}

		if(d!=perSecond) delay=(d*delay)/perSecond;
	}
}

void binPrint(unsigned int i,unsigned char d);

int main(int argc, char *argv[])
{
	int s;
	int bm=0;

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-bm")==0) bm=1;
		else if(strcmp(argv[s],"-s")==0)
			sprite=atoi(argv[++s]);
		else if(strcmp(argv[s],"-p")==0)
			perSecond=atoi(argv[++s]);
		else 
		{
			printf("Usage: sprite [-bm] [-s spritenum] [-p persecond]\n");
			exit(0);
		}
	}


	if(!bm)
	{
		int i;

		init();

		loadLibrary(&lib,"sprites_lib",1);

 		if(lib.n==0)
 		{
 			puts("Error: Cannot find 'flp1_sprites_lib'");
 			exit(1);
 		}

		cls();

		for(i=0;i<SPRITES;i++)
		{
			int x=(i%11),y=i/11,s=y==0?2:(y<3?4:0);

			sprites[i].image[0]=&lib.images[s];
			sprites[i].image[1]=&lib.images[s+1];
			sprites[i].currentImage=0;

			sprites[i].x=x*20+(y==0?1:0)+1;
			sprites[i].y=y*20+10;
			
			sprites[i].dx=1;
			sprites[i].dy=0;

			sprites[i].timer=0;
		}

		for(i=0;i<4;i++)
		{
			struct sprite s;

			s.image[0]=&lib.images[6];
			s.currentImage=0;
			s.x=i*48+32; s.y=256-32-16;

			spritePlot(&s); 
		}

		player.image[0]=&lib.images[8];
		player.currentImage=0;
		player.x=(256-player.image[0]->x)/2;
		player.y=256-player.image[0]->y;

		player_bullet.image[0]=&lib.images[12];
		player_bullet.image[1]=&lib.images[11];
		player_bullet.currentImage=0;
		player_bullet.x=0;
		player_bullet.y=-1;

		ufo.image[0]=&lib.images[7];
		ufo.currentImage=0;
		ufo.x=-1;
		ufo.y=0;

		showScratch(0,256);
		initBG();
		timeLoop(perSecond,0,do_something);
		exit(0);
	}

	init();
	loadLibrary(&lib,"/home/simon/test5.lib",1);
	initBG();

	for(s=0;s<3;s++)
	{
		unsigned long t,c=0;
		struct sprite sprite[8];

		for(c=0;c<8;c++)
		{
			sprite[c].image[0]=&lib.images[s];
			sprite[c].currentImage=0;
			sprite[c].x=c;
			sprite[c].y=c*sprite[c].image[0]->y;
			sprite[c].timer=0;
		}

		t=mt_rclck();
		while(mt_rclck()==t);
		t=mt_rclck()+10;
	
		while(mt_rclck()<t)
		{
			unsigned int i,y=0,x=0,ymin=1024,ymax=0;

			BGtoScratch();

			for(i=0;i<8;i++)
			{
				unsigned char ox=x,oy=y;

				if(y+lib.images[s].y>=256)
				{
					y=0;
					x+=lib.images[s].x*2+16;
				}

				x++;

				spritePlot(&sprite[i]);

				if(y>ymax) ymax=y;
				else if(y<ymin) ymin=y;

				y+=lib.images[s].y;
			}

			showScratch(ymin,ymax+lib.images[s].y);

			c+=8;
		}

		showScratch(0,256);
		printf("%d x %d\t-> %d\n",lib.images[s].x*4,lib.images[s].y,c);
		initBG();
	}
}

void plotTest()
{	
	short y;

	for(y=0;y<8;y++)
	{
		short x;

		for(x=0;x<8;x++)
		{
			unsigned char a;

			for(a=0;a<32;a++)
			{
				unsigned char b; for(b=0;b<16;b++)
				{
					plot(x*32+a,y*16+b,y);
				}
			}
		}
	}
}
