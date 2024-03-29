#define FRAMES ((unsigned short *)163886)       // Location of frame counter

void init();
void fill(unsigned short colour);
void plot(unsigned short x,unsigned short y,unsigned char c);

typedef struct
{
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
	int images;
	image *image[8];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;
} sprite;

typedef struct
{
	int n;
	image *images;
} library;

struct shifter
{
	union
	{
		unsigned char b[4];     // For writing to the screen
        	unsigned short w[2];    // For loading data
       		unsigned int l;         // For shifting
	} z;
};

void spritePlot0(unsigned char *buffer,sprite *sprite);

void bufferCopy(unsigned char *from,unsigned char *to,unsigned int rowStart,unsigned int rowEnd);
unsigned char* createBuffer(unsigned int rows);

void spritePlot(sprite *sprite);
void bgSpritePlot(sprite *sprite);

void tilePlot(unsigned short x,unsigned short y,image *image);
void imagePlot(unsigned int x,unsigned int y,image *image);
void loadLibrary(library *library,char *filename,char *cachefilename,int shift);

void showScratch(int from,int to);
void cls();
void clsAll();

void initBG();
void restoreBG();
void BGtoScratch();

unsigned short peek(unsigned int y,unsigned int x);
