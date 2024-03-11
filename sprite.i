# 1 "sprite.c"
# 1 "/usr/local/share/qdos/include/stdio.h" 1















# 26 "/usr/local/share/qdos/include/stdio.h"


























typedef long fpos_t;



typedef unsigned long  size_t;




















typedef char __stdiobuf_t;
typedef size_t  __stdiosize_t;
typedef struct __iobuf {
__stdiobuf_t *__rptr;
__stdiobuf_t *__rend;
__stdiobuf_t *__wptr;
__stdiobuf_t *__wend;
__stdiobuf_t *__base;
__stdiosize_t __bufsiz;
short __flag;
char __file;
__stdiobuf_t __buf;
int (*__filbuf) (struct __iobuf *) ;
int (*__flsbuf) (int,struct __iobuf *) ;
int (*__flush) (struct __iobuf *) ;
struct __iobuf *__next;
} FILE;
extern FILE __stdin;
extern FILE __stdout;
extern FILE __stderr;



# 113 "/usr/local/share/qdos/include/stdio.h"











int getc (FILE *) ;

int getchar (void) ;

# 142 "/usr/local/share/qdos/include/stdio.h"











int putc (int,FILE *) ;

int putchar (int) ;


int feof (FILE *) ;


int ferror (FILE *) ;


void clearerr (FILE *) ;

FILE *fopen (const char *,const char *) ;
FILE *freopen (const char *,const char *,FILE *) ;
int fflush (FILE *) ;
int fclose (FILE *) ;
int fgetpos (FILE *,fpos_t *) ;
int fsetpos (FILE *,const fpos_t *) ;
long ftell (FILE *) ;
int fseek (FILE *,long,int) ;
void rewind (FILE *) ;
int fgetc (FILE *) ;
int fputc (int,FILE *) ;
__stdiosize_t fread (void *,__stdiosize_t,
__stdiosize_t,FILE *) ;
__stdiosize_t fwrite (const void *,__stdiosize_t,
__stdiosize_t,FILE *) ;
int getw (FILE *) ;
int putw (int,FILE *) ;
char *gets (char *) ;
char *fgets (char *,int,FILE *) ;
int puts (const char *) ;
int fputs (const char *,FILE *) ;
int ungetc (int,FILE *) ;
int printf (const char * ,... ) ;
int fprintf (FILE *,const char * ,... ) ;
int sprintf (char *,const char * ,... ) ;
int vprintf (const char *,char * ) ;
int vfprintf (FILE *,const char *,char * ) ;
int vsprintf (char *,const char *,char * ) ;
int scanf (const char * ,... ) ;
int fscanf (FILE *,const char * ,... ) ;
int sscanf (const char *,const char * ,... ) ;
void setbuf (FILE *,char *) ;
int setvbuf (FILE *,char *,int,__stdiosize_t) ;
int rename (const char *,const char *) ;
int remove (const char *) ;
void perror (const char *) ;
char * tmpnam (char *) ;
FILE * tmpfile (void) ;



















char * ctermid (char *s) ;

char * cuserid (char *s) ;
FILE * fdopen (int,const char *) ;

int fileno (FILE *) ;



int pclose (FILE *) ;
FILE *popen (const char *,const char *) ;

FILE *fopene (const char *,const char *,int) ;
int getch (void) ;
int getche (void) ;
int kbhit (void) ;
int putch (int) ;
int ungetch (int) ;
void setnbf (FILE *) ;
long fgetchid (FILE *) ;
FILE *fusechid (long) ;








# 1 "sprite.c" 2

# 1 "/usr/local/share/qdos/include/stdlib.h" 1



# 1 "/usr/local/share/qdos/include/sys/types.h" 1








typedef long time_t;



typedef long clock_t;



typedef char wchar_t;

typedef unsigned long dev_t;
typedef unsigned char gid_t;
typedef unsigned int ino_t;
typedef int mode_t;
typedef unsigned char nlkink_t;
typedef long off_t;
typedef long pid_t;
typedef unsigned short uid_t;
typedef long ptrdiff_t;
typedef char * addreg_t;
typedef long datareg_t;
typedef long chanid_t;
typedef unsigned char event_t;
typedef long jobid_t;
typedef short timeout_t;
typedef unsigned char colour_t;



















# 105 "/usr/local/share/qdos/include/sys/types.h"


# 4 "/usr/local/share/qdos/include/stdlib.h" 2











extern char * optarg;
extern int optind,opterr,optopt;
typedef struct { int quot; int rem; } div_t;
typedef struct {long quot; long rem; } ldiv_t;







void * malloc (size_t) ;
void * _Calloc  (size_t,size_t) ;
void * _Realloc  (void *,size_t) ;
void free (void *) ;
char * alloca (size_t) ;
char * getmem (int) ;
char * getml (long) ;
int rlsmem (char *,int) ;
int rlsml (char *,long) ;

void *bsearch (const void *,const void *,size_t,size_t,int (*)(const void *,const void *)) ;
void _Qsort  (void *,size_t,size_t,int (*)(const void *,const void *)) ;
void dqsort (double *,int) ;
void fqsort (float *,int) ;
void lqsort (long *,int) ;
void sqsort (short *,int) ;
void tqsort (char **,int) ;
int rand (void) ;
void srand (unsigned) ;
double drand48 (void) ;
double erand48 (short *) ;
long jrand48 (short *) ;
void lcong48 (short *) ;
long lrand48 (void) ;
long mrand48 (void) ;
long nrand48 (short *) ;
short *seed48 (short *) ;
void srand48 (long) ;





int abs (int) ;
void _Abort  (void) ;
char * argopt (int,char**,char *,int *,char *) ;
int atexit (void (*)(void)) ;
double atof (const char *) ;
int atoi (const char *) ;
long atol (const char *) ;
div_t div (int,int) ;
void exit (int) ;
char * getenv (const char *) ;
gid_t getegid (void) ;
uid_t geteuid (void) ;
int getfnl (char *,char *,unsigned,int) ;
gid_t getgid (void) ;
int getopt (int,char **,char *) ;
int isatty (int) ;
long labs (long) ;
ldiv_t ldiv (long,long) ;
char * mktemp (char *) ;
int onexit (int(*)(void)) ;
int _Putenv  (char *) ;
double _Strtod  (const char *,char **) ;
long strtol (const char *,char **,int) ;
unsigned long _Strtoul  (const char *,char**,int) ;
int system (const char *) ;
char * ttyname (int) ;
long utpack (char *) ;
void utunpk (long,char *) ;



