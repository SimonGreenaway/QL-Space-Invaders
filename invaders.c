#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <qdos.h>
#include <sms.h>

#include "QL-sprites/image.h"

#undef PROFILE
#define FPS

#ifdef PROFILE
#undef FPS
#endif

#define IMMORTAL

library lib,font;	// Image libraries

#define SPRITESX 11			// Number of invaders in a row
#define SPRITESY 5			// Number of invader rows
#define SPRITES (SPRITESX*SPRITESY)	// Total number of invaders
#define MAXBULLETS 4

#define WIDTH 224
#define XMIN ((256-WIDTH)>>1)
#define XMAX (XMIN+WIDTH)

char *drive="";
char *rom;
float qdos=-1;
int job=-1;

struct player
{
	sprite sprites[SPRITES];
	unsigned int newDelta,invaderCount,shotCount,score,lives,wave;
	int direction;

	unsigned char *bases;
};

struct player players[2],*currentPlayer=&players[0];

unsigned int credits=0,currentPlayerId,gameMode=0;
unsigned int sound=1;

sprite bullets[3];
unsigned char bulletTypes[3];	// Invader sprites
unsigned maxBulletCount=1,bulletCount=0,shotCount=0;

sprite player,ufo,player_bullet;	// Other sprites
unsigned int playerVisible;

unsigned int highScore=0;			// Player scores
int invaderScores[5]={30,20,20,10,10};
unsigned char ufoScores[]={10,05,05,10,15,10,10,05,30,10,10,10,05,15,10,05};
unsigned char ufoScorePointer=0;

unsigned int invaderSoundTimer;

#ifdef FPS
unsigned int fpsCounter,fpsTimer,fpsStart;
#endif

screen moon;

// Work out the x offset to print in the center of the screen

unsigned int xPrint(unsigned int chars)
{
	return XMIN+((XMAX-XMIN)-6*chars)>>1;
}

// Fast /10

