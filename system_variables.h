void setSysBase(char *a);
char *getSysBase();

#define SV_BASE ((void *)getSysBase())
#define SV_IDENT ((unsigned short *)(getSysBase()+0x0))
#define SV_CHEAP ((unsigned long *)(getSysBase()+0x04))
#define SV_CHPFR ((unsigned long *)(getSysBase()+0x08))
#define SV_FREE ((unsigned long *)(getSysBase()+0x0C))
#define SV_BASIC ((unsigned long *)(getSysBase()+0x10))
#define SV_TRNSP ((unsigned long *)(getSysBase()+0x14))
#define SV_TRNFR ((unsigned long *)(getSysBase()+0x18))
#define SV_RESPR ((unsigned long *)(getSysBase()+0x1C))
#define SV_RAMT ((unsigned long *)(getSysBase()+0x20))
#define SV_RAND ((unsigned short *)(getSysBase()+0x2E))
#define SV_POLLM ((unsigned short *)(getSysBase()+0x30))
#define SV_TVMOD ((unsigned char *)(getSysBase()+0x32))
#define SV_SCRST ((unsigned char *)(getSysBase()+0x33))
#define SV_MCSTA ((unsigned char *)(getSysBase()+0x34))
#define SV_PCINT ((unsigned char *)(getSysBase()+0x35))
#define SV_NETNR ((unsigned char *)(getSysBase()+0x37))
#define SV_I2LST ((unsigned long *)(getSysBase()+0x38))
#define SV_PLIST ((unsigned long *)(getSysBase()+0x3C))
#define SV_SHLST ((unsigned long *)(getSysBase()+0x40))
#define SV_DRLST ((unsigned long *)(getSysBase()+0x44))
#define SV_DDLST ((unsigned long *)(getSysBase()+0x48))
#define SV_KEYQ ((unsigned long *)(getSysBase()+0x4C))
#define SV_TRAPV ((unsigned long *)(getSysBase()+0x50))