int mblen (const char * s,size_t n) ;
int mbtowc (wchar_t * pwc,const char *s,size_t n) ;
size_t mbstowcs (wchar_t * pwc,const char *s,size_t n) ;
int wctomb (char * s,wchar_t pwc) ;
size_t wcstombs (char * s,const wchar_t * pwc,size_t n) ;
char * getpass (char * prompt) ;

int envunpk (char *) ;
char * itoa (int,char *) ;






# 2 "sprite.c" 2

# 1 "/usr/local/share/qdos/include/string.h" 1



# 1 "/usr/local/share/qdos/include/sys/types.h" 1
# 106 "/usr/local/share/qdos/include/sys/types.h"

# 4 "/usr/local/share/qdos/include/string.h" 2

















void * memchr (const void *,int,size_t) ;
int _MemCmp  (const void *,const void *,size_t) ;
void * _MemCpy  (void *,const void *,size_t) ;
void * _MemMove  (void *,const void *,size_t) ;
void * _MemSet  (void *,int,size_t) ;
char * _StrCat  (char *,const char *) ;
char * strchr (const char *,int) ;
int strcmp (const char *,const char *) ;
int strcoll (const char *,const char *) ;
char * _StrCpy  (char *,const char *) ;
size_t strcspn (const char *,const char *) ;
char * strerror (int) ;
size_t _StrLen  (const char *) ;
char * strncat (char *,const char *,size_t) ;
int strncmp (const char *,const char *,size_t) ;
char * strncpy (char *,const char *,size_t) ;
char * strpbrk (const char *,const char *) ;
char * strrchr (const char *,int) ;
size_t strspn (const char *,const char *) ;
char * strstr (const char *,const char *) ;
char * strtok (char *,const char *) ;
size_t strxfrm (char *,const char *,size_t) ;
char * index (const char *,int) ;
char * memccpy (char *,char *,int,size_t) ;
char * rindex (const char *,int) ;
int stricmp (const char *,const char *) ;
char * strdup (char *) ;
char * strlwr (char *) ;
void strmfe (char *,const char *,const char *) ;
void strmfn (char *,const char *,const char *,const char *,const char *) ;
void strmfp (char *,const char *,const char *) ;
int strnicmp (const char *,const char *,size_t) ;
char * strnset (char *,int,int) ;
int strpos (const char *,int) ;
char * strrev (char *) ;
int strrpos (const char *,int) ;
char * strrstr (const char *,const char *) ;
char * strset (char *,int) ;
void strsfn (char *,char *,char *,char *,char *) ;
char * strupr (char *) ;


int stccpy (char *,char *,int) ;
char * stpblk (char *) ;



char * stpcpy (char *,const char *) ;
int strbpl (char **,int,char *) ;


void repmem (char *,char *,int,int) ;
void swmem (char *,char *,unsigned) ;
int stcarg (char *,char *) ;
int stcgfe (char *,char *) ;
int stcgfn (char *,char *) ;
int stcis (char *,char *) ;
int stcisn (char *,char *) ;
int stclen (char *) ;
int stcd_i (char *,int *) ;
int stcd_l (char *,long *) ;
int stch_i (char *,int *) ;
int stch_l (char *,long *) ;
int stci_d (char *,int) ;
int stci_h (char *,int) ;
int stci_o (char *,int) ;
int stcl_d (char *,long) ;
int stcl_h (char *,long) ;
int stcl_o (char *,long) ;
int stco_i (char *,int *) ;
int stco_l (char *,long *) ;
int stcpm (char *,char *,char **) ;
int stcpma (char *,char *) ;
int stcu_d (char *,unsigned) ;
int stcul_d (char *,unsigned long) ;
char * stpdate (char *,int,char *) ;
char * stpsym (char *,char *,int) ;
char * stptime (char *,int,char *) ;
char * stptok (char *,char *,int,char *) ;
int stscmp (char *,char *) ;
int stspfp (char *,int *) ;
char * strrpbrk (const char *,const char *) ;
int strfnd (const char *,const char *) ;
void strins (char *,char *) ;
char * strrstrip (char *,int) ;
char * strstrip (char *,int) ;


# 3 "sprite.c" 2

# 1 "/usr/local/share/qdos/include/math.h" 1





# 1 "/usr/local/share/qdos/include/sys/math.h" 1


extern const double _HUGE_VALUE;
extern const double _Infinity;

# 6 "/usr/local/share/qdos/include/math.h" 2



struct exception {
int type;
char * name;
double arg1,arg2;
double retval;
};



































extern int _fperr;
extern int errno;
extern int signgam;





double acos (double) ;
double asin (double) ;
double atan (double) ;
double atan2 (double,double) ;
double ceil (double) ;
double cos (double) ;
double cosh (double) ;
double exp (double) ;
double fabs (double) ;
double floor (double) ;
double fmod (double,double) ;
double frexp (double,int *) ;
double ldexp (double,int) ;
double log (double) ;
double log10 (double) ;
double modf (double,double *) ;
double pow (double,double) ;
double sin (double) ;
double sinh (double) ;
double sqrt (double) ;
double tan (double) ;
double tanh (double) ;
int matherr (struct exception *) ;
double acosh (double) ;
double asinh (double) ;
double atanh (double) ;
double cbrt (double) ;
double copysign (double,double) ;
double cot (double) ;
double erf (double) ;
double erfc (double) ;
double hypot (double,double) ;
double logb (double) ;
double nextafter (double,double) ;
double remainder (double,double) ;
double rint (double) ;
double scalb (double,double) ;
double j0 (double) ;
double j1 (double) ;
double jn (int,double) ;
double y0 (double) ;
double y1 (double) ;
double yn (int,double) ;
double gamma (double) ;
double lgamma (double) ;
int finite (double) ;
int isnan (double) ;
int unordered (double,double) ;




float ceilf (float) ;


