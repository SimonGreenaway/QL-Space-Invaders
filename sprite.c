#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <qdos.h>

#include "image.h"

struct library lib;	// Image library
struct library font;	// Image library

//int sprite=0;

#define SPRITESX 11			// Number of invaders in a row
#define SPRITESY 5			// Number of invader rows
#define SPRITES (SPRITESX*SPRITESY)	// Total number of invaders
#define MAXBULLETS 4

#define FRAMES ((unsigned short *)163886)	// Location of frame counter

struct sprite sprites[SPRITES],bullets[3];	// Invader sprites
int maxBulletCount=1,bulletCount=0;

struct sprite player,ufo,player_bullet;	// Other sprites
int scores[3]={0,0,0};			// Player scores
int invaderScores[5]={30,20,20,10,10};

unsigned int invaders=SPRITES;		// Number of sprites alive

void printCharAt(unsigned int x,unsigned int y,char c)
{
	struct sprite s;

	if(c-33>=font.n)
	{
		printf("Font error: %d>=%d\n",c-33,font.n);
		exit(1);
	}

	s.x=x; s.y=y;
	s.image[0]=&font.images[c-33];
	s.currentImage=0;

	spritePlot(&s);
}

void printAt(unsigned int x,unsigned y,char *s)
{
	while(*s!=0)
	{
		if(*s!=32) printCharAt(x,y,*s);

		s++;
		x+=6;
	}
}

int keysleep(unsigned int frames)
{
	unsigned int target=*FRAMES+frames;

	while(*FRAMES<target)
	{
		unsigned int key=keyrow(-1);

		if(key) return key;
	}

	return 0;
}

int slowPrintAt(unsigned int x,unsigned y,char *s)
{
	while(*s!=0)
	{

		unsigned int frames=*FRAMES;

		if(keyrow(1)) return 1;

		if(*s!=32) printCharAt(x,y,*s);

                showScratch(0,256);

		s++;
		x+=6;

		while(frames+10>*FRAMES);

	}

	return 0;
}

///////////////////////////////
// Handle keyboard commands. //
///////////////////////////////

void handleKeys()
{
	int key=keyrow(1);	// Read the bottom row of the keyboard

        if(key)		// If a key was pressed
        {
                if((key==2)&&(player.x>0)) player.x-=2;		// Move left
                else if((key==16)&&(player.x<256-player.image[0]->x)) player.x+=2;	// Move right
                else if((key==64)&&(player_bullet.y<0))	// Fire (if not already fired)
                {
                        player_bullet.y=player.y;		// Set player bullets start location
                        player_bullet.x=player.x+3;
                }
                //else printf ("Pressed: %c Code: ; %d\n", key, key);
        }
}

//////////////////////////
// HandleInvaderBullets //
//////////////////////////

int handleInvaderBullets(unsigned int frames)
{
	int i;

	if(bulletCount>0) for(i=0;i<maxBulletCount;i++)
	{
	        if((bullets[i].y>-1)&&(bullets[i].timer>=frames))	// Fired?
	        {
			bullets[i].timer+=bullets[i].timerDelta;
	       	        bullets[i].y+=8;	// Move up
			bullets[i].currentImage=1-bullets[i].currentImage;

			if(bullets[i].y>=255-8)	// Reached the bottom
	              	{
				if((bullets[i].x>=player.x)&&(bullets[i].x<player.x+16))
				{
					bullets[i].currentImage=4;
					spritePlot(&bullets[i]);
					bullets[i].currentImage=0;
					return 1;
				}

				bullets[i].y=++bullets[i].y&4;
				bulletCount--;
	       		}
	              	else
			{

				if(bullets[i].y>-1) spritePlot(&bullets[i]);	// Draw bullet if still active
			}
		}
	}

	return 0;
}

////////////////////////////////
// HandlePlayerBullet         //
//                            //
// returns: 1 - wave complete //
////////////////////////////////

