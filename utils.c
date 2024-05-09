#include "invaders.h"

// Work out the x offset to print in the center of the screen

unsigned int xPrint(unsigned int chars)
{
        return XMIN+(((XMAX-XMIN)-6*chars)>>1);
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