float expf (float) ;
float fabsf (float) ;
float floorf (float) ;
float fmodf (float,float) ;
float logf (float) ;
float log10f (float) ;
float modff (float,float *) ;
float powf (float,float) ;


float sqrtf (float) ;



double except (int,char *,double,double,double) ;
char * ecvt (double,int,int *,int *) ;
char * fcvt (double,int,int *,int *) ;
char * gcvt (double,int,char *) ;











# 4 "sprite.c" 2

# 1 "/usr/local/share/qdos/include/qdos.h" 1



# 1 "/usr/local/share/qdos/include/sys/qlib.h" 1














# 1 "/usr/local/share/qdos/include/limits.h" 1








































































# 15 "/usr/local/share/qdos/include/sys/qlib.h" 2











typedef struct REGS {
datareg_t D0,D1,D2,D3;
addreg_t A0,A1,A2,A3;
} REGS_t;
extern int _oserr;
typedef struct QLSTR {
short qs_strlen;
char qs_str[1];
} QLSTR_t;






typedef struct QLFLOAT {
short qfp_exp;
long qfp_mant;
} QLFLOAT_t;
typedef struct QLHEAP {
long qh_size;
long qh_freeaddr;
jobid_t qh_job;
long qh_zero;
} QLHEAP_t;
typedef struct MELT {
long mp_size;
struct MELT *mp_next;
} MELT_t;

typedef struct QLVECTABLE {
long (*qv_adderr)(void) ;
long (*qv_illegal)(void) ;
long (*qv_divzero)(void) ;
long (*qv_CHK)(void) ;
long (*qv_TRAPV)(void) ;
long (*qv_priviol)(void) ;
long (*qv_tracexpt)(void) ;
long (*qv_intlev7)(void) ;
long (*qv_5trap)(void) ;
long (*qv_6trap)(void) ;
long (*qv_7trap)(void) ;
long (*qv_8trap)(void) ;
long (*qv_9trap)(void) ;
long (*qv_10trap)(void) ;
long (*qv_11trap)(void) ;
long (*qv_12trap)(void) ;
long (*qv_13trap)(void) ;
long (*qv_14trap)(void) ;
long (*qv_15trap)(void) ;
} QLVECTABLE_t;
typedef struct FULLREGS {
datareg_t jb_D0,jb_D1,jb_D2,jb_D3,jb_D4,jb_D5,jb_D6,jb_D7;
addreg_t jb_A0,jb_A1,jb_A2,jb_A3,jb_A4,jb_A5,jb_A6,jb_A7;
short jb_SR;
addreg_t jb_PC;
} FULLREGS_t;
typedef struct JOBHEADER {
long jb_len;
long jb_start;
jobid_t jb_owner;
long jb_hold;
unsigned short jb_tag;
unsigned char jb_prior;
unsigned char jb_princ;
short jb_stat;
char jb_rela6;
char jb_wflag;
jobid_t jb_wjob;
QLVECTABLE_t * jb_trapv;
struct FULLREGS jb_regs;
short jb_resvd;
} JOBHEADER_t;
typedef struct QL_LINK {
struct QL_LINK *l_next;
void (*l_rtn)(void) ;
} QL_LINK_t;
typedef struct QLD_LINK {
struct QLD_LINK *ld_next;
long (*ld_io)(void) ;
long (*ld_open)(void) ;
long (*ld_close)(void) ;
} QLD_LINK_t;
typedef struct QLDDEV_LINK {
struct QLDDEV_LINK *ldd_next;
long (*ldd_io)(void) ;
long (*ldd_open)(void) ;
long (*ldd_close)(void) ;
long (*ldd_slave)(void) ;
long (*ldd_rename)(void) ;
long (*ldd_trunc)(void) ;
long (*ldd_format)(void) ;
long ldd_plen;
QLSTR_t ldd_dname;
} QLDDEV_LINK_t;

typedef struct QLRECT {
unsigned short q_width;
unsigned short q_height;
unsigned short q_x;
unsigned short q_y;
} QLRECT_t;

typedef struct WINDOWDEF {
unsigned char border_colour;
unsigned char border_width;
unsigned char paper;
unsigned char ink;
unsigned short width;
unsigned short height;
unsigned short x_origin;
unsigned short y_origin;
} WINDOWDEF_t;























typedef struct qdirect {
unsigned long d_length;
unsigned char d_access;
unsigned char d_type;
unsigned long d_datalen;
long d_reserved;
unsigned short d_szname;
char d_name[36];
long d_update;
union {
long d_refdate;
struct {
unsigned short d_version;
unsigned short d_fileno;
} v2;
} u;
long d_backup;
} qdirect_t;
typedef struct DIR_LIST {
struct DIR_LIST *dl_next;
struct qdirect dl_dir;
char dl_cname[1];
} DIR_LIST_t;







typedef struct ext_mdinf {
union {
char m_size[22];
QLSTR_t m_name;
} xm_name;
union {
char m_dsize[6];
QLSTR_t m_dname;
} xm_dname;
unsigned char xm_dnum;
char xm_rdonly;
unsigned short xm_alloc;
unsigned long xm_total;
unsigned long xm_free;
unsigned long xm_hdrlen;
char xm_spare[20];
char xm_spare2[36];
} ext_mdinf_t;











extern WINDOWDEF_t _condetails;
extern char _copyright[];
extern long _def_priority;
extern char * _endmsg;
extern timeout_t _endtimeout;
extern long _Jobid;
extern long _memincr;
extern long _memmax;
extern long _memqdos;
extern long _mneed;
extern long _pipesize;
extern char _prog_name[];
extern char _SLASH;
extern char * _SPorig;
extern long _stack;
extern long _stackmargin;
extern char * _sys_var;
extern char _tmpdir_[];
extern char _tmpnam_[];
extern char _version[];
extern int os_nerr;
extern char *os_errlist[];
extern char _CPU;
extern char _FPU;
extern long (*_cmdchannels) (long) ;
extern int (*_cmdparams) (const char *,char ***,int *,int (*)(char *,char ***,int *)  ) ;
extern int (*_cmdwildcard) (char *,char ***,int *) ;
extern void (*_consetup) (chanid_t,WINDOWDEF_t *) ;
extern void _initcon (void) ;
extern long (*_stackchannels) (long) ;
extern int (*_readkbd) (chanid_t,timeout_t,char *) ;
int cmdexpand (char *,char ***,int*) ;
void consetup_qpac (chanid_t,WINDOWDEF_t *) ;
void consetup_title (chanid_t,WINDOWDEF_t *) ;
int readkbd_move (chanid_t,timeout_t,char *) ;
int ioppick (jobid_t) ;