int handlePlayerBullet()
{
        if(player_bullet.y>-1)	// Fired?
        {
       	        player_bullet.y-=8;	// Move up

		if(player_bullet.y==8)	// Reached the top
              	{
			// Explosion!!!

			player_bullet.currentImage++;
			player_bullet.x=3;
			spritePlot(&player_bullet);
                     	player_bullet.currentImage--;

			player_bullet.y=-1;
       		}
              	else
		{
			unsigned int i;

			for(i=0;i<SPRITES;i++)
			{
				if((sprites[i].x-3<player_bullet.x)
				&&(sprites[i].x+9>player_bullet.x)
				&&(sprites[i].y<=player_bullet.y)
				&&(sprites[i].y+8>=player_bullet.y))
				{
					unsigned int newDelta=(50*--invaders)/SPRITES;
					if(invaders==0) return 1;	// Wave over!

					if(newDelta<sprites[i].timerDelta)
					{
						unsigned int j;

						for(j=0;j<SPRITES;j++) sprites[j].timerDelta=newDelta;
					}

					// Set up explosion at the invader's locations

					player_bullet.currentImage++;
					player_bullet.x=sprites[i].x+3;
					player_bullet.y=sprites[i].y;

					sprites[i].y=-1;	

					spritePlot(&player_bullet);

                     			player_bullet.currentImage--;

					player_bullet.y=-1;

					scores[0]+=invaderScores[i/SPRITESX];
					
					break;	// Can only hit one thing!
				}
			}

			if(player_bullet.y>-1) spritePlot(&player_bullet);	// Draw bullet if still active
		}
	}

	return 0;	// Wave still ongoing
}

///////////////////////////////
// handleInvaders            //
//                           //
// returns: 1 - invaders win //
//          0 - still going! // 
///////////////////////////////

int handleInvaders()
{
	unsigned short frames=*FRAMES;
	unsigned int i,bounce=0;

        for(i=0;i<SPRITES;i++)
        {
		if(sprites[i].y>-1)	// Sprite alive?
		{
			if(sprites[i].timer<=frames)	// Time to move?
			{
				sprites[i].x+=sprites[i].dx;	// Move invader
	
		                sprites[i].currentImage=1-sprites[i].currentImage;	// Change image for animation
	
				sprites[i].timer=frames+sprites[i].timerDelta;	// Set up timer for next movement 
	
				if((sprites[i].x<=0)||(sprites[i].x+16>=255)) bounce=1;	// Check for edge hit

				if((bulletCount<maxBulletCount)&&((rand()&31)==0))
				{
					unsigned int j;

					for(j=0;j<maxBulletCount;j++)
					{
						if(bullets[j].y==-1)
						{
							bulletCount++;

							bullets[j].y=sprites[i].y+8;
							bullets[j].x=sprites[i].x+4;
							bullets[j].timer=frames;
							break;
						}
					}
				}
			}
	
			spritePlot(&sprites[i]);	// Draw invader
		}
        }

	if(bounce)	// Move the invaders down and reverse direction
	{
                for(i=0;i<SPRITES;i++)
                {
                        struct sprite *s=&sprites[i];

			if(s->y>-1)	// Is sprite alive?
			{
	                        s->dx=-s->dx;	// Reverse direction
        	                s->y+=8;	// Move invader down

                	        // Game over?
                        	if(s->y>=player.y)  return 1;
			}
                }
	}

	return 0;
}

///////////////
// handleUFO //
///////////////

