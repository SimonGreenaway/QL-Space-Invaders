#include "system_variables.h"

void *sys_base=(char *)0x20000;

void setSysBase(char *a)
{
	sys_base=a;
}

char *getSysBase()
{
	return sys_base;
}