QLSTR_t * _cstr_to_ql  (QLSTR_t *,char *) ;
QLFLOAT_t * _d_to_qlfp  (QLFLOAT_t *,double) ;
char * qlstr_to_c (char *,QLSTR_t *) ;
QLFLOAT_t * i_to_qlfp (QLFLOAT_t *,int) ;
QLFLOAT_t * l_to_qlfp (QLFLOAT_t *,long) ;
QLFLOAT_t * w_to_qlfp (QLFLOAT_t *,int) ;
double qlfp_to_d (QLFLOAT_t *) ;
long qlfp_to_f (QLFLOAT_t *) ;
QLSTR_t * qstrcat (QLSTR_t *,const QLSTR_t *) ;
char * qstrchr (const QLSTR_t *,int) ;
int qstrcmp (const QLSTR_t *,const QLSTR_t *) ;
QLSTR_t * qstrcpy (QLSTR_t *,const QLSTR_t *) ;
int qstricmp (QLSTR_t *,QLSTR_t *) ;
size_t qstrlen (const QLSTR_t *) ;
QLSTR_t * qstrncat (QLSTR_t *,const QLSTR_t *,short) ;
int qstrncmp (const QLSTR_t *,const QLSTR_t *,short) ;
QLSTR_t * qstrncpy (QLSTR_t *,const QLSTR_t *,short) ;
int qstrnicmp (QLSTR_t *,QLSTR_t *,short) ;








void _super (void) ;
void _user (void) ;
void _argfree  (char ***) ;
char * _argpack  (char * const *,int) ;
int _argunpack  (const char *,char ***,int *,int (*)(char *,char ***,int*)  ) ;

void _beep  (unsigned short,unsigned char) ;


int chddir (char *) ;
int _chpdir  (char *) ;
void _do_sound  (unsigned short,unsigned char,unsigned char,unsigned char,unsigned short,unsigned char,unsigned char,unsigned char) ;

int fnmatch (char *,char *) ;
int fqstat (int,struct qdirect *) ;
char * getcdd (char *,int) ;
char * getcpd (char *,int) ;
long getchid (int) ;
char * getcname (chanid_t,char *) ;
int iscon (chanid_t,timeout_t) ;
int isdevice (const char *,int *) ;
struct QLDDEV_LINK * isdirchid (chanid_t) ;
int isdirdev (const char *) ;
int isnoclose (int) ;
int keyrow (char) ;
chanid_t open_qdir (const char *) ;
int poserr (const char *) ;
void qdir_delete (DIR_LIST_t *) ;
DIR_LIST_t * qdir_read (char *,char *,int) ;
DIR_LIST_t * qdir_sort (DIR_LIST_t *,char *,int (*)(DIR_LIST_t *,DIR_LIST_t *,char *)) ;

long qdos1 (struct REGS *,struct REGS *) ;
long qdos2 (struct REGS *,struct REGS *) ;
long qdos3 (struct REGS *,struct REGS *) ;
pid_t qforkl (const jobid_t,const char *,int *,const char *,...) ;
pid_t qforklp (const jobid_t,const char *,int *,const char *,...) ;
pid_t qforkv (const jobid_t,const char *,int *,char * const *) ;
pid_t qforkvp (const jobid_t,const char *,int *,char * const *) ;
int qinstrn (char *,int) ;
int read_qdir (chanid_t,char *,char *,struct qdirect *,int) ;
int qstat (char *,struct qdirect *) ;
long stackcheck (void) ;
long stackreport (void) ;
char * str_oserr (int) ;
int usechid (chanid_t) ;
int waitfor (jobid_t,int *) ;
# 386 "/usr/local/share/qdos/include/sys/qlib.h"



# 4 "/usr/local/share/qdos/include/qdos.h" 2

































































void _mt_aclck  (long) ;
int _mt_activ  (jobid_t,unsigned char,timeout_t) ;
char * _mt_alchp  (long,long *,jobid_t) ;
char * _mt_alloc  (char **,long *) ;
char * _mt_alres  (long) ;
void _mt_baud  (long) ;
jobid_t _mt_cjob  (long,long,char *,jobid_t,char **) ;
void _mt_dmode  (short *,short *) ;
long _mt_free  (void) ;
int _mt_frjob  (jobid_t,int) ;
jobid_t _mt_inf  (char **,long *) ;
int _mt_ipcom  (void *) ;
int _mt_jinf  (jobid_t *,jobid_t *,long *,char **) ;
void _mt_lnkfr  (char *,char **,long) ;
void _mt_lxint  (QL_LINK_t *) ;
void _mt_rxint  (QL_LINK_t *) ;
void _mt_lpoll  (QL_LINK_t *) ;
void _mt_rpoll  (QL_LINK_t *) ;
void _mt_lschd  (QL_LINK_t *) ;
void _mt_rschd  (QL_LINK_t *) ;
void _mt_liod  (QLD_LINK_t *) ;
void _mt_riod  (QLD_LINK_t *) ;
void _mt_ldd  (QLDDEV_LINK_t *) ;
void _mt_rdd  (QLDDEV_LINK_t *) ;
int _mt_prior  (jobid_t,unsigned char) ;
long _mt_rclck  (void) ;
void _mt_rechp  (void *) ;
JOBHEADER_t * _mt_reljb  (jobid_t) ;
int _mt_reres  (void *) ;
int _mt_rjob  (jobid_t,int) ;
void _mt_sclck  (long) ;
int _mt_shrink  (void *,long) ;
int _mt_susjb  (jobid_t,timeout_t,char *) ;
int _mt_trans  (void *,void *) ;
int _mt_trapv  (long,QLVECTABLE_t *) ;





int _io_close  (chanid_t) ;
int _io_delete  (const char *) ;
int _io_format  (const char *,short *,short *) ;
chanid_t _io_open  (const char *,long) ;
chanid_t _io_open_qlstr  (QLSTR_t *,long) ;























