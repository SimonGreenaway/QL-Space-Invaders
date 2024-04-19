# 1 "spritePlot.c"
# 1 "image.h" 1


 


 







typedef struct 
{
	char *data;
	unsigned int ymin,ymax;
}
screen;

extern screen SCREEN;

void init();
void* myMalloc(unsigned int i);

 

screen createScreen();
void closeScreen(screen s);
void copyScreen(screen from,screen to,unsigned int yLow,unsigned int yHigh);
void copyAllScreen(screen from,screen to);
void showAll(screen screen);
void show(screen screen,unsigned int lowy,unsigned int highy);

 

void fill(screen screen,unsigned int xmin,unsigned int xmax,unsigned char c);
void plot(screen screen,unsigned short x,unsigned short y,unsigned char c);

 

typedef struct
{
	
	unsigned int magic;
	

	short y;
	short x;

	char *name;

	unsigned short *mask;
	unsigned short *data;

	unsigned short *datashifter[4],*maskshifter[4];
} image;

typedef struct
{
        unsigned int value,delta;
} timer;

typedef struct
{
	unsigned int active:1;

	int images;
	image *image[8];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;
} sprite;

typedef struct
{
	unsigned n;
	image *images;
} library;

struct shifter
{
	union
	{
		unsigned char b[4];      
        	unsigned short w[2];     
       		unsigned int l;          
	} z;
};

void spritePlot(screen screen,sprite *sprite);

 
 

 

void loadLibrary(library *library,char *filename,int shift);
void bLoadLibrary(library *library,char *filename,int shift);
void bSaveLibrary(library *library,char *filename);

void cls(screen screen);

unsigned short peek(screen screen,unsigned int y,unsigned int x);

 

void setFontMasking(unsigned int m);
void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c);
void printAt(screen screen,library *font,unsigned int x,unsigned y,char *s);
int loadScreen(unsigned char *scr,char *file);

 

void draw8x8(screen screen,sprite *sprite);


# 1 "spritePlot.c" 2


void draw8x8(screen screen,sprite *sprite)
{
	register unsigned int i;

	image *image=sprite->image[sprite->currentImage];

	unsigned short *address=(unsigned short *)screen+sprite->y*128+sprite->x/4;
	unsigned short *mask=(unsigned short *)(image->maskshifter[sprite->x&3]);
	unsigned short *data=(unsigned short *)(image->datashifter[sprite->x&3]);

	if(sprite->draw)
	{
		if(sprite->mask)
		{
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask++|*data++; address+=128;
			*address=(*address)&*mask|*data;
		}
		else
		{
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data++; address+=128;
			*address|=*data;
		}
	}
	else  
	{
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask++; address+=128;
		*address&=*mask;
	}
}
