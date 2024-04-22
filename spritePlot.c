#include "image.h"

void draw8x8(screen screen,sprite *sprite)
{
	register unsigned int i;

	image *image=sprite->image[sprite->currentImage];

	unsigned short *address=((unsigned short *)screen)+(sprite->y<<6)+(sprite->x>>2);
	unsigned short *mask=(unsigned short *)(image->maskshifter[sprite->x&3]);
	unsigned short *data=(unsigned short *)(image->datashifter[sprite->x&3]);

	if(sprite->draw)
	{
		if(sprite->mask)
		{
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask++|*data++; address+=64;
			*address=(*address)&*mask|*data;
		}
		else
		{
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data++; address+=64;
			*address|=*data;
		}
	}
	else // if(sprite->mask)
	{
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask++; address+=64;
		*address&=*mask;
	}
}