int _fs_check  (chanid_t,timeout_t) ;
int _fs_date  (chanid_t,timeout_t,char,long *) ;
int _fs_flush  (chanid_t,timeout_t) ;
int _fs_headr  (chanid_t,timeout_t,void *,short) ;
int _fs_heads  (chanid_t,timeout_t,void *,short) ;
long _fs_load  (chanid_t,char *,unsigned long) ;
int _fs_mdinf  (chanid_t,timeout_t,void *,short *,short *) ;
int _fs_mkdir  (chanid_t) ;
long _fs_pos  (chanid_t,long,int) ;
int _fs_posab  (chanid_t,timeout_t,unsigned long *) ;
int _fs_posre  (chanid_t,timeout_t,long *) ;
int _fs_rename  (const void *,const void *) ;
int _fs_save  (chanid_t,void *,unsigned long) ;
int _fs_trunc  (chanid_t,timeout_t) ;
int _fs_vers  (chanid_t,timeout_t,long *) ;
int _fs_xinf  (chanid_t,timeout_t,struct ext_mdinf *) ;
int _io_edlin  (chanid_t,timeout_t,char **,short,short,short *) ;
int _io_fbyte  (chanid_t,timeout_t,char *) ;
int _io_fline  (chanid_t,timeout_t,void *,short) ;
int _io_fstrg  (chanid_t,timeout_t,void *,short) ;
int _io_pend  (chanid_t,timeout_t) ;
int _io_sbyte  (chanid_t,timeout_t,unsigned char) ;
int _io_sstrg  (chanid_t,timeout_t,void *,short) ;






int _io_fdate  (chanid_t,timeout_t,char,long *) ;
int _io_fvers  (chanid_t,timeout_t,long *) ;
int _io_fxinf  (chanid_t,timeout_t,struct ext_mdinf *) ;
int _io_mkdir  (chanid_t) ;
int _io_rename  (const char *,const char *) ;
int _io_trunc  (chanid_t,timeout_t) ;





































int _sd_bordr  (chanid_t,timeout_t,colour_t,short) ;
int _sd_chenq  (chanid_t,timeout_t,QLRECT_t *) ;
int _sd_clear  (chanid_t,timeout_t) ;
int _sd_clrbt  (chanid_t,timeout_t) ;
int _sd_clrln  (chanid_t,timeout_t) ;
int _sd_clrrt  (chanid_t,timeout_t) ;
int _sd_clrtp  (chanid_t,timeout_t) ;
int _sd_cure  (chanid_t,timeout_t) ;
int _sd_curs  (chanid_t,timeout_t) ;
int _sd_donl  (chanid_t,timeout_t) ;
int _sd_extop  (chanid_t,timeout_t,int (*)(void),long,long,void *) ;
int _sd_fill  (chanid_t,timeout_t,colour_t,QLRECT_t *) ;
int _sd_fount  (chanid_t,timeout_t,char *,char *) ;
int _sd_ncol  (chanid_t,timeout_t) ;
int _sd_nl  (chanid_t,timeout_t) ;
int _sd_nrow  (chanid_t,timeout_t) ;
int _sd_pan  (chanid_t,timeout_t,short) ;
int _sd_panln  (chanid_t,timeout_t,short) ;
int _sd_panrt  (chanid_t,timeout_t,short) ;
int _sd_pcol  (chanid_t,timeout_t) ;
int _sd_pixp  (chanid_t,timeout_t,short,short) ;
int _sd_pos  (chanid_t,timeout_t,short,short) ;
int _sd_prow  (chanid_t,timeout_t) ;
int _sd_pxenq  (chanid_t,timeout_t,QLRECT_t *) ;
int _sd_recol  (chanid_t,timeout_t,char *) ;
int _sd_scrbt  (chanid_t,timeout_t,short) ;
int _sd_scrol  (chanid_t,timeout_t,short) ;
int _sd_scrtp  (chanid_t,timeout_t,short) ;
int _sd_setfl  (chanid_t,timeout_t,char) ;
int _sd_setin  (chanid_t,timeout_t,colour_t) ;
int _sd_setmd  (chanid_t,timeout_t,short) ;
int _sd_setpa  (chanid_t,timeout_t,colour_t) ;
int _sd_setst  (chanid_t,timeout_t,colour_t) ;
int _sd_setsz  (chanid_t,timeout_t,short,short) ;
int _sd_setul  (chanid_t,timeout_t,char) ;
int _sd_tab  (chanid_t,timeout_t,short) ;
int _sd_wdef  (chanid_t,timeout_t,colour_t,short,QLRECT_t *) ;













int _sd_arc  (chanid_t,timeout_t,double,double,double,double,double) ;
int _sd_elipse  (chanid_t,timeout_t,double,double,double,double,double) ;
int _sd_flood  (chanid_t,timeout_t,long) ;
int _sd_gcur  (chanid_t,timeout_t,double,double,double,double) ;
int _sd_line  (chanid_t,timeout_t,double,double,double,double)  ;
int _sd_point  (chanid_t,timeout_t,double,double) ;
int _sd_scale  (chanid_t,timeout_t,double,double,double) ;
int _sd_iarc  (chanid_t,timeout_t,long,long,long,long,long) ;
int _sd_ielipse  (chanid_t,timeout_t,long,long,long,long,long) ;
int _sd_igcur  (chanid_t,timeout_t,long,long,long,long) ;
int _sd_iline  (chanid_t,timeout_t,long,long,long,long) ;
int _sd_ipoint  (chanid_t,timeout_t,long,long) ;
int _sd_iscale  (chanid_t,timeout_t,long,long,long) ;






