void handleUFO(unsigned int frames)
{
	if(ufo.x==-1)	// No ufo moving?
        {
		// TODO: Convert to timer?

		unsigned int r=rand(); // Get a random integer

                if((r&127)==0)		// Every 128 frames fire a UFO
                {
                        ufo.x=(r&256)?0:255-ufo.image[0]->x;	// Use a random bit for side to start on
			ufo.dx=(ufo.x==0)?4:-4;		//  direction depends on start location
			ufo.timer=0;
			ufo.timerDelta=5;		// Move every 5 frames
                }
        }
        else
        {

		if(ufo.timer<frames) // Is it time to move?
		{
			ufo.x+=ufo.dx;		// Move

       	        	if((ufo.x<=0)||(ufo.x+ufo.image[0]->x>=255))	// Reached other end?
			{
				ufo.x=-1;	// Switch off the UFO
				return;
			}

			ufo.timer=frames+ufo.timerDelta;	// Set the next time to run
		}

                spritePlot(&ufo);	// Draw the UGO
       }
}

void setupBG(unsigned int lives,unsigned int bases)
{
        unsigned int i;
        char buffer[80];
        struct sprite base;

        clsAll();

        sprintf(buffer,"%d",lives); printAt(8,256-7,buffer);
        printAt(50,0,"SCORE<1> HI-SCORE SCORE<2>");
        printAt(150,256-7,"CREDIT 01");

        if(bases) for(i=0;i<4;i++)
        {
                struct sprite s;

                s.image[0]=&lib.images[26];
                s.currentImage=0;
                s.x=i*48+32; s.y=256-16-13-32;

                spritePlot(&s);
        }

        base.image[0]=&lib.images[8];
        base.currentImage=0;
        base.y=256-8;
        base.x=24;

        for(i=0;i<lives-1;i++)
        {
                spritePlot(&base);
                base.x+=16;
        }

        base.image[0]=&lib.images[28];
        base.y--;

        for(i=0;i<256;i+=32)
        {
                base.x=i;
                //spritePlot(&base);
        }

        showScratch(0,256);
        initBG();
}

//////////////////
// IntroScreens //
//////////////////

void introScreens()
{
	char s[80];

	clsAll();
	setupBG(6,0);


	while(1)
	{
		BGtoScratch();
		printAt(92,100,"INSERT  COIN"); showScratch(0,256);
		if(slowPrintAt(80,140,"<1 OR 2 PLAYERS>")) return;
		if(slowPrintAt(80,140+24,"*1 PLAYER  1 COIN")) return;
		if(slowPrintAt(80,140+48,"*2 PLAYERS 2 COINS")) return;

		if(keysleep(100)) return;

		BGtoScratch(); showScratch(0,256);

		if(slowPrintAt(120,70,"PLAY")) return;
		if(slowPrintAt(90,100,"SPACE INVADERS")) return;

		if(keysleep(50)) return;

		printAt(80,130,"*SCORE ADVANCE TABLE*");
		ufo.x=100; ufo.y=150;
		ufo.image[0]=&lib.images[29];
		spritePlot(&ufo); ufo.image[0]=&lib.images[7]; ufo.y=-1;

		sprites[0].x=104; sprites[0].y=170; spritePlot(&sprites[0]);
		sprites[SPRITES/2].x=103; sprites[SPRITES/2].y=190; spritePlot(&sprites[SPRITES/2]);
		sprites[SPRITES-1].x=103; sprites[SPRITES-1].y=210; sprites[SPRITES-1].image[0]=&lib.images[30]; spritePlot(&sprites[SPRITES-1]); sprites[SPRITES-1].image[0]=&lib.images[0];

		showScratch(0,256);

		if(slowPrintAt(120,150,"=? MYSTERY")) return; 
		if(slowPrintAt(120,170,"=30 POINTS")) return; 
		if(slowPrintAt(120,190,"=20 POINTS")) return; 
		if(slowPrintAt(120,210,"=10 POINTS")) return; 

		if(keysleep(500)) return;
	}
}

//////////
// game //
//////////