unsigned int divu10(unsigned int n)
{
    unsigned q, r;

    q = (n >> 1) + (n >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 3;
    r = n - (((q << 2) + q) << 1);

    return q + (r > 9);
}

// Fast *10

unsigned int mul10(unsigned int z)
{
        return (z<<3)+(z<<1);
}

void scorePrint(char *c,unsigned int z)
{
        int a;
        unsigned int zz;
        
        for(a=3;a>=0;a--)
        {
                zz=divu10(z);
                c[a]='0'+(z-mul10(zz));
                z=zz;
        }
}

void printScores()
{
	char s[80],*sp=s;
	char p1[5],hs[5],p2[5];

	p1[4]=hs[4]=p2[4]='\0';

	scorePrint(p1,players[0].score);
	scorePrint(hs,highScore);
	scorePrint(p2,players[1].score);

	fill(SCREEN,48,48+8,0);
	sprintf(s,"%4s     %4s     %4s",p1,hs,p2);
	printAt(SCREEN,&font,xPrint(strlen(s)),16+32,s);	
}

void doHelp()
{
	// Show help

	cls(SCREEN);

	printAt(SCREEN,&font,xPrint(12),00,"HELP SCREEN");
	printAt(SCREEN,&font,50,30,"<C> - ADD A COIN");
	printAt(SCREEN,&font,50,55,"<1> - 1 PLAYER GAME");
	printAt(SCREEN,&font,50,80,"<2> - 2 PLAYER GAME");
	printAt(SCREEN,&font,50,105,"<S> - SOUND TOGGLE");
	//printAt(SCREEN,&font,50,130,"<P> - PAUSE GAME TOGGLE");
	printAt(SCREEN,&font,50,130," F1 - HELP");

	printAt(SCREEN,&font,xPrint(10),170,"THANKS TO:");
	printAt(SCREEN,&font,30,186,"GEORGIUS KONSTANTOPULOS (TESTING)");
	printAt(SCREEN,&font,30,196,"JB1ZZEL (TESTING & MOON BACKGROUND)");
	printAt(SCREEN,&font,30,206,"JOHN ENGDAHL (TESTING)");
	printAt(SCREEN,&font,30,216,"SILVERIO M RS, JOBDONE");
	printAt(SCREEN,&font,30,226,"   & STEPHEN USHER (TESTING)");
}

int keysleep(unsigned int frames)
{
	unsigned int target=getFrames()+frames;

	while(getFrames()<target)
	{
		if(keyrow(2)&8) // Coin key 'C' ?
		{
			credits++; 
			while(keyrow(2)&8) ;

			return 3;
		}

		if((keyrow(4)&8)&&(credits>0)) // Player 1 start '1' ?
		{
			gameMode=1;	
			return 1; // Player 1 start?
		}

		if((keyrow(6)&2)&&(credits>1)) // Player 2 start '2' ?
		{
			gameMode=2;
			return 2;  // Player 2 start?
		}
	}

	return 0;
}

int slowPrintAt(unsigned int x,unsigned y,char *s)
{
	unsigned key;

	while(*s!=0)
	{
		unsigned int frames=getFrames();

		// Coin key 'C' ?

		if(keyrow(2)&8)
		{
			credits++; 
			while(keyrow(2)&8) ;

			return 1;
		}

		if((keyrow(4)&8)&&(credits>0))
		{
			gameMode=1;	
			return 1; // Player 1 start?
		}

		if((keyrow(6)&2)&&(credits>1))
		{
			gameMode=2;
			return 2;  // Player 2 start?
		}

		if(*s!=32) printCharAt(SCREEN,&font,x,y,*s);

		s++;
		x+=6;

		while(frames+5>getFrames());
	}

	return 0;
}

///////////////////////////////
// Handle keyboard commands. //
///////////////////////////////

timer keyTimer;
int playerReload; 

void handleKeys(unsigned int frames)
{
	unsigned int key;

	if(!playerVisible)
	{
		if(player.timer.value>frames) return;

		playerVisible=1;	// Make player visible
		player.timer.value=frames;
		keyTimer.value=frames;

		spritePlot(SCREEN,&player);

		return;
	}

	if(frames>=keyTimer.value)
	{
		key=keyrow(1);	// Read the bottom row of the keyboard

		keyTimer.value+=keyTimer.delta;

        	if(key)		// If a key was pressed
		{
        	        if((key&2)&&(player.x>XMIN))
			{
				spriteClear(SCREEN,moon,&player);

				player.x--;	// Move left
				spritePlot(SCREEN,&player);
			}
                	else if((key&16)&&(player.x<XMAX-player.image[0]->x<<2))
			{
				player.draw=0;
				spriteClear(SCREEN,moon,&player);
				player.draw=1;

				player.x++;	// Move right
				spritePlot(SCREEN,&player);
			}

			if((key&64)&&(!player_bullet.active)&&playerReload)	// Fire (if not already fired)
                	{
				player_bullet.active=1;
	                        player_bullet.y=player.y-8;		// Set player bullets start location
        	                player_bullet.x=player.x+3;
				player_bullet.timer.value=frames;
				playerReload=0;
				shotCount++;
			}
		}
	
		if((key&64)==0) playerReload=1;

		if(keyrow(3)&8)
		{
			sound=1-sound;

			while(keyrow(3));
		}
	}

	/* Pause
	if(keyrow(4)&32)
	{
		while(keyrow(4)&32); 
		while((keyrow(4)&32)==0); 
		while(keyrow(4)&32); 
	}
	*/
}

//////////////////////////
// HandleInvaderBullets //
//////////////////////////

unsigned int reload;

/////////////////
// invaderFire //
/////////////////               

void setInvaderReload()         
{                            
        if(currentPlayer->score<=200) reload=getFrames()+30;
        else if(currentPlayer->score<=1000) reload=getFrames()+10;
        else if(currentPlayer->score<=2000) reload=getFrames()+9;
        else if(currentPlayer->score<=3000) reload=getFrames()+8;
        else reload=getFrames()+7;
}

int handleInvaderBullets(unsigned int frames)
{
	unsigned int i;

	if(bulletCount>0) for(i=0;i<maxBulletCount;i++)
	{
	        if((bullets[i].active)&&(bullets[i].timer.value<=frames))	// Fired?
	        {
			spriteClear(SCREEN,moon,&bullets[i]);	// Draw bullet if still active

			bullets[i].timer.value=frames+bullets[i].timer.delta;
	       	        bullets[i].y+=(currentPlayer->invaderCount<=8?5:4);
			bullets[i].currentImage=(bullets[i].currentImage+1)&3;

			if(bullets[i].y>=player.y)	// Reached the bottom
	              	{
				bullets[i].active=0;
				bulletCount--;

				setInvaderReload();
			
				#ifndef IMMORTAL	 
				if((bullets[i].x>=player.x)&&(bullets[i].x<player.x+16))
				{
					// Player hit!

					unsigned int j;

					
					for(j=0;j<10;j++)
					{			
						player.currentImage=1;
						spritePlot(SCREEN,&player);

						msleep(10);

						player.draw=0;
						spritePlot(SCREEN,&player);
						player.draw=1;

						player.currentImage=2;
						spritePlot(SCREEN,&player);
						msleep(10);

						player.draw=0;
						spritePlot(SCREEN,&player);
						player.draw=1;
					}

					player.currentImage=0;
					return 1;
				}
				#endif
	       		}
			else
			{
				if(peek(SCREEN,bullets[i].y+4,bullets[i].x)&0xAA00
				 ||peek(SCREEN,bullets[i].y+6,bullets[i].x)&0xAA00)
				{
					// Hit something!

					bullets[i].currentImage=4;
					bullets[i].mask=1;
					bullets[i].x-=2;
					spriteClear(SCREEN,moon,&bullets[i]);
	
					bullets[i].currentImage=0;
					bullets[i].mask=0;
					bullets[i].active=0;
					bulletCount--;
				}
			}
		}

		if(bullets[i].active)
		{
			spritePlot(SCREEN,&bullets[i]);	// Draw bullet if still active
		}
	}

	return 0;
}

//////////////////////////////////
// HandlePlayerBullet           //
//                              //
// returns: 1 - wave complete   //
//          0 - wave continues! //
//////////////////////////////////

int handlePlayerBullet(unsigned int frames)
{
	unsigned int i,j,skipped,hit=0;
	unsigned short pk;

        if((player_bullet.active)&&(player_bullet.timer.value<frames))
        {
                skipped=frames-player_bullet.timer.value+1;

                {
			player_bullet.draw=0;
			spriteClear(SCREEN,moon,&player_bullet);
			player_bullet.draw=1;

			for(i=0;i<skipped;i++) if(!hit)
			{
				player_bullet.y-=2;

				pk=peek(SCREEN,player_bullet.y+2,player_bullet.x+3);

      			        if(((pk&0x80C0)==0x80C0) // White bit 3
			         ||((pk&0x2030)==0x2030) // White bit 2
				 ||((pk&0x080C)==0x080C)   // White bit 1
				 ||((pk&0x0203)==0x0203)   // White bit 0
            		           	 ||(pk&0xAA00))          // Anything green?
				{
					hit=player_bullet.y;
					break;
				}
			}

			player_bullet.timer.value=frames+player_bullet.timer.delta;

			if(player_bullet.y<=64)	// Reached the top
       		       	{
                                if((ufo.active)&&(ufo.x<=player_bullet.x)
                                               &&(ufo.x+16>=player_bullet.x))
                                {
					// Bodge - need explostion

                                        //player_bullet.currentImage=3;
                                        //player_bullet.x=ufo.x;
                                        //player_bullet.y=ufo.y;
                                        //spritePlot(SCREEN,&player_bullet);
                                        //player_bullet.currentImage=0;

                                        player_bullet.active=0;

					// Bodge - need explosion
					ufo.draw=0; ufo.mask=1;
					spritePlot(SCREEN,&ufo);

                                        ufo.active=0;

                                        currentPlayer->score+=ufoScores[ufoScorePointer]*10;
                                        printScores();

                                        ufoScorePointer=(ufoScorePointer+1)&15;

                                        return 0;
                                }

				// Explosion!!!
		
				// BODGE - need explosion
				//player_bullet.currentImage++;
				//spritePlot(SCREEN,&player_bullet);
       		              	//player_bullet.currentImage--;
	
				player_bullet.active=0;

				return 0;
			}

			// Due to the moonscape, we need to do this:

			if(hit)
			{
				// Invader hit?

				for(i=0;i<SPRITES;i++)
				{
					if(currentPlayer->sprites[i].active)
					{
						sprite *s=&currentPlayer->sprites[i];

						if((abs(s->x-player_bullet.x)<11)
					  	 &&(abs(s->y-player_bullet.y)<11))
						{
							currentPlayer->newDelta=(50*currentPlayer->invaderCount)/SPRITES;

							if(currentPlayer->newDelta<s->timer.delta)
							{
								unsigned int j;
	
								for(j=0;j<SPRITES;j++) currentPlayer->sprites[j].timer.delta=currentPlayer->newDelta;
							}

							// Set up explosion at the invader's locations

							//player_bullet.currentImage=2;
							//player_bullet.x=players[currentPlayer].sprites[i].x;
							//player_bullet.y=players[currentPlayer].sprites[i].y;

							//spritePlot(SCREEN,&player_bullet);

		              				player_bullet.currentImage=0;

        	        	        	        spriteClear(SCREEN,moon,s);

							s->active=0;	
							player_bullet.active=0;
	
							currentPlayer->score+=invaderScores[i/SPRITESX];
							printScores();
				
							return --currentPlayer->invaderCount==0;	// Can only hit one thing!
						}
					}
				}

                                // Base?

                                player_bullet.currentImage=4;
                                player_bullet.y-=1;
				player_bullet.mask=1;
                               	spritePlot(SCREEN,&player_bullet);
				player_bullet.mask=0;
                                player_bullet.currentImage=0;

                                player_bullet.active=0;

				//show(SCREEN,0,256); while(1);

                                return 0;
			}
		}
	}

	if(player_bullet.active)
	{
		spritePlot(SCREEN,&player_bullet);	// Draw bullet if still active
	}

	return 0;	// Wave still ongoing
}

/////////////////
// invaderFire //
/////////////////

void invaderFire(unsigned int frames)
{
	//ShotReloadRate:
	//; The tables at 1CB8 and 1AA1 control how fast shots are created. The speed is based
	//; on the upper byte of the player's score. For a score of less than or equal 0200 then
	//; the fire speed is 30. For a score less than or equal 1000 the shot speed is 10. Less
	//; than or equal 2000 the speed is 0B. Less than or equal 3000 is 08. And anything
	//; above 3000 is 07.
	//;
	//; 1CB8: 02 10 20 30

	if((reload<frames)&&(bulletCount<maxBulletCount))
	{
		unsigned int firingInvader,bullet;

		for(bullet=0;bullet<maxBulletCount;bullet++) // Find first free bullet
		{
			if(!bullets[bullet].active)
			{
				int k;

				// Pick type

				bulletTypes[bullet]=rand()/(RAND_MAX/3);

				switch(bulletTypes[bullet])
				{
					case 0:  bullets[bullet].image[0]=&lib.images[19];
						 bullets[bullet].image[1]=&lib.images[20];
						 bullets[bullet].image[2]=&lib.images[21];
						 bullets[bullet].image[3]=&lib.images[22];
						 break;
					case 1:  bullets[bullet].image[0]=&lib.images[23];
						 bullets[bullet].image[1]=&lib.images[24];
						 bullets[bullet].image[2]=&lib.images[23];
						 bullets[bullet].image[3]=&lib.images[25];
						 break;
					default: bullets[bullet].image[0]=&lib.images[16];
						 bullets[bullet].image[1]=&lib.images[9];
						 bullets[bullet].image[2]=&lib.images[17];
						 bullets[bullet].image[3]=&lib.images[13];
						 break;
				}

				bulletCount++;
				setInvaderReload();

				if(bulletTypes[bullet]==0)
				{
					// Bullet type 0 fires either at the player, or the closest to the player

					int nearest=INT_MAX;

					for(k=0;k<SPRITES;k++)
					{
						if(currentPlayer->sprites[k].active)
						{
							int d=currentPlayer->sprites[k].x>player.x?currentPlayer->sprites[k].x-player.x
										   :player.x-currentPlayer->sprites[k].x;

							if(d<nearest)
							{
								firingInvader=k; nearest=d;
							}
						}
					}
				}
				else 
				{
					// Make bullet come from random invader

					do
					{
						firingInvader=rand()/(RAND_MAX/SPRITES);
					}
					while(!currentPlayer->sprites[firingInvader].active);
				}


				// Now move fire to invader below, if they exist

				for(k=firingInvader+11;k<SPRITES;k+=11) if(currentPlayer->sprites[k].active) firingInvader=k;

				// Initiate the bullet

				bullets[bullet].y=currentPlayer->sprites[firingInvader].y+8;
				bullets[bullet].x=currentPlayer->sprites[firingInvader].x+4;
				bullets[bullet].active=1;
				bullets[bullet].timer.value=frames;
				bullets[bullet].timer.delta=3;
				bullets[bullet].currentImage=0;

				//if(sound) do_sound(3000,255,1,200,0,5,0,9);

				break;
			}
		}
	}
}

///////////////////////////////
// bounceInvaders            //
//                           //
// returns: 1 - game overn   //
//          0 - still going! // 
///////////////////////////////

unsigned int waveTime=0;

int bounceInvaders()
{
        unsigned int i,lowest=0;

        // Move the invaders down and reverse direction

        for(i=0;i<SPRITES;i++)
                if(currentPlayer->sprites[i].active)
                        lowest=max(lowest,currentPlayer->sprites[i].y);

        if(lowest+16>=195) fill(SCREEN,lowest+8,lowest+16,0);

        currentPlayer->direction=-currentPlayer->direction; 
                
        for(i=0;i<SPRITES;i++)
        {
                sprite *s=&currentPlayer->sprites[i];

                if(s->active)     // Is sprite alive?
                {
                        spriteClear(SCREEN,moon,s);

                        currentPlayer->sprites[i].dx=currentPlayer->direction;
                        s->y+=8;        // Move invader down

                        // Game over?
                        if(s->y>=player.y)  return 1;

                        spritePlot(SCREEN,s);
                }
        }

	//printf("%f\n",(getFrames()-waveTime)/50.0);
	//exit(1);

        return 0;
}

///////////////////////////////
// handleInvaders            //
//                           //
// returns: 1 - invaders win //
//          0 - still going! // 
///////////////////////////////

int handleInvaders(unsigned int frames)
{
	unsigned int i,bounce=0;

	for(i=0;i<SPRITES;i++)
        {
		sprite *s=&currentPlayer->sprites[i];

		if((s->active)&&(s->timer.value<=frames))	// Time to move?
		{
			// Clear old invader from BG
			spriteClear(SCREEN,moon,s);

			s->x+=s->dx;				// Move invader
		        s->currentImage=1-s->currentImage; 	// Animate
			s->timer.value+=s->timer.delta;		// Set up timer for next movement 
			spritePlot(SCREEN,s);	// Draw invader on BG

			if(i+1==SPRITES) // Only check after all sprites have moved
			{
				unsigned int j;

				for(j=0;j<SPRITES;j++)
				{
					s=&currentPlayer->sprites[j];
				
					if((s->active)&&((s->x<XMIN)||(s->x>XMAX-17))) bounce=1;
				}
			}
		}
        }

	if(bounce) bounceInvaders();
	
	if(frames>=invaderSoundTimer)
	{
		invaderSoundTimer+=max(5,currentPlayer->newDelta);
		
		if(sound) do_sound(490,176,0,0,0,0,8,0);
	}

	return 0;
}

///////////////
// handleUFO //
///////////////

void handleUFO(unsigned int frames)
{
	if(!ufo.active)	// No ufo moving?
        {
		// TODO: Convert to timer?

		unsigned int r=rand(); // Get a random integer

                if((r&255)==0)		// Every 128 frames fire a UFO
                {
			ufo.active=1;
                        ufo.x=(r&256)?XMIN:(XMAX-1-ufo.image[0]->x);	// Use a random bit for side to start on
			ufo.dx=(ufo.x==XMIN)?2:-2;		//  direction depends on start location
			ufo.timer.value=0;
			ufo.timer.delta=1;		// Move every 5 frames
                }
        }
        else
        {
		if(ufo.timer.value<frames) // Is it time to move?
		{
			ufo.draw=0;
                	spritePlot(SCREEN,&ufo);	// Draw the UFO
			ufo.draw=1;
			
			ufo.x+=ufo.dx;		// Move

       	        	if((ufo.x<=XMIN)||(ufo.x>=(XMAX-ufo.image[0]->x)))	// Reached other end?
			{
				ufo.active=0;	// Switch off the UFO
				return;
			}

			ufo.timer.value=frames+ufo.timer.delta;	// Set the next time to run
		}

                spritePlot(SCREEN,&ufo);	// Draw the UFO
       }
}

void saveBases()
{
	memcpy(currentPlayer->bases,(unsigned char *)SCREEN+(192<<7),2048);
}

void loadBases()
{
	memcpy((unsigned char *)SCREEN+(192<<7),currentPlayer->bases,2048);
}

/////////////
// setupBG //
/////////////

void setupBG(unsigned int bases,unsigned int life,unsigned int line)
{
        unsigned int i;
        char buffer[80];
        sprite base;

        cls(SCREEN);

	if(bases) copyScreen(SCREEN,moon,157,255);

	sprintf(buffer,"%d",currentPlayer->lives);
	printAt(SCREEN,&font,XMIN+4,255-8,buffer);

        printAt(SCREEN,&font,xPrint(26),32,"SCORE<1> HI-SCORE SCORE<2>");
	sprintf(buffer,"CREDIT %02d",credits);
        printAt(SCREEN,&font,XMAX-6*strlen(buffer)-20,255-8,buffer);

        if(bases&&life)
	{
		for(i=0;i<4;i++)
	        {
        	        sprite s;

			s.mask=1; s.draw=1;
	                s.image[0]=&lib.images[26];
	                s.currentImage=0;
	                s.x=XMIN+i*48+32; s.y=195;
	
	                spritePlot(SCREEN,&s);
	        }

		saveBases();
	}
	else loadBases();

        if(line)
        {
                // Bottom green line

                base.image[0]=&lib.images[28];
                base.currentImage=0;
                base.mask=1;
                base.draw=1;
                base.y=245;

	        for(base.x=XMIN;base.x<XMAX;base.x+=32) spritePlot(SCREEN,&base);
        }

        base.image[0]=&lib.images[8];
        base.currentImage=0;
        base.y=255-8;
        base.x=XMIN+16;

        for(i=0;i<currentPlayer->lives-1;i++)
        {
                spritePlot(SCREEN,&base);
                base.x+=16;
        }


        base.image[0]=&lib.images[28];
        base.y--;

        for(i=0;i<256;i+=32) // WHAT DOES THIS DO?
        {
                base.x=i;
                //spritePlot(&base);
        }

        //copyAllScreen(SCREEN,SCREEN);
}

///////////////////
// setupInvaders //
///////////////////

void setupInvaders(unsigned int frames,unsigned int show)
{
	unsigned int i;

	for(i=0;i<SPRITES;i++)
        {
		sprite *s=&currentPlayer->sprites[i];

		int x=(i%11),y=i/11,ss=y==0?2:(y<3?4:0);

                s->image[0]=&lib.images[ss];
                s->image[1]=&lib.images[ss+1];
                s->currentImage=0;

                s->x=45+(x<<4)+(y==0?2:0)+1;
                s->y=(y<<4)+80+(currentPlayer->wave<<4);

                s->dx=1;
                s->dy=0;

                s->timer.value=frames+(SPRITES-i);
                s->timer.delta=50;

		s->mask=0;
		s->active=1;
		s->draw=1;

		if(show) spritePlot(SCREEN,s);
        }

	invaderSoundTimer=0;

	currentPlayer->invaderCount=SPRITES;
	currentPlayer->newDelta=50;
}

//////////////////
// IntroScreens //
//////////////////

void startGameScreen()
{
	while(gameMode==0)
	{
		setupBG(0,0,0);
		printScores();

		printAt(SCREEN,&font,xPrint(4),90,"PUSH");

		if(credits>1) printAt(SCREEN,&font,xPrint(20),130,"1 OR 2PLAYERS BUTTON");
		else printAt(SCREEN,&font,xPrint(19),130,"ONLY 1PLAYER BUTTON");

		keysleep(INT_MAX);
	}

	// gameMode will be 1 or 2 here
}

void setupGame(unsigned int frames);

void introScreens()
{
	unsigned int x=xPrint(0)-56; // Middle of screen
	unsigned int ks;

	cls(SCREEN);
        //setupGame(getFrames());
	setupInvaders(getFrames(),0);

	setupBG(0,0,0);

	while(1)
	{
		printScores();

		if(slowPrintAt(xPrint(4),70,"PLAY")) return;
		if(slowPrintAt(xPrint(14),100,"SPACE INVADERS")) return;

		if(keysleep(150)) return;

		printAt(SCREEN,&font,xPrint(21),130,"*SCORE ADVANCE TABLE*");
		ufo.active=1;
		ufo.x=x-3; ufo.y=150;
		ufo.image[0]=&lib.images[29];
		spritePlot(SCREEN,&ufo); ufo.image[0]=&lib.images[7]; ufo.active=0;

		players[0].sprites[0].x=x; players[0].sprites[0].y=170; spritePlot(SCREEN,&players[0].sprites[0]);

		players[0].sprites[SPRITES>>1].x=x-1; players[0].sprites[SPRITES>>1].y=190; spritePlot(SCREEN,&players[0].sprites[SPRITES>>1]);

		players[0].sprites[SPRITES-1].x=x-1; players[0].sprites[SPRITES-1].y=210; players[0].sprites[SPRITES-1].image[0]=&lib.images[30]; spritePlot(SCREEN,&players[0].sprites[SPRITES-1]); players[0].sprites[SPRITES-1].image[0]=&lib.images[0];

		if(slowPrintAt(x+16,150,"=? MYSTERY")) return; 
		if(slowPrintAt(x+16,170,"=30 POINTS")) return; 
		if(slowPrintAt(x+16,190,"=20 POINTS")) return; 
		if(slowPrintAt(x+16,210,"=10 POINTS")) return; 

		if(keysleep(150)) continue;

		// Score table

		cls(SCREEN);

		printScores();

		printAt(SCREEN,&font,xPrint(12),100,"INSERT  COIN"); 
		if(slowPrintAt(xPrint(16),140,"<1 OR 2 PLAYERS>")) return;
		if(slowPrintAt(xPrint(17),140+24,"*1 PLAYER  1 COIN")) return;
		if(slowPrintAt(xPrint(18),140+48,"*2 PLAYERS 2 COINS")) return;

		if(keysleep(100)) return;

		cls(SCREEN);

		doHelp();

		if(keysleep(350)) return;

		cls(SCREEN);
	}
}


void initiate(unsigned int convert)
{
	char name[80];
	unsigned int timeout=getFrames()+150,loaded;

	init();

	loaded=loadScreen((unsigned char *)SCREEN,drive,"logo_scr");

	moon=createScreen();
	cls(moon);

	loadScreen((unsigned char *)moon+(157<<7),drive,"moon_scr");

	// font

	if(convert)
	{
		sprintf(name,"%sfont_lib",drive);
		loadLibrary(&font,name,1); 

		sprintf(name,"%sfont_blb",drive);
		bSaveLibrary(&font,name);
	}
	else
	{
		sprintf(name,"%sfont_blb",drive);
		bLoadLibrary(&font,name,1); 
	}

 	if(font.n==0)
 	{
 		puts("Error: Loaded 0 images from font library!\n");
 		exit(1);
 	}

 	if(!loaded) printAt(SCREEN,&font,xPrint(28),75,"S P A C E   I N V A D E R S");

	printAt(SCREEN,&font,xPrint(18),150,"BY SIMON GREENAWAY");

	// sprites

	if(convert)
	{
		sprintf(name,"%sinvaders_lib",drive);
		loadLibrary(&lib,name,1);
		sprintf(name,"%sinvaders_blb",drive);
		bSaveLibrary(&lib,name);

		puts("Sprite convertion completed.");

		exit(0);
	}
	else
	{
		sprintf(name,"%sinvaders_blb",drive);
		bLoadLibrary(&lib,name,1);
	}

 	if(lib.n==0)
 	{
 		puts("Error: Loaded 0 images from sprite library!\n");
 		exit(1);
 	}

	// Create areas for storing players bases

	players[0].bases=myMalloc(128*20);
	players[1].bases=myMalloc(128*20);

	while(getFrames()<timeout)
	{
		unsigned int i;

		for(i=0;i<10;i++) if(keyrow(i)) return;
	}
}

//////////
// game //
//////////

unsigned int delayCounts=0;
long lastTime=0;

int gameLoop()
{
	unsigned int frames,lastFrames=0;

	#ifdef PROFILE
	unsigned int profileCounts[20],profileCounter=0,profileN;
	#endif

	#ifdef FPS
	char s[80];
	fpsCounter=0;
	fpsStart=getFrames();
	fpsTimer=fpsStart+50;
	#endif
	
	player.x=XMIN;

	#ifdef PROFILE
	for(frames=0;frames<20;frames++) profileCounts[frames]=0;
	#endif

	printScores();

	reload=getFrames()+5*50;

	waveTime=getFrames();

	while(1)
	{
		// Wait for next frame

		frames=getFrames();

		// Move the invaders on the BG screen
		if(handleInvaders(frames)) return 2; // GAME OVER!

		invaderFire(frames);

		handleKeys(frames);	// Fire/move the player

		if(handlePlayerBullet(frames)) return 0; // LEVEL CLEARED!

		handleUFO(frames);

		if(handleInvaderBullets(frames)) return 1; // LOSE A LIFE!

		#ifdef FPS
		fpsCounter++;
		if(fpsTimer<getFrames())
		{
			#ifdef IMMORTAL
			sprintf(s,"%d IMMORTAL MODE!",fpsCounter*500/((getFrames()-fpsStart)));
			#else
			sprintf(s,"%d",fpsCounter*500/((getFrames()-fpsStart)));
			#endif

			fpsTimer=getFrames()+50;

			fill(SCREEN,0,8,0);
			printAt(SCREEN,&font,0,0,s);
		}
		#endif
	}
}

///////////////
// setupGame //
///////////////

void setupGame(unsigned int frames)
{
	unsigned int i;

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
		bullets[i].mask=0;
		bullets[i].draw=1;
		bullets[i].active=0;
	}

	players[0].score=players[1].score=0;
	players[0].lives=players[1].lives=6;
	players[0].wave=players[1].wave=0;
	players[0].direction=players[1].direction=1;

	player.image[0]=&lib.images[8];
	player.image[1]=&lib.images[10];
	player.image[2]=&lib.images[14];
	player.image[3]=&lib.images[31];
	player.currentImage=0;
	player.mask=1;
	player.draw=1;
	player.active=1;
	player.x=0;
	player.y=256-player.image[0]->y-24;

	player_bullet.image[0]=&lib.images[12];
	player_bullet.image[1]=&lib.images[15];
	player_bullet.image[2]=&lib.images[11];
	player_bullet.image[3]=&lib.images[27];
        player_bullet.image[4]=&lib.images[32];
	player_bullet.currentImage=0;
	player_bullet.timer.value=0;
	player_bullet.timer.delta=1;
	player_bullet.mask=0;
	player_bullet.draw=1;
	player_bullet.active=0;
	shotCount=0;

	ufo.image[0]=&lib.images[7];
	ufo.currentImage=0;
	ufo.mask=0;
	ufo.draw=1;
	ufo.active=0;
	ufo.x=-1;
	ufo.y=64;

	keyTimer.value=0;
	keyTimer.delta=1;
	
	currentPlayer=&players[currentPlayerId=0];
}