char * _cn_date  (char *,long) ;
char * _cn_day  (char *,long) ;
void _cn_itobb  (char *,char *) ;
void _cn_itobw  (char *,short *) ;
void _cn_itobl  (char *,long *) ;
int _cn_itod  (char *,short *) ;
void _cn_itohb  (char *,char *) ;
void _cn_itohw  (char *,short *) ;
void _cn_itohl  (char *,long *) ;
int _io_qeof  (char *) ;
int _io_qin  (char *,int) ;
int _io_qout  (char *,char *) ;
void _io_qset  (char *,long) ;
int _io_qtest  (char *,char *,long *) ;
int _io_serio  (chanid_t,timeout_t,int,long *,long *,char **,int ** ) ;
int _io_serq  (chanid_t,timeout_t,int,long *,long *,char **) ;
char * _mm_alchp  (long *) ;
char * _mm_alloc  (char **,long *) ;
void _mm_lnkfr  (char *,char **,long) ;
void _mm_rechp  (char *) ;
chanid_t _ut_con  (WINDOWDEF_t *) ;
int _ut_cstr  (const QLSTR_t *,const QLSTR_t *,int) ;
void _ut_err  (long,chanid_t) ;
void _ut_err0  (long) ;
void _ut_link  (void *,void *) ;
int _ut_mint  (chanid_t,int) ;
int _ut_mtext  (chanid_t,const QLSTR_t *) ;
chanid_t _ut_scr  (WINDOWDEF_t *) ;
void _ut_unlnk  (void *,void *) ;
chanid_t _ut_window  (const char *,char *) ;


# 5 "sprite.c" 2


# 1 "image.h" 1
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
		unsigned char b[4];      
        	unsigned short w[2];     
       		unsigned int l;          
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
void clsAll();
# 7 "sprite.c" 2


struct library lib;	 
struct library font;	 

 








struct sprite sprites[(11			*5			)	],bullets[3];
unsigned char bulletTypes[3];	 
unsigned maxBulletCount=1,bulletCount=0,shotCount;

struct sprite player,ufo,player_bullet;	 
int scores[3]={0,0,0};			 
int invaderScores[5]={30,20,20,10,10};
unsigned char ufoScores[]={10,05,05,10,15,10,10,05,30,10,10,10,05,15,10,05};
unsigned char ufoScorePointer=0;

unsigned int invaders=(11			*5			)	;		 

void printCharAt(unsigned int x,unsigned int y,char c)
{
	struct sprite s;

	if(c-33>=font.n)
	{
		printf("Font error: %d>=%d\n",c-33,font.n);
		exit(1);
	}

	s.x=x; s.y=y;
	s.image[0]=&font.images[c-33];
	s.currentImage=0;

	spritePlot(&s);
}

void printAt(unsigned int x,unsigned y,char *s)
{
	while(*s!=0)
	{
		if(*s!=32) printCharAt(x,y,*s);

		s++;
		x+=6;
	}
}

int keysleep(unsigned int frames)
{
	unsigned int target=*((unsigned short *)163886)	+frames;

	while(*((unsigned short *)163886)	<target)
	{
		unsigned int key=keyrow(-1);

		if(key) return key;
	}

	return 0;
}

int slowPrintAt(unsigned int x,unsigned y,char *s)
{
	while(*s!=0)
	{

		unsigned int frames=*((unsigned short *)163886)	;

		if(keyrow(1)) return 1;

		if(*s!=32) printCharAt(x,y,*s);

                showScratch(0,256);

		s++;
		x+=6;

		while(frames+10>*((unsigned short *)163886)	);

	}

	return 0;
}

 
 
 

unsigned int keyTimer=0;

void handleKeys()
{
	if(*((unsigned short *)163886)	>=keyTimer)
	{
		int key=keyrow(1);	 

        	if(key)		 
		{
        	        if((key==2)&&(player.x>0))
				player.x--;		 
                	else if((key==16)&&(player.x<256-player.image[0]->x))
					player.x++;	 
               	 	else if((key==64)&&(player_bullet.y<0))	 
                	{
	                        player_bullet.y=player.y;		 
        	                player_bullet.x=player.x+3;
				shotCount++;
			}
        	}

		keyTimer=*((unsigned short *)163886)	+2;
	}
}

 
 
 

unsigned char reload=0x30+*((unsigned short *)163886)	;

int handleInvaderBullets(unsigned int frames)
{
	int i;

	if(bulletCount>0) for(i=0;i<maxBulletCount;i++)
	{
	        if((bullets[i].y>-1)&&(bullets[i].timer<=frames))	 
	        {
			bullets[i].timer=*((unsigned short *)163886)	+bullets[i].timerDelta;
	       	        bullets[i].y+=(invaders<=8?5:4);	 
			bullets[i].currentImage=(bullets[i].currentImage+1)&3;

			if(bullets[i].y>=player.y)	 
	              	{
				bullets[i].y=-1;
				bulletCount--;

				if(scores[0]<200) reload=frames+0x30;
				else if(scores[0]<1000) reload=frames+0x10;
				else if(scores[0]<2000) reload=frames+0x0B;
				else if(scores[0]<3000) reload=frames+0x08;
				else reload=*((unsigned short *)163886)	+0x07;
				 
				if((bullets[i].x>=player.x)&&(bullets[i].x<player.x+16))
				{
					bullets[i].currentImage=3;
					spritePlot(&bullets[i]);
					bullets[i].currentImage=0;
					return 1;
				}
	       		}
		}

		if(bullets[i].y>-1) spritePlot(&bullets[i]);	 
	}

	return 0;
}

 
 
 
 
 

int handlePlayerBullet()
{
        if((player_bullet.y>-1)&&(player_bullet.timer<*((unsigned short *)163886)	))	 
        {
       	        player_bullet.y-=2;	 
		player_bullet.timer=*((unsigned short *)163886)	+player_bullet.timerDelta;

		if(player_bullet.y<=32)	 
              	{
			 

			player_bullet.currentImage++;
			spritePlot(&player_bullet);
                     	player_bullet.currentImage--;

			player_bullet.y=-1;
       		}
              	else
		{
			unsigned int i;

			for(i=0;i<(11			*5			)	;i++)
			{
				if((sprites[i].x-3<player_bullet.x)
				&&(sprites[i].x+9>player_bullet.x)
				&&(sprites[i].y<=player_bullet.y)
				&&(sprites[i].y+8>=player_bullet.y))
				{
					unsigned int newDelta=(50*--invaders)/(11			*5			)	;
					if(invaders==0) return 1;	 

					if(newDelta<sprites[i].timerDelta)
					{
						unsigned int j;

						for(j=0;j<(11			*5			)	;j++) sprites[j].timerDelta=newDelta;
					}

					 

					player_bullet.currentImage=2;
					player_bullet.x=sprites[i].x;
					player_bullet.y=sprites[i].y;

					sprites[i].y=-1;	

					spritePlot(&player_bullet);

                     			player_bullet.currentImage=0;

					player_bullet.y=-1;

					scores[0]+=invaderScores[i/11			];
					
					break;	 
				}
			}

			if((ufo.y>-1)&&(ufo.x<player_bullet.x)
				     &&(ufo.x+9>player_bullet.x)
			             &&(ufo.y<=player_bullet.y)
			             &&(ufo.y+8>=player_bullet.y))
			{

				player_bullet.currentImage=3;
				player_bullet.x=ufo.x;
				player_bullet.y=ufo.y;
				spritePlot(&player_bullet);
				player_bullet.currentImage=0;

				player_bullet.y=-1;
				ufo.x=-1;

				scores[0]+=ufoScores[ufoScorePointer]*10;
				ufoScorePointer=(ufoScorePointer+1)&15;
			}

		}
	}

	if(player_bullet.y>-1) spritePlot(&player_bullet);	 

	return 0;	 
}

 
 
 
 
 
 

