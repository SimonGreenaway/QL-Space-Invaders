void init();
void fill(unsigned short colour);
void plot(unsigned short x,unsigned short y,unsigned char c);

struct image
{
	short y;
	short x;

	char *name;

	unsigned short *mask;
	unsigned short *data;

	unsigned short *datashifter[4],*maskshifter[4];
};

struct sprite
{
	int images;
	struct image *image[8];

	int x,y,dx,dy,currentImage;
	unsigned int timer,timerDelta;
};

struct library
{
	int n;
	struct image *images;
};

struct shifter
{
	union
	{
		unsigned char b[4];     // For writing to the screen
        	unsigned short w[2];    // For loading data
       		unsigned int l;         // For shifting
	} z;
};

void spritePlot0(unsigned char *buffer,struct sprite *sprite);
void bufferCopy(unsigned char *from,unsigned char *to,unsigned int rowStart,unsigned int rowEnd);
unsigned char* createBuffer(unsigned int rows);

void spritePlot(struct sprite *sprite);

void tilePlot(unsigned short x,unsigned short y,struct image *image);
void imagePlot(unsigned int x,unsigned int y,struct image *image);
void loadLibrary(struct library *library,char *filename,int shift);

void showScratch(int from,int to);
void cls();
void clsAll();

void initBG();
void restoreBG();
void BGtoScratch();

unsigned short peek(unsigned int y,unsigned int x);
