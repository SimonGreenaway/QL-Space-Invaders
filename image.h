// undef MAGIC to disable image checking
#define MAGIC 0xdeadbeef

//#define HIMEM
//#define HILOCALS

// Enable second screen?
#undef SECONDSCREEN

#ifdef SECONDSCREEN
#define SCREEN2 ((char *)0x28000)
#endif

typedef void * screen;

extern screen SCREEN;
void init();
void* myMalloc(unsigned int i);

// Screens

screen createScreen();
void closeScreen(screen s);
void copyScreen(screen from,screen to,unsigned int yLow,unsigned int yHigh);
void copyAllScreen(screen from,screen to);
void showAll(screen screen);
void show(screen screen,unsigned int lowy,unsigned int highy);

//

void fill(screen screen,unsigned int xmin,unsigned int xmax,unsigned char c);
void plot(screen screen,unsigned short x,unsigned short y,unsigned char c);

//

typedef struct
{
	#ifdef MAGIC
	unsigned int magic;
	#endif

	unsigned short y;
	unsigned short x;

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
	unsigned int active;

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
		unsigned char b[4];     // For writing to the screen
        	unsigned short w[2];    // For loading data
       		unsigned int l;         // For shifting
	} z;
};

void spritePlot(screen scr,sprite *sprite);
void spriteClear(screen scr,screen mask,sprite *sprite);

//void tilePlot(unsigned short x,unsigned short y,image *image);
//void imagePlot(unsigned int x,unsigned int y,image *image);

// Image library handling

void loadLibrary(library *library,char *filename,int shift);
void bLoadLibrary(library *library,char *filename,int shift);
void bSaveLibrary(library *library,char *filename);

void cls(screen screen);

unsigned short peek(screen screen,unsigned int y,unsigned int x);

// Print text

void setFontMasking(unsigned int m);
void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c);
void printAt(screen screen,library *font,unsigned int x,unsigned y,char *s);
int loadScreen(unsigned char *scr,char *dir,char *file);

// Developmental

void draw8x8(screen screen,sprite *sprite);