int handleInvaders()
{
	unsigned short frames=*((unsigned short *)163886)	;
	unsigned int i,bounce=0;

        for(i=0;i<(11			*5			)	;i++)
        {
		if(sprites[i].y>-1)	 
		{
			if(sprites[i].timer<=frames)	 
			{
				sprites[i].x+=sprites[i].dx;	 
	
		                sprites[i].currentImage=1-sprites[i].currentImage; 	 
	
				sprites[i].timer=frames+sprites[i].timerDelta;	 
	
				if((sprites[i].x<=0)||(sprites[i].x+16>=255)) bounce=1;	 

				 
				 
				 
				 
				 
				 
				 
				 

				if((bulletCount<maxBulletCount)&&(reload<*((unsigned short *)163886)	))
				{
					unsigned int j;

					for(j=0;j<maxBulletCount;j++)
					{
						if(bullets[j].y==-1)
						{
							 

							bulletTypes[j]=rand()/(2147483647 /3);

							switch(bulletTypes[j])
							{
								case 0:  bullets[j].image[0]=&lib.images[19];
									 bullets[j].image[1]=&lib.images[20];
									 bullets[j].image[2]=&lib.images[21];
									 bullets[j].image[3]=&lib.images[22];
									 break;
								case 1:  bullets[j].image[0]=&lib.images[23];
									 bullets[j].image[1]=&lib.images[24];
									 bullets[j].image[2]=&lib.images[23];
									 bullets[j].image[3]=&lib.images[25];
									 break;
								default: bullets[j].image[0]=&lib.images[16];
									 bullets[j].image[1]=&lib.images[9];
									 bullets[j].image[2]=&lib.images[17];
									 bullets[j].image[3]=&lib.images[13];
									 break;

							}

							bulletCount++;

							bullets[j].y=sprites[i].y+8;
							bullets[j].x=sprites[i].x+4;
							bullets[j].timer=frames;
							bullets[j].timerDelta=3;
							bullets[j].currentImage=0;

							break;
						}
					}
				}
			}
	
			spritePlot(&sprites[i]);	 
		}
        }

	if(bounce)	 
	{
                for(i=0;i<(11			*5			)	;i++)
                {
                        struct sprite *s=&sprites[i];

			if(s->y>-1)	 
			{
	                        s->dx=-s->dx;	 
        	                s->y+=8;	 

                	         
                        	if(s->y>=player.y)  return 1;
			}
                }
	}

	return 0;
}

 
 
 

void handleUFO(unsigned int frames)
{
	if(ufo.x==-1)	 
        {
		 

		unsigned int r=rand();  

                if((r&127)==0)		 
                {
                        ufo.x=(r&256)?0:255-ufo.image[0]->x;	 
			ufo.dx=(ufo.x==0)?4:-4;		 
			ufo.timer=0;
			ufo.timerDelta=5;		 
                }
        }
        else
        {

		if(ufo.timer<frames)  
		{
			ufo.x+=ufo.dx;		 

       	        	if((ufo.x<=0)||(ufo.x+ufo.image[0]->x>=255))	 
			{
				ufo.x=-1;	 
				return;
			}

			ufo.timer=frames+ufo.timerDelta;	 
		}

                spritePlot(&ufo);	 
       }
}

void setupBG(unsigned int lives,unsigned int bases)
{
        unsigned int i;
        char buffer[80];
        struct sprite base;

        clsAll();

        sprintf(buffer,"%d",lives); printAt(8,256-7,buffer);
        printAt(50,0,"SCORE<1> HI-SCORE SCORE<2>");
        printAt(150,256-7,"CREDIT 01");

        if(bases) for(i=0;i<4;i++)
        {
                struct sprite s;

                s.image[0]=&lib.images[26];
                s.currentImage=0;
                s.x=i*48+32; s.y=256-16-13-32;

                spritePlot(&s);
        }

        base.image[0]=&lib.images[8];
        base.currentImage=0;
        base.y=256-8;
        base.x=24;

        for(i=0;i<lives-1;i++)
        {
                spritePlot(&base);
                base.x+=16;
        }

        base.image[0]=&lib.images[28];
        base.y--;

        for(i=0;i<256;i+=32)
        {
                base.x=i;
                 
        }

        showScratch(0,256);
        initBG();
}

 
 
 

