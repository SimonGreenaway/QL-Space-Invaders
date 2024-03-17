#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qdos.h>

#include "image.h"

void binPrint(unsigned int i,unsigned char d);

const unsigned short masks[]={32575,57295,63475,65020};
const unsigned char shifts[]={64,16,4,1};

unsigned char *addresses[256];
unsigned int secondAddress;
unsigned short bits[8];

unsigned short *background;
unsigned char *scratch;

// Print a number in binary to a set number of places...

void binPrint(unsigned int i,unsigned char d)
{
	int z,b=32768;

	for(z=15;z>=0;z--)
	{
		if(z<=d-1) putchar(i&b?'1':'0');

		b>>=1;
	}
}

// Initialise the sprite system

long _stack = 4L*1024L; /* size of stack */
long _mneed = 4L*1024L; /* minimum requirement */
//long _mneed = 256L*1024L; /* minimum requirement */
long _memmax = 9999L * 1024L; /* maximum allowed */
long _memincr = 1L * 1024L; /* increment size */
long _memqdos = 20L * 1024L; /* minimum for QDOS */

//long _stack = 500*1024L; /* size of stack */

void init()
{
	int i;
	short colours=8,mode=0;

	background=(unsigned short *)createBuffer(256);
	scratch=createBuffer(256);
	secondAddress=(int)(background)-0x20000;

	mt_dmode(&colours,&mode);

	for(i=0;i<256;i++) addresses[i]=(unsigned char *)(i*128);

	for(i=0;i<8;i++) bits[i]=(i&3)+(i&4)*128;
}

// Clear the screen to black

void cls()
{
	memset((unsigned char *)0x20000,0,32768);
}

void clsAll()
{
	cls();

	memset(scratch,0,32768);
	memset(background,0,32768);
}

// Plot a point in the given colour

void plot(unsigned short x,unsigned short y,unsigned char c)
{
	unsigned char *address=addresses[y]+x/4;

	(*address)=((*address)&masks[x&3])|(bits[c]*shifts[x&3]);
}

void spritePlot(struct sprite *sprite)
{
	spritePlot0((unsigned char *)scratch,sprite);
}

void bgSpritePlot(struct sprite *sprite)
{
	spritePlot0((unsigned char *)background,sprite);
}

// Draw an image, erasing old one if needed