//////////////
// mainloop //
//////////////

void mainLoop(int convert)
{
	unsigned int i;
	unsigned int goes[2];

	framesInit();

	initiate(convert);

	while(1)
	{
		setupGame(getFrames());

		if(credits==0) introScreens();

		startGameScreen();

		// Play!

		credits-=gameMode;

		setupGame(getFrames());

		players[0].score=players[1].score=0;	// Reset the scores
		goes[0]=goes[1]=0;

		while(currentPlayer->lives>0)
		{
			char s[80];
			unsigned int frames;

		        cls(SCREEN);

		        setupBG(0,0,0);   
               
			if(!goes[currentPlayerId]++) setupInvaders(getFrames(),0);

			// TODO: Following not seen on screen 
		        printAt(SCREEN,&font,xPrint(10),100,currentPlayerId==0?"PLAYER <1>":"PLAYER <2>");

			// Blink the score of the next player

			setFontMasking(1);

			frames=getFrames()+150;

			// Font character 'Z'+1 is a special blanking character

			while(getFrames()<frames)
			{
				unsigned flashFrames;

				if(getFrames()&1)
		                	sprintf(s,"%04d     %04d     %04d",players[0].score,highScore,players[1].score);
		                else if(currentPlayerId==0) 
					sprintf(s,"%c%c%c%c     %04d     %04d",'Z'+1,'Z'+1,'Z'+1,'Z'+1,highScore,players[1].score);
		                else 
					sprintf(s,"%04d     %04d     %c%c%c%c",players[0].score,highScore,'Z'+1,'Z'+1,'Z'+1,'Z'+1);

       				printAt(SCREEN,&font,xPrint(strlen(s)),48,s);
			}

			setFontMasking(0);

			setupBG(1,goes[currentPlayerId]==1,1); 

			// Start the player a few seconds into the game
			player.timer.value=frames+100;
			playerVisible=0;

			// Set invader timers

			for(i=0;i<SPRITES;i++)
			{
			        sprite *s=&currentPlayer->sprites[i];

				if(s->active) s->timer.value=frames+(SPRITES-i);
			}

			invaderSoundTimer=getFrames()+50;

			playerReload=1;

			// Play until death, then...

			loadBases();

			switch(gameLoop())
			{
				case 0: currentPlayer->wave++ ;
					setupInvaders(getFrames(),0);
					setupBG(1,1,1);
					break;		// Wave completed
				case 1: currentPlayer->lives--; break;	// Base hit
				case 2: currentPlayer->lives=0; break;	// Invaders hit the bottom
			}
			
			saveBases();

			if(gameMode==2)
				currentPlayer=&players[currentPlayerId=1-currentPlayerId];
		}

		printAt(SCREEN,&font,xPrint(9),70,"GAME OVER");

		sleep(5);

		if(currentPlayer->score>highScore) highScore=currentPlayer->score;
	}
}

//////////
// main //
//////////

int main(int argc, char *argv[])
{
	int s,convert=0;
	void *sv;
	long ver;

	sms_info(&sv,&ver);
	setSysBase(sv);


	// Parse the args

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-c")==0) convert=1;
		else if(strcmp(argv[s],"-d")==0) drive=argv[++s];
		else if(strcmp(argv[s],"-rom")==0) rom=argv[++s];
		else if(strcmp(argv[s],"-qdos")==0) qdos=atof(argv[++s]);
		else if(strcmp(argv[s],"-job")==0) job=atoi(argv[++s]);
		else
		{
			printf("Unknown command line argument: %s\n",argv[s]);
			exit(4);	
		}
	}

	mainLoop(convert);
}