void introScreens()
{
	char s[80];

	clsAll();
	setupBG(6,0);

	while(1)
	{
		BGtoScratch();
		printAt(92,100,"INSERT  COIN"); showScratch(0,256);
		if(slowPrintAt(80,140,"<1 OR 2 PLAYERS>")) return;
		if(slowPrintAt(80,140+24,"*1 PLAYER  1 COIN")) return;
		if(slowPrintAt(80,140+48,"*2 PLAYERS 2 COINS")) return;

		if(keysleep(100)) return;

		BGtoScratch(); showScratch(0,256);

		if(slowPrintAt(120,70,"PLAY")) return;
		if(slowPrintAt(90,100,"SPACE INVADERS")) return;

		if(keysleep(50)) return;

		printAt(80,130,"*SCORE ADVANCE TABLE*");
		ufo.x=100; ufo.y=150;
		ufo.image[0]=&lib.images[29];
		spritePlot(&ufo); ufo.image[0]=&lib.images[7]; ufo.y=-1;

		sprites[0].x=104; sprites[0].y=170; spritePlot(&sprites[0]);
		sprites[(11			*5			)	/2].x=103; sprites[(11			*5			)	/2].y=190; spritePlot(&sprites[(11			*5			)	/2]);
		sprites[(11			*5			)	-1].x=103; sprites[(11			*5			)	-1].y=210; sprites[(11			*5			)	-1].image[0]=&lib.images[30]; spritePlot(&sprites[(11			*5			)	-1]); sprites[(11			*5			)	-1].image[0]=&lib.images[0];

		showScratch(0,256);

		if(slowPrintAt(120,150,"=? MYSTERY")) return; 
		if(slowPrintAt(120,170,"=30 POINTS")) return; 
		if(slowPrintAt(120,190,"=20 POINTS")) return; 
		if(slowPrintAt(120,210,"=10 POINTS")) return; 

		if(keysleep(500)) return;
	}
}

void initiate()
{
	init();

	loadLibrary(&lib,"invaders_lib",1);
	loadLibrary(&font,"font_lib",1); 

 	if(lib.n==0)
 	{
 		puts("Error: Cannot find 'sprites_lib'");
 		exit(1);
 	}

	scores[2]=0;  
}

 
 
 

int play()
{
	scores[0]=scores[1]=0;

	



	while(1)
	{
		char s[80];

		unsigned short frames=*((unsigned short *)163886)	;

		



		BGtoScratch();

		



		sprintf(s,"%04d     %04d     %04d",scores[0],scores[2],scores[1]);
		printAt(64,16,s);	

		



		handleKeys();
		if(handlePlayerBullet()) return 0;  

	        spritePlot(&player);

		



		if(handleInvaders()) return 2;  
		handleUFO(frames);

		if(handleInvaderBullets(frames))
		{
	        	showScratch(0,256);
			return 1;  
		}

		showScratch(0,256);
	}

	if(scores[0]>scores[2]) scores[2]=scores[0];
	if(scores[1]>scores[2]) scores[2]=scores[1];
}

 
 
 

void setupInvaders()
{
	unsigned int i;

	for(i=0;i<(11			*5			)	;i++)
        {
		int x=(i%11),y=i/11,s=y==0?2:(y<3?4:0);

                sprites[i].image[0]=&lib.images[s];
                sprites[i].image[1]=&lib.images[s+1];
                sprites[i].currentImage=0;

                sprites[i].x=x*16+(y==0?1:0)+1;
                sprites[i].y=y*16+48;

                sprites[i].dx=1;
                sprites[i].dy=0;

                sprites[i].timer=0;
                sprites[i].timerDelta=50;
        }

}

void setupGame()
{
	unsigned int i;

	setupInvaders();

	for(i=0;i<4 ;i++)
	{
		bullets[i].x=0; bullets[i].y=-1;
		bullets[i].dx=0; bullets[i].dy=0;

		bullets[i].image[0]=&lib.images[16];
		bullets[i].image[1]=&lib.images[9];
		bullets[i].image[2]=&lib.images[17];
		bullets[i].image[3]=&lib.images[13];
		bullets[i].image[4]=&lib.images[18];

		bullets[i].currentImage=0;
	}

	scores[0]=scores[1]=0;

	player.image[0]=&lib.images[8];
	player.currentImage=0;
	player.x=(256-player.image[0]->x)/2;
	player.y=256-player.image[0]->y-24;

	player_bullet.image[0]=&lib.images[12];
	player_bullet.image[1]=&lib.images[15];
	player_bullet.image[2]=&lib.images[11];
	player_bullet.image[3]=&lib.images[27];
	player_bullet.currentImage=0;
	player_bullet.x=0;
	player_bullet.y=-1;
	player_bullet.timer=0;
	player_bullet.timerDelta=1;
	shotCount=0;

	ufo.image[0]=&lib.images[7];
	ufo.currentImage=0;
	ufo.x=-1;
	ufo.y=32;
}


 
 
 

void mainLoop()
{
	initiate();

	while(1)
	{
		unsigned int lives=6;

		introScreens();

		while(keyrow(1));  

		setupGame();

		while(lives>0)
		{
			setupBG(lives,1); 

			setupInvaders();

			switch(play())
			{
				case 0:  
					break;
				case 1: lives--; break;
				case 2: lives=0; break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int s;
	int bm=0;

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-bm")==0) bm=1;
	}

	if(!bm) mainLoop();

	init();
	loadLibrary(&lib,"/home/simon/test5.lib",1);
	initBG();

	for(s=0;s<3;s++)
	{
		unsigned long t,c=0;
		struct sprite sprite[8];

		for(c=0;c<8;c++)
		{
			sprite[c].image[0]=&lib.images[s];
			sprite[c].currentImage=0;
			sprite[c].x=c;
			sprite[c].y=c*sprite[c].image[0]->y;
		}

		t=_mt_rclck ();
		while(_mt_rclck ()==t);
		t=_mt_rclck ()+10;
	
		while(_mt_rclck ()<t)
		{
			unsigned int i,y=0,x=0,ymin=1024,ymax=0;

			BGtoScratch();

			for(i=0;i<8;i++)
			{
				unsigned char ox=x,oy=y;

				if(y+lib.images[s].y>=256)
				{
					y=0;
					x+=lib.images[s].x*2+16;
				}

				x++;

				spritePlot(&sprite[i]);

				if(y>ymax) ymax=y;
				else if(y<ymin) ymin=y;

				y+=lib.images[s].y;
			}

			showScratch(ymin,ymax+lib.images[s].y);

			c+=8;
		}

		showScratch(0,256);
		printf("%d x %d\t-> %d\n",lib.images[s].x*4,lib.images[s].y,c);
		initBG();
	}
}

void plotTest()
{	
	short y;

	for(y=0;y<8;y++)
	{
		short x;

		for(x=0;x<8;x++)
		{
			unsigned char a;

			for(a=0;a<32;a++)
			{
				unsigned char b; for(b=0;b<16;b++)
				{
					plot(x*32+a,y*16+b,y);
				}
			}
		}
	}
}
