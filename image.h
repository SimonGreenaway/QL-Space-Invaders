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
	int x,y,dx,dy,currentImage,timer;
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

void tilePlot(unsigned short x,unsigned short y,struct image *image);
void imagePlot(unsigned int x,unsigned int y,struct image *image);
void spritePlot(struct sprite *sprite);
void loadLibrary(struct library *library,char *filename,int shift);
void initBG();
void restoreBG();
void BGtoScratch();
void showScratch(int from,int to);
void cls();