void spritePlot0(unsigned char *buffer,struct sprite *sprite)
{
	struct image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)buffer;
	unsigned int addressDelta=64-image->x;

	unsigned short *shifter=image->datashifter[sprite->x&3];
	unsigned short *maskshifter=image->maskshifter[sprite->x&3];

	unsigned int a,xlim=image->x/2;

	address+=(unsigned short*)addresses[sprite->y]+(sprite->x/4);

	switch(xlim) // Welcome to loop unroll City....
	{
		case 4:	for(a=0;a<image->y;a++)
			{
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address=  *address&*maskshifter++|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		case 3:	for(a=0;a<image->y;a++)
			{
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address=  *address&*maskshifter++|*shifter++; 
	
				address+=addressDelta;
			}

			break;
	
		case 2:	for(a=0;a<image->y;a++)
			{
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=(*address&*maskshifter++|*shifter++)
						&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address=  *address&*maskshifter++|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		case 1:	for(a=0;a<image->y;a++)
			{
				*address++=*address&*maskshifter++|*shifter++; 
				*address++=*address&*maskshifter++|*shifter++; 
				*address=  *address&*maskshifter++|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		default:	for(a=0;a<image->y;a++)
				{
					unsigned int b;
	
					for(b=0;b<xlim;b++)
					{
						*address++=*address&*maskshifter++|*shifter++; 
						*address++=*address&*maskshifter++|*shifter++; 
						*address=*address&*maskshifter++|*shifter++; 
					}
	
					address+=addressDelta;
				}
	}
}

void spritePlotM0(unsigned char *buffer,struct sprite *sprite)
{
	struct image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)buffer;
	unsigned int addressDelta=64-image->x;

	unsigned short *shifter=image->datashifter[sprite->x&3];

	unsigned int a,xlim=image->x/2;

	address+=(unsigned short*)addresses[sprite->y]+(sprite->x/4);

	switch(xlim) // Welcome to loop unroll City....
	{
		case 4:	for(a=0;a<image->y;a++)
			{
				*address++=*address|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address=  *address|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		case 3:	for(a=0;a<image->y;a++)
			{
				*address++=*address|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address=  *address|*shifter++; 
	
				address+=addressDelta;
			}

			break;
	
		case 2:	for(a=0;a<image->y;a++)
			{
				*address++=*address|*shifter++; 
				*address++=*address|*shifter++; 
				*address++=(*address|*shifter++)
						|*shifter++; 
				*address++=*address|*shifter++; 
				*address=  *address|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		case 1:	for(a=0;a<image->y;a++)
			{
				*address++=*address|*shifter++; 
				*address++=*address|*shifter++; 
				*address=  *address|*shifter++; 
	
				address+=addressDelta;
			}

			break;

		default:	for(a=0;a<image->y;a++)
				{
					unsigned int b;
	
					for(b=0;b<xlim;b++)
					{
						*address++=*address|*shifter++; 
						*address++=*address|*shifter++; 
						*address=*address|*shifter++; 
					}
	
					address+=addressDelta;
				}
	}
}

void spritePlotM(struct sprite *sprite)
{
	spritePlotM0((unsigned char *)scratch,sprite);
}
// Draw an image, erasing old one if needed

void imagePlot(unsigned int x,unsigned int y,struct image *image)
{
	unsigned short *pmask=image->mask,*data=image->data;
	const int shifts=2*(x&3);
	unsigned char *address=addresses[y]+2*(x/4);
	unsigned int addressRow=128-2*image->x;

	unsigned int yloop;

	for(yloop=0;yloop<image->y;yloop++)
	{
		int xloop;

		for(xloop=0;xloop<image->x;xloop+=2)
		{
			union shifter shifterHigh,shifterLow,mask;

			shifterHigh.z.l=shifterLow.z.l=mask.z.l=0;

			shifterHigh.z.w[0]=*data++;
			shifterLow.z.w[0]=*data++;
			mask.z.w[0]=*pmask;

			shifterHigh.z.l>>=shifts;
			shifterLow.z.l>>=shifts;
			mask.z.l>>=shifts;

			mask.z.l=~mask.z.l;

			*address++=((*address)&mask.z.b[0])|shifterLow.z.b[0]; 
			*address++=((*address)&mask.z.b[0])|shifterHigh.z.b[0]; 
			*address++=((*address)&mask.z.b[1])|shifterLow.z.b[1];
			*address++=((*address)&mask.z.b[1])|shifterHigh.z.b[1];
			*address++=((*address)&mask.z.b[2])|shifterLow.z.b[2];
			*address--=((*address)&mask.z.b[2])|shifterHigh.z.b[2];
		}

		address+=addressRow;
	}
}

void tilePlot(unsigned short x,unsigned short y,struct image *image)
{
	unsigned short *mask=(unsigned short *)image->mask;
	unsigned short *data=(unsigned short *)image->data;
	int a;

	for(a=0;a<image->y;a++)
	{
		int b;

		for(b=0;b<image->x;b++)
		{
			unsigned char *address=addresses[a+y]+x/4+b;

			//(*address)=((*address)&*mask)|(*data);
			*address=*data;

			mask++;
			data++;
		}
	}
}

char *readLine(FILE *in,char *buffer)
{
	do
	{
		if(feof(in))
		{
			puts("Error reading library!\n");
			exit(1);
		}

		fgets(buffer,80,in);
	}
	while(buffer[0]=='#');

	return buffer;
}

void preShift(struct image *image)
{
        int a,b,x,i,n=image->y*image->x/2;

        for(x=0;x<4;x++)
        {
                struct shifter shifter1,shifter2,mask,tmp;

                unsigned short *pmask=(unsigned short *)image->mask,*data=(unsigned short *)image->data;
                const unsigned int shifts=2*x;

                unsigned short *ss=image->datashifter[x]=(unsigned short *)malloc(sizeof(unsigned short)*n*3);
                unsigned short *mm=image->maskshifter[x]=(unsigned short *)malloc(sizeof(unsigned short)*n*3);

                for(a=0;a<image->y;a++)
                {
                        for(b=0;b<image->x;b+=2)
                        {
                                shifter1.z.l=shifter2.z.l=mask.z.l=0;

                                shifter1.z.w[0]=*data++;
                                shifter2.z.w[0]=*data++;
                                mask.z.w[0]=*pmask++; pmask++;

                                shifter1.z.l>>=shifts;
                                shifter2.z.l>>=shifts;
                                mask.z.l>>=shifts;

                                mask.z.l=~mask.z.l;

				for(i=0;i<3;i++)
				{
					tmp.z.b[1]=shifter1.z.b[i];
					tmp.z.b[0]=shifter2.z.b[i];
					*ss++=tmp.z.w[0];

					tmp.z.b[0]=mask.z.b[i];
					tmp.z.b[1]=mask.z.b[i];
					*mm++=tmp.z.w[0];
				}
                        }
                }
        }
}

void loadLibrary(struct library *library,char *filename,int shift)
{
	int i,a,b;
	unsigned short *d,*m;

	FILE *in=fopen(filename,"r");
	char buffer[80];

	puts("Loading library...");
	
	readLine(in,buffer); library->n=atoi(buffer);

	printf(" images: %d\n",library->n);
	
	library->images=(struct image *)(malloc(sizeof(struct image)*library->n));

	for(i=0;i<library->n;i++)
	{
		int n;

		readLine(in,buffer); printf("  %d %s",i,buffer);

		library->images[i].name=(char *)malloc(strlen(buffer)+1);
		strcpy(library->images[i].name,buffer);

		readLine(in,buffer); library->images[i].x=atoi(buffer); 
		readLine(in,buffer); library->images[i].y=atoi(buffer); 

		n=2*sizeof(unsigned short)*library->images[i].x*library->images[i].y;
		//printf("\t%dx%d\n",library->images[i].x,library->images[i].y);

		d=library->images[i].data=(unsigned short *)(malloc(n));
		m=library->images[i].mask=(unsigned short *)(malloc(n));

		for(b=0;b<library->images[i].y;b++)
		{
			for(a=0;a<library->images[i].x;a++)
			{
				readLine(in,buffer); *d++=(unsigned short)atoi(buffer);
				readLine(in,buffer); *m++=(unsigned short)atoi(buffer);
			}
		}

		for(a=0;a<2*library->images[i].x*library->images[i].y;a+=2)
		{
			unsigned short hi,lo;

			hi=(library->images[i].data[a+1]&255)
                          |(library->images[i].data[a]<<8);

			lo=(library->images[i].data[a]&0xff00)
			  |(library->images[i].data[a+1]>>8);

			library->images[i].data[a]=hi;
			library->images[i].data[a+1]=lo;

			hi=(library->images[i].mask[a+1]&255)
                          |(library->images[i].mask[a]<<8);

			lo=(library->images[i].mask[a]&0xff00)
			  |(library->images[i].mask[a+1]>>8);

			library->images[i].mask[a]=hi;
			library->images[i].mask[a+1]=lo;
		}

                if(shift)
		{
			preShift(&library->images[i]);

			free(library->images[i].data);
			free(library->images[i].mask);
		}
	}

	fclose(in);

	puts("Sprites loaded.\n");
}

////////////////////////////////
// Buffer creation and moving //
////////////////////////////////

// Create a buffer //

unsigned char* createbuffer(unsigned int rows)
{
	return (unsigned char *)malloc(rows*128);
}

// Copy from buffer to buffer (or the screen)

void bufferCopy(unsigned char *to,unsigned char *from,unsigned int rowStart,unsigned int rowEnd)
{
	memcpy(to+rowStart*128,from+rowStart*128,(rowEnd-rowStart)*128);
}

// Screen -> background

void initBG()
{
	bufferCopy((unsigned char *)background,(unsigned char *)0x20000,0,256);
}

// Background -> Screen

void restoreBG()
{
	bufferCopy((unsigned char *)0x20000,(unsigned char *)background,0,256);
}

// Background -> scratch

void BGtoScratch()
{
	bufferCopy((unsigned char *)scratch,(unsigned char *)background,0,256);
}

void showScratch(int from,int to)
{
	bufferCopy((unsigned char *)0x20000,scratch,0,256);
}

unsigned short peek(unsigned int y,unsigned int x)
{
	unsigned short *address=(unsigned short *)scratch;
	unsigned short data;
	address+=(unsigned short*)addresses[y]+(x/4);

	data=*address;

	switch(x&3)
	{
		case 0: return data&0x0203;
		case 1: return data&0x080C;
		case 2: return data&0x2030;
		default: return data&0x80C0;
	}
}