int play()
{
	scores[0]=scores[1]=0;

	#ifdef DEBUG
	puts("Main loop start");
	#endif

	while(1)
	{
		char s[80];

		unsigned short frames=*FRAMES;

		#ifdef DEBUG
		puts("Loop");
		#endif

		BGtoScratch();

		#ifdef DEBUG
		puts("Scores");
		#endif

		sprintf(s,"%04d     %04d     %04d",scores[0],scores[2],scores[1]);
		printAt(64,16,s);	

		#ifdef DEBUG
		puts("Keys");
		#endif

		handleKeys();
		if(handlePlayerBullet()) return 0; // LEVEL CLEARED!

	        spritePlot(&player);

		#ifdef DEBUG
		puts("Invaders");
		#endif

		if(handleInvaders()) return 2; // GAME OVER!
		handleUFO(frames);

		if(handleInvaderBullets(frames))
		{
	        	showScratch(0,256);
			return 1; // LOSE A LIFE!
		}

		showScratch(0,256);
	}

	if(scores[0]>scores[2]) scores[2]=scores[0];
	if(scores[1]>scores[2]) scores[2]=scores[1];
}

///////////////////
// setupInvaders //
///////////////////

void setupInvaders()
{
	unsigned int i;

	for(i=0;i<SPRITES;i++)
        {
		int x=(i%11),y=i/11,s=y==0?2:(y<3?4:0);

                sprites[i].image[0]=&lib.images[s];
                sprites[i].image[1]=&lib.images[s+1];
                sprites[i].currentImage=0;

                sprites[i].x=x*16+(y==0?1:0)+1;
                sprites[i].y=y*16+48;

                sprites[i].dx=1;
                sprites[i].dy=0;

                sprites[i].timer=0;
                sprites[i].timerDelta=50;
        }

}

//////////////
// mainloop //
//////////////

void mainLoop()
{

	scores[2]=0; // Hi-score

	while(1)
	{
		unsigned int lives=7;

		introScreens();

		while(lives>0)
		{
			setupBG(lives,1); 

			setupInvaders();

			switch(play())
			{
				case 0: // Reset vaders
					break;
				case 1: lives--; break;
				case 2: lives=0; break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int s;
	int bm=0;

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-bm")==0) bm=1;
	}


	if(!bm)
	{
		int i;

		init();

		loadLibrary(&lib,"invaders_lib",1);
		loadLibrary(&font,"font_lib",1); 

 		if(lib.n==0)
 		{
 			puts("Error: Cannot find 'sprites_lib'");
 			exit(1);
 		}

		
		for(i=0;i<SPRITES;i++)
		{
			int x=(i%11),y=i/11,s=y==0?2:(y<3?4:0);

			sprites[i].image[0]=&lib.images[s];
			sprites[i].image[1]=&lib.images[s+1];
			sprites[i].currentImage=0;

			sprites[i].x=x*16+(y==0?1:0)+1;
			sprites[i].y=y*16+48;
			
			sprites[i].dx=1;
			sprites[i].dy=0;

			sprites[i].timer=0;
			sprites[i].timerDelta=50;
		}

		for(i=0;i<MAXBULLETS;i++)
		{
			bullets[i].x=0; bullets[i].y=-1;
			bullets[i].dx=0; bullets[i].dy=0;

			bullets[i].image[0]=&lib.images[16];
			bullets[i].image[1]=&lib.images[9];
			bullets[i].image[2]=&lib.images[17];
			bullets[i].image[3]=&lib.images[13];
			bullets[i].image[4]=&lib.images[18];

			bullets[i].currentImage=0;
		}

		scores[0]=scores[1]=0;

		player.image[0]=&lib.images[8];
		player.currentImage=0;
		player.x=(256-player.image[0]->x)/2;
		player.y=256-player.image[0]->y-24;

		player_bullet.image[0]=&lib.images[12];
		player_bullet.image[1]=&lib.images[15];
		player_bullet.currentImage=0;
		player_bullet.x=0;
		player_bullet.y=-1;

		ufo.image[0]=&lib.images[7];
		ufo.currentImage=0;
		ufo.x=-1;
		ufo.y=32;


		mainLoop();
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
