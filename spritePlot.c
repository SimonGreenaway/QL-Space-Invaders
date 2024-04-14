#include "image.h"

void drawSpriteNoMask(unsigned int xlim,unsigned short *address,unsigned short *shifter,image *image)
{
	register unsigned int a;
        register unsigned int addressDelta=64-image->x;

	switch(xlim) // Welcome to loop unroll City....
	{
		case 4: for(a=0;a<image->y;a++)
		{
			*address++|=*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address  |=*shifter++;

			address+=addressDelta;
		}

		break;

		case 3: for(a=0;a<image->y;a++)
		{
			*address++|=*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address  |=*shifter++;

			address+=addressDelta;
		}

		break;

		case 2: for(a=0;a<image->y;a++)
		{
			*address++|=*shifter++;
			*address++|=*shifter++;
			*address++|=*shifter++|*shifter++;
			*address++|=*shifter++;
			*address  |=*shifter++;

			address+=addressDelta;
		}

		break;

		case 1: for(a=0;a<image->y;a++)
		{
			*address++|=*shifter++;
			*address++|=*shifter++;
			*address  |=*shifter++;

			address+=addressDelta;
		}

		break;

		default:        for(a=0;a<image->y;a++)
		{
			unsigned int b;

			for(b=0;b<xlim;b++)
			{
				*address++|=*shifter++;
				*address++|=*shifter++;
				*address  |=*shifter++;
			}

			address+=addressDelta;
		}
	}
}

