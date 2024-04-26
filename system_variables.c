#include "system_variables.h"

void *sys_base=(unsigned char *)0x20000;

void setSysBase(unsigned char *a)
{
	sys_base=a;
}

unsigned char *getSysBase()
{
	return sys_base;
}
